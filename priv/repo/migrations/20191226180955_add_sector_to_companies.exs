defmodule HottspotCapital.Repo.Migrations.AddSectorToCompanies do
  use Ecto.Migration

  def up do
    [
      "CREATE EXTENSION IF NOT EXISTS pgcrypto",
      """
      ALTER TABLE companies
        ADD COLUMN sector text NOT NULL DEFAULT gen_random_uuid()
      """,
      """
      CREATE INDEX companies_sector_idx ON companies(sector)
      """
    ]
    |> Enum.each(&execute/1)
  end

  def down do
    [
      "ALTER TABLE companies DROP COLUMN sector",
      "DROP EXTENSION IF EXISTS pgcrypto"
    ]
    |> Enum.each(&execute/1)
  end
end
