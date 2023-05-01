drop function if exists insert_latest_avg_one_sec_variances;

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
