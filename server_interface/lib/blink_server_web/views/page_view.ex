defmodule BlinkWeb.PageView do
  use BlinkWeb, :view

  def format_led_number(led_row, led_col) do
    "#{(led_row - 1) * 5 + led_col}"
    |> String.pad_leading(2, "0")
  end

end
