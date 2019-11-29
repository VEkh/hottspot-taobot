defmodule HottspotCapital.Test.UtilsTest do
  use ExUnit.Case

  alias HottspotCapital.Utils

  describe ".previous_weekdate" do
    test "returns previous weekdate" do
      assert Utils.previous_weekdate(~D[2019-10-21]) == ~D[2019-10-18]
    end
  end

  describe ".update_in_and_build" do
    test "builds empty map" do
      subject = %{}

      assert Utils.update_in_and_build(
               subject,
               [:a, :b, :c]
             ) == %{a: %{b: :c}}
    end

    test "handles mixed atom and string keys" do
      subject = %{}

      assert Utils.update_in_and_build(
               subject,
               [:a, "b", :c]
             ) == %{a: %{"b" => :c}}
    end

    test "map is unaltered" do
      subject = %{a: %{b: :c}}

      assert Utils.update_in_and_build(subject, []) == subject
      assert Utils.update_in_and_build(subject, [:a]) == subject
      assert Utils.update_in_and_build(subject, [:b]) == subject

      subject = %{a: :b}

      assert Utils.update_in_and_build(subject, []) == subject
      assert Utils.update_in_and_build(subject, [:a]) == subject
      assert Utils.update_in_and_build(subject, [:c]) == subject
    end

    test "updates map with existing values" do
      subject = %{a: :b}

      assert Utils.update_in_and_build(
               subject,
               [:a, :b, :c]
             ) == %{a: %{b: :c}}

      subject = %{a: %{b: %{c: :d}}}

      assert Utils.update_in_and_build(
               subject,
               [:a, :b, :c]
             ) == %{a: %{b: :c}}

      subject = %{a: [1, 2, 3]}

      assert Utils.update_in_and_build(
               subject,
               [:a, :b, :c]
             ) == %{a: %{b: :c}}

      subject = %{a: %{b: {:ok, :dokie}}}

      assert Utils.update_in_and_build(
               subject,
               [:a, :b, :c]
             ) == %{a: %{b: :c}}

      subject = %{
        a: %{
          b: %{c: %{d: "e"}},
          d: [1, 2, 3]
        },
        x: %{y: %{z: "alpha"}}
      }

      assert Utils.update_in_and_build(
               subject,
               [:a, :b, :c]
             ) == %{
               a: %{
                 b: :c,
                 d: [1, 2, 3]
               },
               x: %{y: %{z: "alpha"}}
             }
    end
  end
end
