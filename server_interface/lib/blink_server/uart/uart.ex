defmodule Blink.UART do
  use GenServer

  # Public API

  def start_link(_opts) do
    GenServer.start_link(__MODULE__, :ok, [name: __MODULE__])
  end

  def toggle_led(led_number) do
    GenServer.call(__MODULE__, {:toggle, led_number})
  end

  def list_leds() do
    GenServer.call(__MODULE__, :list)
  end

  # Callbacks

  def init(:ok) do
    {:ok, Enum.map(1..25, fn _val -> :off end)}
  end

  def handle_call({:toggle, led_number}, _from, state) do
    new_state = case state |> Enum.at(led_number) do
      :off ->
        state |> List.replace_at(led_number, :on)
      :on ->
        state |> List.replace_at(led_number, :off)
      _ ->
        state
    end

    {:reply, :ok, new_state}
  end

  def handle_call(:list, _from, state) do
    {:reply, state, state}
  end

end
