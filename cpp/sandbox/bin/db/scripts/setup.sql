\echo '💡 Setting up database'
select
  format($$ create role %s bypassrls createdb createrole login password '%s' replication superuser $$, :'DB_USERNAME', :'DB_PASSWORD')
where
  not exists (
    select
      1
    from
      pg_catalog.pg_roles
    where
      rolname = :'DB_USERNAME') \gexec

select
  format('create database %s owner %s', :'DB_NAME', :'DB_USERNAME')
where
  not exists (
    select
      1
    from
      pg_database
    where
      datname = :'DB_NAME') \gexec

\echo '🎉 Finished setting up database'