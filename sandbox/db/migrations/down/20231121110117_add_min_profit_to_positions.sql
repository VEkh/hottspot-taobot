\timing
begin;
alter table positions
  drop column min_profit,
  drop column min_profit_at;
commit;
