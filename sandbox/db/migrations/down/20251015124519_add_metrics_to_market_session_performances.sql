\timing
begin;
alter table market_session_performances
  drop column max_drawdown_percent,
  alter column profit_loss_percent drop default,
  drop column time_to_max_drawdown_seconds;
commit;
