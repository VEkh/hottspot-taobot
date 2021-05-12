#include "lib/websockets_client/websockets_client.cpp" // LibWebSocketsClient
#include <iostream>

int main() {
  WebSocketsClient client("wss://stream.data.alpaca.markets/v2/iex");
  client.connect();
}
