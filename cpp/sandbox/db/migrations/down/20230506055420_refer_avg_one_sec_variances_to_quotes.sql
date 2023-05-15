alter table avg_one_sec_variances
  drop constraint avg_one_sec_variances_quote_fkey;

alter table quotes
  drop constraint quotes_id_symbol_timestamp_key;

alter table avg_one_sec_variances
  drop column quote_id;
