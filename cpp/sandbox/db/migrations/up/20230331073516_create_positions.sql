create table positions(
  api_key_id text not null,
  close_order_execution_mid float not null,
  close_order_id text not null,
  close_order_quantity float not null,
  closed_at timestamp with time zone not null,
  id bigint primary key,
  max_profit float not null,
  max_profit_at timestamp with time zone not null,
  open_order_execution_mid float not null,
  open_order_id text not null,
  open_order_quantity float not null,
  opened_at timestamp with time zone not null,
  stop_loss float not null,
  stop_profit float not null,
  symbol text not null
);

create index positions_api_key_id_idx on positions(api_key_id);

create index positions_symbol_idx on positions(symbol);

create sequence positions_id_seq
  cache 1 start with 1
  no maxvalue
  no minvalue;

alter sequence positions_id_seq owned by positions.id;

alter table only positions
  alter column id set default nextval('positions_id_seq'::regclass);
