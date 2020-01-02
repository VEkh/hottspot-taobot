defmodule HottspotCapital.Company do
  require Ecto.Query
  use Ecto.Schema

  alias Ecto.Changeset
  alias HottspotCapital.Repo

  @primary_key {:symbol, :string, autogenerate: false}

  schema "companies" do
    field(:inserted_at, :utc_datetime)
    field(:market_cap, :integer)
    field(:name, :string)
    field(:sector, :string)
    field(:updated_at, :utc_datetime)
  end

  def changeset(%{} = params) do
    changeset(%__MODULE__{}, params)
  end

  def changeset(%__MODULE__{} = company, %{} = params) do
    required_fields = [
      :market_cap,
      :name,
      :sector,
      :symbol
    ]

    company
    |> Changeset.cast(params, required_fields)
    |> Changeset.validate_required(required_fields)
    |> Changeset.validate_length(:symbol, max: 5)
    |> Changeset.unique_constraint(:symbol)
  end

  def get_largest(count) do
    query =
      Ecto.Query.from(
        companies in __MODULE__,
        limit: ^count,
        order_by: [desc: companies.market_cap],
        select: companies
      )

    Repo.all(query)
  end

  def upsert(%Changeset{} = changeset) do
    Repo.insert(
      changeset,
      conflict_target: :symbol,
      on_conflict: :replace_all
    )
  end
end
