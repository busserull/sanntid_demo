defmodule Blink.UART do
  use GenServer

  @uart_interface "ttyACM0"
  @led_on 0x01
  @stx 0x02
  @etx 0x03

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

  def update_state(new_state) do
    GenServer.call(__MODULE__, {:update, new_state |> Enum.map(&(&1 == @led_on))})
  end

  # Callbacks

  def init(:ok) do
    {:ok, uart_pid} = Nerves.UART.start_link()
    Nerves.UART.open(uart_pid, @uart_interface, speed: 9600, active: false)
    Task.start_link(__MODULE__, :poll_microcontroller, [uart_pid, []])

    {:ok, Enum.map(1..25, fn _ -> false end)}
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

  def handle_call({:update, new_state}, _from, _state) do
    BlinkWeb.LEDChannel.trigger_led_broadcast(new_state)
    {:reply, :ok, new_state}
  end

  # Helpers

  def poll_microcontroller(uart_pid, read) do
    bytes_read = Enum.count(read)

    cond do
      bytes_read > 25 ->
        poll_microcontroller(uart_pid, [])

      bytes_read == 25 ->
        update_state(read)
        poll_microcontroller(uart_pid, [])

      bytes_read == 0 ->
        message = read_from_uart(uart_pid)
        {_head, tail} = split_at(message, @stx)
        {head, _tail} = split_at(tail, @etx)
        poll_microcontroller(uart_pid, head)

      true ->
        message = read_from_uart(uart_pid)
        {head, _tail} = split_at(message, @etx)
        poll_microcontroller(uart_pid, read ++ head)
    end
  end

  def read_from_uart(uart_pid) do
    {:ok, raw_message} = Nerves.UART.read(uart_pid, 20)
    :erlang.binary_to_list(raw_message)
  end

  def split_at(message, delimiter) do
    case Enum.split_while(message, &(&1 != delimiter)) do
      {head, []} ->
        {head, []}
      {head, tail} ->
        {head, tl(tail)}
    end
  end

end
