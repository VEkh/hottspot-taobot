defmodule HottspotCapital.SQLQueryParserTest do
  use ExUnit.Case

  alias HottspotCapital.SQLQueryParser

  describe ".named_to_ordered_params" do
    test "converts named params to ordered params" do
      subject = "select * from users where name = $name and email = $email"

      assert SQLQueryParser.named_to_ordered_params(
               subject,
               name: "Kanye West",
               email: "me@example.com"
             ) ==
               {
                 "select * from users where name = $1 and email = $2",
                 ["Kanye West", "me@example.com"]
               }
    end
  end
end
