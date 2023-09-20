\timing
begin;
create table five_min_predictions(
  close double precision not null,
  five_min_candle_id bigint not null,
  high double precision not null,
  id bigint primary key,
  inserted_at timestamp with time zone not null default now(),
  low double precision not null,
  model_name text not null,
  open double precision not null,
  symbol text not null,
  updated_at timestamp with time zone not null default now()
);
create sequence five_min_predictions_id_seq
  cache 1 start with 1
  increment by 1
  no maxvalue
  no minvalue;
alter sequence five_min_predictions_id_seq owned by five_min_predictions.id;
alter table five_min_predictions
  alter column id set default nextval('five_min_predictions_id_seq'::regclass);
create unique index five_min_predictions_five_min_candle_id_model_name_key on five_min_predictions(five_min_candle_id, model_name);
create index five_min_predictions_symbol_idx on five_min_predictions(symbol);
alter table five_min_predictions
  add constraint five_min_predictions_five_min_candle_key foreign key (five_min_candle_id) references five_min_candles(id);
commit;
