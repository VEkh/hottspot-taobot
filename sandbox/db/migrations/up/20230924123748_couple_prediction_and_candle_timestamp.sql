\timing
begin;
create unique index five_min_candles_id_closed_at_key on five_min_candles(id, closed_at);
update
  five_min_predictions
set
  inserted_at = five_min_candles.closed_at
from
  five_min_candles
where
  five_min_candles.id = five_min_predictions.five_min_candle_id;
alter table five_min_predictions rename column inserted_at to candle_closed_at;
alter table five_min_predictions rename constraint five_min_predictions_five_min_candle_key to five_min_predictions_five_min_candle_fkey;
alter table five_min_predictions
  add constraint five_min_predictions_candle_closed_at_fkey foreign key (five_min_candle_id, candle_closed_at) references five_min_candles(id, closed_at);
commit;
