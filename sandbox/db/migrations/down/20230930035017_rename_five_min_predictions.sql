\timing
begin;
alter table candle_predictions rename constraint candle_predictions_candle_id_fkey to five_min_predictions_five_min_candle_fkey;
alter table candle_predictions rename constraint candle_predictions_candle_closed_at_fkey to five_min_predictions_candle_closed_at_fkey;
alter index candle_predictions_symbol_idx rename to five_min_predictions_symbol_idx;
alter index candle_predictions_candle_id_model_name_key rename to five_min_predictions_five_min_candle_id_model_name_key;
alter index candle_predictions_pkey rename to five_min_predictions_pkey;
alter sequence candle_predictions_id_seq
  rename to five_min_predictions_id_seq;
alter table candle_predictions rename to five_min_predictions;
commit;
