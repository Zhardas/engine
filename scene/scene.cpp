#include "./scene.h"

Scene::Scene() {
  camera_ = new Camera();
}

void Scene::Update() {
  for (auto layer : layers_) {
    std::list<std::shared_ptr<Drawable>> remove_list;
    bool remove = false;
    for (auto obj : layer->drawable_list_) {
      // Update
      obj->Update();
      // Collision
      //CheckCollision(obj);
      // Remove check
      if (obj->remove_) {
        remove_list.push_back(obj);
        remove = true;
      }
    }
    if (remove) {
      for (auto drawable : remove_list) {
        layer->Remove(drawable);
      }
    }
  }
}

void Scene::CheckCollision(std::shared_ptr<Drawable> collider) {
  for (auto collide_layer : layers_) {
    for (auto collidable : collide_layer->drawable_list_) {
      collider->Collide(collidable);
    }
  }
}

bool Scene::MouseUp(const uint8_t &parameter, const Position &position) {
  for (auto func : events_mouse_up_) {
    if (func(parameter, position))return true;
  }
  return false;
}
bool Scene::MouseDown(const uint8_t &parameter, const Position &position) {
  for (auto func : events_mouse_down_) {
    if (func(parameter, position))return true;
  }
  return false;
}
bool Scene::MouseMove(const Position &position) {
  for (auto func : events_mouse_move_) {
    if (func(position))return true;
  }
  return false;
}
bool Scene::KeyUp(const uint8_t &parameter) {
  for (auto func : events_key_up_) {
    if (func(parameter))return true;
  }
  return false;
}
bool Scene::KeyDown(const uint8_t &parameter) {
  for (auto func : events_key_down_) {
    if (func(parameter))return true;
  }
  return false;
}

void Scene::EventCall(Event event, uint8_t key, Position *parameter) {
  Position pos;
  if (event == Event::MOUSE_DOWN
      || event == Event::MOUSE_UP
      || event == Event::MOUSE_MOVE) {
    pos = *parameter;
    pos.x += camera_->position_.x;
    pos.y += camera_->position_.y;
  }
  switch (event) {
    case MOUSE_UP: {
      if (MouseUp(key, pos)) {
        return;
      }
      break;
    }
    case MOUSE_DOWN: {
      if (MouseDown(key, pos)) {
        return;
      }
      break;
    }
    case MOUSE_MOVE: {
      if (MouseMove(pos)) {
        return;
      }
      break;
    }
    case KEYBOARD_UP: {
      if (KeyUp(key)) {
        return;
      }
      break;
    }
    case KEYBOARD_DOWN: {
      if (KeyDown(key)) {
        return;
      }
      break;
    }
  }
  for (std::list<std::shared_ptr<Layer>>::reverse_iterator rit = layers_.rbegin();
       rit != layers_.rend(); ++rit) {
    if (static_cast<std::shared_ptr<Layer>>(*rit)->EventCall(event, key, pos))return;
  }
}
