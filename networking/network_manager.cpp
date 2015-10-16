#include "network_manager.h"

NetworkManager::NetworkManager() {
  client_ = new Client();
}

NetworkManager::~NetworkManager() {
  delete client_;
}
void NetworkManager::Update() {
  client_->Update();
}
