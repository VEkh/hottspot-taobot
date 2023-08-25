\timing
begin;
create table five_min_candles(
  close double precision not null,
  closed_at timestamp with time zone not null,
  high double precision not null,
  id bigint primary key,
  low double precision not null,
  open double precision not null,
  opened_at timestamp with time zone not null,
  symbol text not null
);
create sequence five_min_candles_id_seq
  cache 1 start with 1
  no maxvalue
  no minvalue;
alter sequence five_min_candles_id_seq owned by five_min_candles.id;
alter table only five_min_candles
  alter column id set default nextval('five_min_candles_id_seq'::regclass);
create index five_min_candles_closed_at_idx on five_min_candles(closed_at);
create index five_min_candles_opened_at_idx on five_min_candles(opened_at);
create unique index five_min_candles_opened_at_symbol_key on five_min_candles(opened_at, symbol);
commit;
