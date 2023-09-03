create table account_stats(
  api_key_id text not null,
  equity double precision not null,
  id bigint primary key,
  inserted_at timestamp with time zone not null default now(),
  margin_buying_power double precision not null,
  margin_multiplier double precision not null
);

create index account_stats_api_key_id_idx on account_stats(api_key_id);

create index account_stats_inserted_at_idx on account_stats(inserted_at);

create unique index account_stats_api_key_id_inserted_at_idx on account_stats(api_key_id, inserted_at);

create sequence account_stats_id_seq
  cache 1 start with 1
  no maxvalue
  no minvalue;

alter sequence account_stats_id_seq owned by account_stats.id;

alter table only account_stats
  alter column id set default nextval('account_stats_id_seq'::regclass);
