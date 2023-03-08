\set ORDER :ORDER
select
  case :'ORDER'
  when ':ORDER' then
    'asc'
  else
    :'ORDER'
  end as "ORDER" \gset

select
  version
from
  schema_migrations
order by
  version :ORDER;
