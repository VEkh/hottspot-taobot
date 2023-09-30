\timing
begin;
alter table five_min_candles rename to candles;
alter table candles
  add column duration_minutes int not null default 5;
alter table candles
  alter column duration_minutes drop default;
alter table five_min_predictions rename column five_min_candle_id to candle_id;
alter index five_min_candles_pkey rename to candles_pkey;
alter index five_min_candles_closed_at_idx rename to candles_closed_at_idx;
alter index five_min_candles_id_closed_at_key rename to candles_id_closed_at_key;
alter index five_min_candles_opened_at_idx rename to candles_opened_at_idx;
drop index five_min_candles_opened_at_symbol_key;
create index candles_duration_minutes_idx on candles(duration_minutes);
create unique index candles_duration_minutes_opened_at_symbol_key on candles(duration_minutes, opened_at, symbol);
commit;
