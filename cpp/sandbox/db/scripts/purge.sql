\echo '💡 Purging database'
select
  format($$drop database %s$$, :'DB_NAME')
where
  exists (
    select
      1
    from
      pg_database
    where
      datname = :'DB_NAME') \gexec

select
  format($f$drop role %s$f$, :'DB_USERNAME')
where
  exists (
    select
      1
    from
      pg_catalog.pg_roles
    where
      rolname = :'DB_USERNAME') \gexec

\echo '🎉 Finished purging database'
