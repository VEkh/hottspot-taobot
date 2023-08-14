create table avg_one_sec_variances(
  avg_one_sec_variance double precision not null,
  id bigint primary key,
  symbol text not null,
  timestamp timestamp with time zone not null
);

create index avg_one_sec_variances_symbol_idx on avg_one_sec_variances(symbol);

create index avg_one_sec_variances_timestamp_idx on avg_one_sec_variances(timestamp);

create unique index avg_one_sec_variances_symbol_timestamp_idx on avg_one_sec_variances(symbol, timestamp);

create sequence avg_one_sec_variances_id_seq
  cache 1 start with 1
  increment by 1
  no maxvalue
  no minvalue;

alter sequence avg_one_sec_variances_id_seq owned by avg_one_sec_variances.id;

alter table only avg_one_sec_variances
  alter column id set default nextval('avg_one_sec_variances_id_seq'::regclass);
