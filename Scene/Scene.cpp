#include "scene.h"

Scene::Scene() {
  camera_ = new Camera();
}

Scene::~Scene() {
  while (!layers_.empty()) delete layers_.front(), layers_.pop_front();
}

void Scene::Update() {
  for (auto layer : layers_) {
    for (auto obj : layer->drawable_list_) {
      // Complex object layer reload check
      if(layer->type() == Layer::STATIC && !layer->reload_){
        if(auto complex = dynamic_cast<Complex*>(obj)){
          if(complex->reload_layer_){
            layer->reload_ = true;
            complex->reload_layer_ = false;
          }
        }
      }

      // Update
      if(auto updatable = dynamic_cast<Updatable*>(obj)){
        updatable->Update();
      }

      // Collision
      CheckCollision(obj);
    }
  }
}

void Scene::CheckCollision(Drawable *drawable) {
  if (auto collider = dynamic_cast<Collider *>(drawable)) {
    for (auto collide_layer : layers_) {
      for (Drawable *collide_obj : collide_layer->drawable_list_) {
        if (Collidable *collidable = dynamic_cast<Collidable *>(collide_obj)) {
          collider->Collide(collidable);
        }
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