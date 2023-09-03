create table streamed_quotes(
  ask float not null,
  bid float not null,
  id bigint primary key,
  symbol text not null,
  updated_at timestamp with time zone
);

create unique index streamed_quotes_symbol_idx on streamed_quotes(symbol);

create sequence streamed_quotes_id_seq
  cache 1 start with 1
  no maxvalue
  no minvalue;

alter sequence streamed_quotes_id_seq owned by streamed_quotes.id;

alter table only streamed_quotes
  alter column id set default nextval('streamed_quotes_id_seq'::regclass);
