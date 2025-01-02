\timing
begin;
alter table positions
  add column account_currency text not null default 'USD',
  add column currency text not null default 'USD',
  add column to_account_currency_ratio double precision not null default 1.0;
commit;
