select
  format($$insert into schema_migrations (version) values (%s)$$, :VERSION) \gexec
