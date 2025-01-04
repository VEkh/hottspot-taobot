\timing
begin;
alter table positions rename column close_order_execution_mid to close_order_execution_price;
alter table positions rename column open_order_execution_mid to open_order_execution_price;
commit;
