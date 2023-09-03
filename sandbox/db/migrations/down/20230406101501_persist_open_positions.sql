alter table positions
  alter column close_order_execution_mid set not null,
  alter column close_order_id set not null,
  alter column close_order_quantity set not null,
  alter column closed_at set not null,
  drop column current_profit,
  alter column max_profit drop default,
  alter column max_profit_at drop default,
  alter column opened_at drop default,
  drop constraint positions_api_key_id_close_order_id_key,
  drop constraint positions_conditionally_require_close;

drop index positions_api_key_id_open_order_id_idx;
