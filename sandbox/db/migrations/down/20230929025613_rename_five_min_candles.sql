\timing
begin;
alter index candles_pkey rename to five_min_candles_pkey;
alter index candles_closed_at_idx rename to five_min_candles_closed_at_idx;
alter index candles_id_closed_at_key rename to five_min_candles_id_closed_at_key;
alter index candles_opened_at_idx rename to five_min_candles_opened_at_idx;
alter table five_min_predictions rename column candle_id to five_min_candle_id;
alter sequence candles_id_seq
  rename to five_min_candles_id_seq;
alter table candles
  drop column duration_minutes;
alter table candles rename to five_min_candles;
create unique index five_min_candles_opened_at_symbol_key on five_min_candles(opened_at, symbol);
commit;
