\timing
begin;
drop index candles_closed_at_idx;
drop index candles_opened_at_idx;
create index candles_closed_at_idx on candles(closed_at);
create index candles_opened_at_idx on candles(opened_at);
commit;
