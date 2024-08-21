\timing
begin;
create table price_actions(
  closed_at timestamp with time zone not null,
  id bigint primary key,
  opened_at timestamp with time zone not null,
  range_open_percent double precision not null default 0.0,
  symbol text not null
);
create sequence price_actions_id_seq
  cache 1 start with 1
  increment by 1
  no minvalue
  no maxvalue;
alter sequence price_actions_id_seq owned by price_actions.id;
alter table price_actions
  alter column id set default nextval('price_actions_id_seq'::regclass);
create index price_actions_closed_at_idx on price_actions(closed_at);
create index price_actions_opened_at_idx on price_actions(opened_at);
create index price_actions_symbol_idx on price_actions(symbol);
create unique index price_actions_closed_at_opened_at_symbol_key on price_actions(closed_at, opened_at, symbol);
alter table price_actions
  add constraint price_actions_closed_at_opened_at_check check (opened_at < closed_at);
commit;
