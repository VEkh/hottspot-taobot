alter table positions
  alter column close_order_execution_mid drop not null,
  alter column close_order_id drop not null,
  alter column close_order_quantity drop not null,
  alter column closed_at drop not null,
  alter column max_profit set default 0.0,
  alter column max_profit_at set default now(),
  alter column opened_at set default now(),
  add column current_profit float not null default 0.0;

update
  positions
set
  current_profit =((-1 * close_order_quantity / abs(close_order_quantity)) *(close_order_execution_mid - open_order_execution_mid));

alter table positions
  add constraint positions_api_key_id_close_order_id_key unique (api_key_id, close_order_id),
  add constraint positions_conditionally_require_close check ((close_order_execution_mid is null and close_order_id is null and close_order_quantity is null and closed_at is null)::integer +(close_order_execution_mid is not null and close_order_id is not null and close_order_quantity is not null and closed_at is not null)::integer = 1);

create unique index positions_api_key_id_open_order_id_idx on positions(api_key_id, open_order_id);
