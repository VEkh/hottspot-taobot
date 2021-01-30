# NOTE: Untested
defmodule HottspotCapital.CppClient do
  @build_directory Path.expand("../../../../cpp/sandbox/build", __ENV__.file)

  def execute(cmd, args \\ []) do
    full_cmd = Path.expand(cmd, @build_directory)

    case System.cmd(full_cmd, args) do
      {response, 0} -> {:ok, response}
      {response, _} -> {:error, response}
    end
  end
end
