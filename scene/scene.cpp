#include "./scene.h"

void Scene::Update() {
  for (const auto &layer : layers_) {
    for (const auto &obj : layer->drawable_list_) {
      // Update
      obj->Update();
      // Collision
      CheckCollision(obj.get());
    }
    layer->drawable_list_.remove_if([](const std::unique_ptr<Drawable> &obj) {
      return obj->remove_;
    });
  }
}

void Scene::CheckCollision(Drawable *collider) {
  if (collider->type_ == 0)return;
  for (const auto &collide_layer : layers_) {
    for (const auto &collidable : collide_layer->drawable_list_) {
      if (collidable->type_ > 0)collider->Collide(collidable.get());
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
  for (auto rit = layers_.rbegin();
       rit != layers_.rend(); ++rit) {
    if (rit->get()->EventCall(event, key, pos))return;
  }
}
void Scene::RemoveLayer(Layer *layer) {
  layers_.remove_if([layer](const auto &ptr) {
    return ptr.get() == layer;
  });
}
void Scene::AddLayer(Layer *layer) {
  layers_.push_back(std::unique_ptr<Layer>(layer));
}
