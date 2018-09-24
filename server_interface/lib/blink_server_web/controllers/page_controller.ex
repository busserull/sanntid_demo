defmodule BlinkWeb.PageController do
  use BlinkWeb, :controller

  def index(conn, _params) do
    render conn, "index.html"
  end
end
