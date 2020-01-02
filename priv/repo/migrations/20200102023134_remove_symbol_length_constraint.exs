defmodule HottspotCapital.Repo.Migrations.RemoveSymbolLengthConstraint do
  use Ecto.Migration

  def up do
    [
      "ALTER TABLE companies ALTER COLUMN symbol SET DATA TYPE text",
      "ALTER TABLE stock_quotes ALTER COLUMN symbol SET DATA TYPE text"
    ]
    |> Enum.each(&execute/1)
  end

  def down do
    [
      "ALTER TABLE companies ALTER COLUMN symbol SET DATA TYPE varchar(5)",
      "ALTER TABLE stock_quotes ALTER COLUMN symbol SET DATA TYPE varchar(5)"
    ]
    |> Enum.each(&execute/1)
  end
end
