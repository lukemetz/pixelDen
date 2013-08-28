#include <bandit/bandit.h>

#include "Stringizer.h"
#include "CameraControls.h"
#include "Camera.h"

using namespace bandit;

go_bandit([]() {
  describe("CameraControls",[]() {
    Camera::Ptr camera = 0;
    before_each([&]() {
      camera = createCamera();
    });
    describe("panHorizontal", [&]() {
      it("pans the camera side to side", [&]() {
        float delta = 3;
        float scale = 0.5f;
        CameraControls::panHorizontal(camera, delta, scale);
        glm::vec4 newPos = camera->view * glm::vec4(0, 0, 0, 1);
        AssertThat(newPos, Equals(glm::vec4(1.5f, 0, 0, 1)));
      });
    });
    describe("panInto", [&]() {
      it("moves the camera in and out", [&]() {
        float delta = 3;
        float scale = 0.5f;
        CameraControls::panInto(camera, delta, scale);
        glm::vec4 newPos = camera->view * glm::vec4(0, 0, 0, 1);
        AssertThat(newPos, Equals(glm::vec4(0, 0, 1.5f, 1)));
      });
    });
  });
});
