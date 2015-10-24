#include "client.h"

Client::~Client() {
  enet_host_destroy(client_);
  enet_deinitialize();
}
bool Client::Initialize(const char *host, enet_uint16 port) {
  // Initialize enet
  if (enet_initialize() != 0) {
    // fprintf(stderr, "An error occured while initializing ENet.\n");
    return false;
  }

  // Create a host using enet_host_create
  client_ = enet_host_create(NULL, 1, 2, 57600 / 8, 14400 / 8);

  if (client_ == NULL) {
    // fprintf(stderr, "An error occured while trying to create an ENet server host\n");
    return false;
  }

  enet_address_set_host(&address_, host);
  address_.port = port;

  // Connect and user service
  peer_ = enet_host_connect(client_, &address_, 2, 0);

  if (peer_ == NULL) {
    return false;
  }

  is_initialized_ = true;
  return true;
}
void Client::Update() {
  if (!is_initialized_)return;
//  event_status_ = enet_host_service(client_, &event_, 50000);
  event_status_ = enet_host_service(client_, &event_, 0);

  // If we had some event that interested us
  if (event_status_ > 0) {
    switch (event_.type) {
      case ENET_EVENT_TYPE_CONNECT:
        std::cout << "\nConnected to server! " << event_.peer->address.host << ":" << event_.peer->address.port;
        connected_ = true;
        break;

      case ENET_EVENT_TYPE_RECEIVE:
        if(Game::instance()->scene_)Game::instance()->scene_->Parse(event_.packet);
        enet_packet_destroy(event_.packet);
        break;

      case ENET_EVENT_TYPE_DISCONNECT:
        std::cout << "\nServer disconnected! " << event_.peer->data;
        connected_ = false;
        // printf("(Client) %s disconnected.\n", reinterpret_cast<char *>(event.peer->data));

        // Reset client's information
        event_.peer->data = NULL;
        break;
      case ENET_EVENT_TYPE_NONE:
        break;
    }
  }
}
void Client::Send(const char *message) {
  if (strlen(message) <= 0)return;
  ENetPacket *packet = enet_packet_create(message, strlen(message) + 1, ENET_PACKET_FLAG_RELIABLE);
  enet_peer_send(peer_, 0, packet);
}
void Client::Send(uint8_t *data, size_t length) {
  ENetPacket *packet = enet_packet_create(data, length, ENET_PACKET_FLAG_RELIABLE);
  enet_peer_send(peer_, 0, packet);
}