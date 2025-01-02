\timing
begin;
alter table positions
  drop column account_currency,
  drop column currency,
  drop column to_account_currency_ratio;
commit;
