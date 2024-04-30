\timing
begin;
drop index candles_closed_at_idx;
drop index candles_opened_at_idx;
create index candles_closed_at_idx on candles using brin(closed_at);
create index candles_opened_at_idx on candles using brin(opened_at);
commit;
