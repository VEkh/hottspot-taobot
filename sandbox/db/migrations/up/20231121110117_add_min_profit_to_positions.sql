\timing
begin;
alter table positions
  add column min_profit double precision not null default 0.0,
  add column min_profit_at timestamp with time zone not null default now();
update
  positions
set
  min_profit = least(current_profit, 0.0),
  min_profit_at = coalesce(closed_at, opened_at);
commit;
