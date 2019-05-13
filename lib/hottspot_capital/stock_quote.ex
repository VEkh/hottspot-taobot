defmodule HottspotCapital.StockQuote do
  use Ecto.Schema

  alias Ecto.Changeset
  alias HottspotCapital.Repo

  @primary_key {:symbol, :string, autogenerate: false}

  schema "stock_quotes" do
    field(:close, :float)
    field(:company_name, :string)
    field(:date, :date)
    field(:inserted_at, :utc_datetime)
    field(:market_cap, :integer)
    field(:open, :float)
    field(:updated_at, :utc_datetime)
    field(:volume, :integer)
  end

  def changeset(%{} = params) do
    changeset(%__MODULE__{}, params)
  end

  def changeset(%__MODULE__{} = stock_quote, %{} = params) do
    required_fields = [
      :close,
      :company_name,
      :date,
      :market_cap,
      :open,
      :symbol,
      :volume
    ]

    stock_quote
    |> Changeset.cast(params, required_fields)
    |> Changeset.validate_required(required_fields)
    |> Changeset.validate_length(:symbol, max: 5)
    |> Changeset.unique_constraint(:symbol)
  end

  def upsert(%Changeset{} = changeset) do
    Repo.insert(
      changeset,
      conflict_target: :symbol,
      on_conflict: :replace_all
    )
  end
end
