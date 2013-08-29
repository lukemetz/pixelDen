#include <bandit/bandit.h>

#include "Stringizer.h"
#include "CameraControls.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace bandit;

go_bandit([]() {
  describe("CameraControls",[]() {
    Camera::Ptr camera = 0;
    before_each([&]() {
      camera = createCamera();
    });
    describe("panHorizontal", [&]() {
      it("pans the camera side to side", [&]() {
        float amount = 1.5f;
        CameraControls::panHorizontal(camera, amount);
        glm::vec4 newPos = camera->view * glm::vec4(0, 0, 0, 1);
        AssertThat(newPos, Equals(glm::vec4(1.5f, 0, 0, 1)));
      });
    });
    describe("panInto", [&]() {
      it("moves the camera in and out", [&]() {
        float amount = 1.5f;
        CameraControls::panInto(camera, amount);
        glm::vec4 newPos = camera->view * glm::vec4(0, 0, 0, 1);
        AssertThat(newPos, Equals(glm::vec4(0, 0, 1.5f, 1)));
      });
    });
    describe("rotateHorizontal", [&]() {
      it("rotate the camera around the horizontal", [&]() {
        float amount = 1.5f;
        CameraControls::rotateHorizontal(camera, amount);
        glm::vec4 newPos = camera->view * glm::vec4(0, 0, 0, 1);
        AssertThat(newPos, Equals(glm::vec4(0, 0, 0, 1)));
      });
    });
  });
});
