defmodule Blink.UART do
  use GenServer

  # Public API

  def start_link(_opts) do
    GenServer.start_link(__MODULE__, :ok, [name: __MODULE__])
  end

  def toggle_led(led_number) do
    GenServer.call(__MODULE__, {:toggle, led_number})
  end

  # Callbacks

  def init(:ok) do
    IO.puts("Blink.UART starting")
    {:ok, Enum.map(1..25, fn _val -> :off end)}
  end

  def handle_call({:toggle, led_number}, _from, state) do
    IO.puts("Got a call with LED number #{led_number}")

    new_state = case state |> Enum.at(led_number) do
      :off ->
        state |> List.replace_at(led_number, :on)
      :on ->
        state |> List.replace_at(led_number, :off)
      _ ->
        state
    end

    IO.puts("LED string: #{inspect new_state}")

    {:reply, :ok, new_state}
  end

  # Helpers

end
