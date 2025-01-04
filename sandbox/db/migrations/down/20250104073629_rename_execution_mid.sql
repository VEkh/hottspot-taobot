\timing
begin;
alter table positions rename column close_order_execution_price to close_order_execution_mid;
alter table positions rename column open_order_execution_price to open_order_execution_mid;
commit;
