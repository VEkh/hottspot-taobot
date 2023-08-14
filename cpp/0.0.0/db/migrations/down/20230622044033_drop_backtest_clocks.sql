\timing
begin;
create table backtest_clocks(
  id bigint primary key,
  api_key_id text not null,
  set_to timestamp with time zone not null,
  symbol text not null
);
create sequence backtest_clocks_id_seq
  cache 1 start with 1
  increment by 1
  no maxvalue
  no minvalue;
alter sequence backtest_clocks_id_seq owned by backtest_clocks.id;
alter table backtest_clocks
  alter column id set default nextval('backtest_clocks_id_seq'::regclass);
create unique index backtest_clocks_api_key_id_symbol_key on backtest_clocks(api_key_id, symbol);
commit;
