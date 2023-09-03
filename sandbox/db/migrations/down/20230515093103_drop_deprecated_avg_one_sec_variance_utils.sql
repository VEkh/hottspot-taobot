create or replace view computed_latest_avg_one_sec_variances as
with last_quotes as (
  select
    symbol,
    max(timestamp) as timestamp
  from
    quotes
  group by
    symbol
),
ranked_quotes as (
  select
    rank() over (partition by quotes.symbol,
      last_quotes.timestamp order by quotes.timestamp asc) as i,
((quotes.ask + quotes.bid) * 0.5) as mid,
    quotes.symbol,
    last_quotes.timestamp as ref_timestamp,
    quotes.timestamp
  from
    quotes
    join last_quotes on last_quotes.symbol = quotes.symbol
  where
    quotes.symbol = last_quotes.symbol
    and quotes.timestamp >=(last_quotes.timestamp - interval '3 minutes')
),
one_sec_variances as (
  select
    current_quotes.symbol,
    current_quotes.ref_timestamp,
    abs(next_quotes.mid - current_quotes.mid) /((extract(epoch from next_quotes.timestamp) - extract(epoch from current_quotes.timestamp))) as one_sec_variance
  from
    ranked_quotes as current_quotes
    join ranked_quotes as next_quotes on current_quotes.i = next_quotes.i - 1
      and current_quotes.symbol = next_quotes.symbol
      and current_quotes.ref_timestamp = next_quotes.ref_timestamp
)
  select
    avg(one_sec_variance) as avg_one_sec_variance,
  symbol,
  ref_timestamp as timestamp
from
  one_sec_variances
group by
  symbol,
  ref_timestamp;

create or replace view limited_one_sec_variance_running_averages as
select
  latest_avg.avg_one_sec_variance as latest,
  limited_agg.avg as running,
  symbols.symbol
from ( select distinct
    symbol as symbol
  from
    avg_one_sec_variances) as symbols
  join lateral (
    select
      avg_one_sec_variance,
      symbol
    from
      avg_one_sec_variances
    where
      symbol = symbols.symbol
    order by
      timestamp desc
    limit 1) as latest_avg on latest_avg.symbol = symbols.symbol
  join lateral (
    select
      limited.symbol,
      avg(limited.avg_one_sec_variance) as avg
    from (
      select
        avg_one_sec_variance,
        symbol,
        timestamp
      from
        avg_one_sec_variances
      where
        symbol = latest_avg.symbol
      order by
        timestamp desc
      limit 500000) as limited
  group by
    limited.symbol) as limited_agg on limited_agg.symbol = latest_avg.symbol;

create or replace function insert_latest_avg_one_sec_variances(symbols text[])
  returns setof avg_one_sec_variances
  as $$
declare
  result avg_one_sec_variances;
begin
  for result in insert into avg_one_sec_variances(avg_one_sec_variance, symbol, timestamp)
  select
    computed_latest_avg_one_sec_variances.avg_one_sec_variance,
    computed_latest_avg_one_sec_variances.symbol,
    computed_latest_avg_one_sec_variances.timestamp
  from (
    select
      *
    from
      computed_latest_avg_one_sec_variances
    where
      symbol = any (symbols)) as computed_latest_avg_one_sec_variances
  join (
    select
      coalesce(computed_running_avgs.running, fallback.avg_one_sec_variance) as running,
      coalesce(computed_running_avgs.symbol, fallback.symbol) as symbol
    from
      limited_one_sec_variance_running_averages as computed_running_avgs
      right join computed_latest_avg_one_sec_variances as fallback on fallback.symbol = computed_running_avgs.symbol) as running_avgs on running_avgs.symbol = computed_latest_avg_one_sec_variances.symbol
    and (computed_latest_avg_one_sec_variances.avg_one_sec_variance / running_avgs.running) >= 0.35
  on conflict
    do nothing
  returning
    avg_one_sec_variances.* loop
      return next result;
    end loop;
end
$$
language plpgsql;
