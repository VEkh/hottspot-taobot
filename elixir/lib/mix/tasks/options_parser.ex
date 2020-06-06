defmodule Mix.Tasks.OptionsParser do
  def parse(args) do
    %{
      defaults: defaults,
      options: options,
      permitted: permitted,
      task_name: task_name
    } = args

    options
    |> Enum.reduce(defaults, fn option, acc ->
      parts = String.split(option, ["--", "="], trim: true)

      with [key, value] <- parts,
           true <- key in permitted do
        Map.put(acc, key, value)
      else
        _ ->
          error_message = "Invalid args #{options}. Run mix help #{task_name} for help."

          raise(ArgumentError, message: error_message)
      end
    end)
  end
end
