defmodule HottspotCapital.Repo.Migrations.RenameCompanyName do
  use Ecto.Migration

  def up do
    [
      "ALTER TABLE companies RENAME COLUMN company_name TO name",
      "CREATE INDEX companies_name_idx ON companies(name)"
    ]
    |> Enum.each(&execute/1)
  end

  def down do
    [
      "DROP INDEX companies_name_idx",
      "ALTER TABLE companies RENAME COLUMN name TO company_name"
    ]
    |> Enum.each(&execute/1)
  end
end
