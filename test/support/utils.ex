defmodule HottspotCapital.Test.Utils do
  def with_env(app, key, options, fun) do
    old_values = Application.get_env(app, key)
    new_values = Keyword.merge(old_values, options)

    Application.put_env(app, key, new_values)

    try do
      fun.()
    after
      Application.put_env(app, key, old_values)
    end
  end
end
