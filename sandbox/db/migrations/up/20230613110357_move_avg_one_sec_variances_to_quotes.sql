\timing
begin;
set force_parallel_mode = on;
alter table quotes
  add column avg_one_sec_variance double precision not null default 0.0;
update
  quotes
set
  avg_one_sec_variance = avg_one_sec_variances.avg_one_sec_variance
from
  avg_one_sec_variances
where
  avg_one_sec_variances.quote_id = quotes.id;
drop table avg_one_sec_variances;
alter table quotes
  drop constraint quotes_id_symbol_timestamp_key;
commit;
