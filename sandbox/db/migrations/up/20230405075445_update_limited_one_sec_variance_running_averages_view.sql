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
