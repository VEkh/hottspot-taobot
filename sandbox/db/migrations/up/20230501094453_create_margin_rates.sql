create table margin_rates(
  id integer primary key,
  inserted_at timestamp with time zone not null default now(),
  multiplier double precision not null,
  symbol text not null
);

create index margin_rates_symbol_idx on margin_rates(symbol);

create sequence margin_rates_id_seq
  cache 1 start with 1
  increment by 1
  no maxvalue
  no minvalue;

alter sequence margin_rates_id_seq owned by margin_rates.id;

alter table only margin_rates
  alter column id set default nextval('margin_rates_id_seq'::regclass),
  add constraint margin_rates_multiplier_symbol_key unique (multiplier, symbol);
