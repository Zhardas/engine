class NetworkManager;
#ifndef NETWORKING_NETWORK_MANAGER_H_
#define NETWORKING_NETWORK_MANAGER_H_

#include "client.h"

class NetworkManager {
 private:
  Client *client_ = nullptr;
 public:
  NetworkManager();
  ~NetworkManager();
  Client *client() { return client_; }
  void Update();
};

#endif  // NETWORKING_NETWORK_MANAGER_H_
