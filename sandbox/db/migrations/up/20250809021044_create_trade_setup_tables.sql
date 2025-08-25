\timing
begin;
create table market_sessions(
  close double precision not null,
  high double precision not null,
  id serial primary key,
  low double precision not null,
  open double precision not null,
  open_period tstzrange not null,
  symbol text not null,
  warm_up_close double precision not null,
  warm_up_high double precision not null,
  warm_up_low double precision not null,
  warm_up_open double precision not null,
  warm_up_period tstzrange not null
);
create index market_sessions_open_period_duration_idx on market_sessions(extract(epoch from (upper(open_period) - lower(open_period))));
create index market_sessions_open_period_idx on market_sessions using gist(open_period);
create index market_sessions_symbol_idx on market_sessions(symbol);
create index market_sessions_warm_up_idx on market_sessions using gist(warm_up_period);
create index market_sessions_warm_up_period_duration_idx on market_sessions(extract(epoch from (upper(warm_up_period) - lower(warm_up_period))));
create unique index market_sessions_symbol_open_period_warm_up_period_key on market_sessions(symbol, open_period, warm_up_period);
create table trade_setups(
  id serial primary key,
  priority serial not null,
  reverse_percentile_id int not null,
  stop_profit_id int not null
);
create unique index trade_setups_reverse_percentile_stop_profit_key on trade_setups(reverse_percentile_id, stop_profit_id);
-- reverse_percentile_id map:
-- { 1: 0.0, 2: 50.0 }
-- stop_profit_id map (when extending range)
-- {
--   1: 'Warm-up period range',
--   2: 'No stop profit. Reverse percentile is 0.0. When max_profit >= warm-up
--   period range, reverse percentile changes to 50',
--   3: 'Distance between warm up period range and median open period range (up to
--     that time)'
-- }
insert into trade_setups(priority, reverse_percentile_id, stop_profit_id)
  values (2, 1, 1),
(1, 1, 2),
(3, 1, 3),
(4, 2, 1),
(5, 2, 3);
select
  setval('trade_setups_priority_seq',(
      select
        max(priority)
      from trade_setups));
create table market_session_performances(
  env jsonb not null,
  id serial primary key,
  market_session_id int not null references market_sessions(id),
  profit_loss_percent double precision not null,
  trade_setup_id int not null references trade_setups(id)
);
create index market_session_performances_market_session_id_idx on market_session_performances(market_session_id);
create index market_session_performances_trade_setup_id_idx on market_session_performances(trade_setup_id);
create unique index market_session_performances_market_session_trade_setup_key on market_session_performances(market_session_id, trade_setup_id);
commit;
