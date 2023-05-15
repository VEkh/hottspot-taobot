\timing
alter table avg_one_sec_variances
  add column quote_id bigint references quotes(id);

update
  avg_one_sec_variances
set
  quote_id = quotes.id
from
  quotes
where
  quotes.timestamp = avg_one_sec_variances.timestamp
  and quotes.symbol = avg_one_sec_variances.symbol;

alter table avg_one_sec_variances
  alter column quote_id set not null;

create unique index avg_one_sec_variances_quote_id_idx on avg_one_sec_variances(quote_id);

alter table quotes
  add constraint quotes_id_symbol_timestamp_key unique (id, symbol, timestamp);

alter table avg_one_sec_variances
  add constraint avg_one_sec_variances_quote_fkey foreign key (quote_id, symbol, timestamp) references quotes(id, symbol, timestamp);
