defmodule BlinkWeb.LEDChannel do
  use BlinkWeb, :channel

  def join("led-channel", _params, socket) do
    led_list = %{list: Blink.UART.list_leds()}
    {:ok, led_list, socket}
  end

  def handle_in("led-btn-" <> button_string, _params, socket) do
    led_id = button_string
    |> String.trim_leading("0")
    |> String.to_integer()

    Blink.UART.toggle_led(led_id - 1)

    push_update(socket)

    {:reply, :ok, socket}
  end

  def push_update(socket) do
    broadcast!(socket, "render_leds", %{
      list: Blink.UART.list_leds()
    })
  end

end
