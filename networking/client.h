#ifndef NETWORKING_CLIENT_H_
#define NETWORKING_CLIENT_H_

#include <enet/enet.h>
#include <string>
#include <iostream>

class Client {
 private:
  ENetAddress address_;
  ENetHost *client_ = nullptr;
  ENetPeer *peer_ = nullptr;
  ENetEvent event_;
  int event_status_ = 1;
  bool is_initialized_ = false;
 public:
  Client() { }
  ~Client();
  bool Initialize(const char *host, enet_uint16 port);
  void Update();
  void Send(const char *message);
};

#endif  // NETWORKING_CLIENT_H_
