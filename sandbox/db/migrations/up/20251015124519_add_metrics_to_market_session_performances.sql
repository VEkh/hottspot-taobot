\timing
begin;
alter table market_session_performances
  add column max_drawdown_percent double precision not null default 0.0,
  alter column profit_loss_percent set default 0.0,
  add column time_to_max_drawdown_seconds int not null default 0;
commit;
