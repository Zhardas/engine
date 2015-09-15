#include <Helper/types.h>

class Camera;
#ifndef OVERLORD_CAMERA_H
#define OVERLORD_CAMERA_H


class Camera {
private:
public:
    Position3 position_;
    float zoom_ = 1.0f;

    Camera();
};


#endif //OVERLORD_CAMERA_H
