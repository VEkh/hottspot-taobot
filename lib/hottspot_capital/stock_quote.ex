defmodule HottspotCapital.StockQuote do
  use Ecto.Schema

  alias Ecto.Changeset
  alias HottspotCapital.Repo

  schema "stock_quotes" do
    field(:close, :float)
    field(:date, :date)
    field(:inserted_at, :utc_datetime)
    field(:open, :float)
    field(:symbol, :string)
    field(:updated_at, :utc_datetime)
    field(:volume, :integer)
  end

  def changeset(%{} = params) do
    changeset(%__MODULE__{}, params)
  end

  def changeset(%__MODULE__{} = stock_quote, %{} = params) do
    required_fields = [
      :close,
      :date,
      :open,
      :symbol,
      :volume
    ]

    stock_quote
    |> Changeset.cast(params, required_fields)
    |> Changeset.validate_required(required_fields)
    |> Changeset.validate_length(:symbol, max: 5)
    |> Changeset.unique_constraint(
      :symbol,
      message: "there is already a quote for this day",
      name: :stock_quotes_symbol_date_index
    )
  end

  def upsert(%Changeset{} = changeset) do
    Repo.insert(
      changeset,
      conflict_target: [:date, :symbol],
      on_conflict: :replace_all
    )
  end
end
