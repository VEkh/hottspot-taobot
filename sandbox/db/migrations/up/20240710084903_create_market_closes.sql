\timing
begin;
create table market_closes(
  api_key_id text not null,
  closed_at timestamp with time zone not null,
  id bigint primary key,
  inserted_at timestamp with time zone not null default now(),
  symbol text not null
);
create sequence market_closes_id_seq
  cache 1 start with 1
  increment by 1
  no maxvalue
  no minvalue;
alter sequence market_closes_id_seq owned by market_closes.id;
alter table market_closes
  alter column id set default nextval('market_closes_id_seq'::regclass);
create index market_closes_api_key_id_idx on market_closes(api_key_id);
create index market_closes_closed_at_idx on market_closes(closed_at);
create index market_closes_symbol_idx on market_closes(symbol);
create unique index market_closes_api_key_id_closed_at_symbol_key on market_closes(api_key_id, closed_at, symbol);
commit;
