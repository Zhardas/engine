#include "scene.h"

Scene::Scene() {
  camera_ = new Camera();
}

Scene::~Scene() {
  while (!layers_.empty()) delete layers_.front(), layers_.pop_front();
}

void Scene::Update() {
  CheckCollision();
}

void Scene::CheckCollision() {
  for(Collidable* collider : collidables_){
    for(Collidable* collidable : collidables_){
      if (collider != collidable) {
        collider->Collide(*collidable);
      }
    }
  }
}

void Scene::EventCall(Event event, uint8_t key, Position *parameter) {
  Position pos;
  if (event == Event::MOUSE_DOWN || event == Event::MOUSE_UP || event == Event::MOUSE_MOVE) {
    pos = *parameter;
    pos.x += camera_->position_.x;
    pos.y += camera_->position_.y;
  }
  for (std::list<Layer *>::reverse_iterator rit = layers_.rbegin(); rit != layers_.rend(); ++rit) {
    auto layer = static_cast<Layer *>(*rit);
    if (layer->EventCall(event, key, &pos)) {
      return;
    }
  }
}