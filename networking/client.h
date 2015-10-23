class Client;
#ifndef NETWORKING_CLIENT_H_
#define NETWORKING_CLIENT_H_

#include <enet/enet.h>
#include <scene/scene.h>
#include <string>
#include <iostream>
#include <functional>
#include <map>

class Client {
 private:
  ENetAddress address_;
  ENetHost *client_ = nullptr;
  ENetPeer *peer_ = nullptr;
  ENetEvent event_;
  int event_status_ = 1;
  bool is_initialized_ = false;
  Scene *parent_ = nullptr;
 public:
  bool connected_ = false;

  Client() { }
  ~Client();
  bool Initialize(Scene *scene, const char *host, enet_uint16 port);
  void Update();
  void Send(const char *message);
  void Send(uint8_t *data, size_t length);
};

#endif  // NETWORKING_CLIENT_H_
