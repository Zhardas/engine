#include <helper/types.h>

class Camera;
#ifndef OVERLORD_CAMERA_H
#define OVERLORD_CAMERA_H


class Camera {
 private:
 public:
  Position3 position_{0.0f, 0.0f, 0.0f};
  float zoom_ = 1.0f;

  Camera();
};


#endif //OVERLORD_CAMERA_H
