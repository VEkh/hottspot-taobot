\timing
set force_parallel_mode = on;

begin;
create table avg_one_sec_variances(
  avg_one_sec_variance double precision not null,
  id bigint primary key,
  quote_id bigint references quotes(id) not null,
  symbol text not null,
  timestamp timestamp with time zone not null
);
create sequence avg_one_sec_variances_id_seq
  cache 1 start with 1
  increment by 1
  no maxvalue
  no minvalue;
alter sequence avg_one_sec_variances_id_seq owned by avg_one_sec_variances.id;
alter table only avg_one_sec_variances
  alter column id set default nextval('avg_one_sec_variances_id_seq'::regclass);
create index avg_one_sec_variances_symbol_idx on avg_one_sec_variances(symbol);
create index avg_one_sec_variances_timestamp_idx on avg_one_sec_variances(timestamp);
create unique index avg_one_sec_variances_quote_id_idx on avg_one_sec_variances(quote_id);
create unique index avg_one_sec_variances_symbol_timestamp_idx on avg_one_sec_variances(symbol, timestamp);
alter table quotes
  add constraint quotes_id_symbol_timestamp_key unique (id, symbol, timestamp);
alter table avg_one_sec_variances
  add constraint avg_one_sec_variances_quote_fkey foreign key (quote_id, symbol, timestamp) references quotes(id, symbol, timestamp);
insert into avg_one_sec_variances(avg_one_sec_variance, symbol, "timestamp", quote_id)(
  select
    avg_one_sec_variance,
    symbol,
    "timestamp",
    id
  from
    quotes);
alter table quotes
  drop column avg_one_sec_variance;
commit;
