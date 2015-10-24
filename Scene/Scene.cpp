#include "scene.h"

Scene::Scene() {
  camera_ = new Camera();
}

bool Scene::CheckComplexReload(Complex* obj){
  if(obj->reload_layer_){
    obj->reload_layer_ = false;
    return true;
  }
  for(auto drawable : obj->complex_list_){
    if(auto complex = dynamic_cast<Complex*>(drawable)){
      if(CheckComplexReload(complex)){
        return true;
      }
    }
  }
  return false;
}

void Scene::Update() {
  for (auto layer : layers_) {
    for (auto obj : layer->drawable_list_) {
      // Complex object layer reload check
      if (layer->type() == Layer::STATIC && !layer->reload_) {
        if (auto complex = dynamic_cast<Complex *>(obj)) {
          if(CheckComplexReload(complex)){
            layer->reload_ = true;
          }
        }
      }
      // Update
      if (auto updatable = dynamic_cast<Updatable *>(obj)) {
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
