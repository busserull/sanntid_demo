# This file is responsible for configuring your application
# and its dependencies with the aid of the Mix.Config module.
#
# This configuration file is loaded before any dependency and
# is restricted to this project.
use Mix.Config

# General application configuration
config :blink_server,
  namespace: Blink

# Configures the endpoint
config :blink_server, BlinkWeb.Endpoint,
  url: [host: "localhost"],
  secret_key_base: "2Y1Zp+LC5cLxF05Qu2rp0GUzIa6rUH3EqCFIHxygW32SQQUWtnS0HITXxPOcvL/o",
  render_errors: [view: BlinkWeb.ErrorView, accepts: ~w(html json)],
  pubsub: [name: Blink.PubSub,
           adapter: Phoenix.PubSub.PG2]

# Configures Elixir's Logger
config :logger, :console,
  format: "$time $metadata[$level] $message\n",
  metadata: [:user_id]

# Import environment specific config. This must remain at the bottom
# of this file so it overrides the configuration defined above.
import_config "#{Mix.env}.exs"
