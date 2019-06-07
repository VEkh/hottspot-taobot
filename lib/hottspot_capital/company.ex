defmodule HottspotCapital.Company do
  use Ecto.Schema

  alias Ecto.Changeset
  alias HottspotCapital.Repo

  @primary_key {:symbol, :string, autogenerate: false}

  schema "companies" do
    field(:company_name, :string)
    field(:inserted_at, :utc_datetime)
    field(:market_cap, :integer)
    field(:updated_at, :utc_datetime)
  end

  def changeset(%{} = params) do
    changeset(%__MODULE__{}, params)
  end

  def changeset(%__MODULE__{} = company, %{} = params) do
    required_fields = [
      :company_name,
      :market_cap,
      :symbol
    ]

    company
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
