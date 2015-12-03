#include "./scene.h"

Scene::Scene() {
  camera_ = new Camera();
}

bool Scene::CheckComplexReload(Complex *obj) {
  auto reload = false;
  if (obj->reload_layer_) {
    obj->reload_layer_ = false;
    reload = true;
  }
  for (auto drawable : obj->complex_list_) {
    if (auto complex = dynamic_cast<Complex *>(drawable)) {
      if (CheckComplexReload(complex)) {
        reload = true;
      }
    }
  }
  return reload;
}

void Scene::Update() {
  for (auto layer : layers_) {
    for (auto obj : layer->drawable_list_) {
      // Complex object layer reload check
      if (layer->type() == Layer::STATIC && !layer->reload_) {
        if (auto complex = dynamic_cast<Complex *>(obj)) {
          if (CheckComplexReload(complex)) {
            layer->reload_ = true;
          }
        }
      }
      // Update
      obj->Update();
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
  if (event == Event::MOUSE_DOWN
      || event == Event::MOUSE_UP
      || event == Event::MOUSE_MOVE) {
    pos = *parameter;
    pos.x += camera_->position_.x;
    pos.y += camera_->position_.y;
  }
  switch (event) {
    case MOUSE_UP: {
      if (MouseUp(key, parameter)) {
        return;
      }
      break;
    }
    case MOUSE_DOWN: {
      if (MouseDown(key, parameter)) {
        return;
      }
      break;
    }
    case MOUSE_MOVE: {
      if (MouseMove(parameter)) {
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
  std::for_each(layers_.rbegin(), layers_.rend(), [&event, &key, &pos](Layer *layer) {
    if (layer->EventCall(event, key, &pos)) {
      return;
    }
  });
}
