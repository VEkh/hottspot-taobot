create table quotes(
  ask double precision not null,
  bid double precision not null,
  id bigint primary key,
  inserted_at timestamp with time zone not null,
  symbol text not null,
  timestamp timestamp with time zone not null
);

create sequence quotes_id_seq
  cache 1 start with 1
  increment by 1
  no maxvalue
  no minvalue;

alter sequence quotes_id_seq owned by quotes.id;

alter table only quotes
  alter column id set default nextval('quotes_id_seq'::regclass);
