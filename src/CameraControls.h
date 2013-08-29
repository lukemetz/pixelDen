#include "Camera.h"

namespace CameraControls
{
  void panHorizontal(Camera::Ptr camera, float amount);
  void panInto(Camera::Ptr camera, float amount);
  void rotateHorizontal(Camera::Ptr camera, float amount);
  void rotateVertical(Camera::Ptr camera, float amount);
};
