create or replace view limited_one_sec_variance_running_averages as
select
  (array_agg(limited.avg_one_sec_variance order by limited.timestamp desc))[1] as latest,
  avg(limited.avg_one_sec_variance) as running,
  limited.symbol
from (
  select
    avg_one_sec_variance,
    symbol,
    timestamp
  from
    avg_one_sec_variances
  order by
    timestamp desc
  limit 500000) as limited
group by
  limited.symbol;
