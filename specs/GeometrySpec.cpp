#include <bandit/bandit.h>
#include "Geometry.h"

using namespace bandit;

go_bandit([](){
  describe("Geometry", []() {
    describe("createGeometryFromFile", []() {
      it("fills indicies, normals and positions buffers", []() {
        Geometry::Ptr geometry = createGeometryFromFile("./specs/assets/triangle.geo");
        AssertThat(geometry->indicies.size(), Equals(3));
        AssertThat(geometry->normals.size(), Equals(9));
        AssertThat(geometry->positions.size(), Equals(9));
        
        std::vector<float> indicies{0, 1, 2};
        std::vector<float> positions{0, 1, 0, 1, 0, 0, .5, .5, 0};
        std::vector<float> normals{1, 0, 0, 1, 0, 0, 0, 1, 0};

        AssertThat(geometry->indicies, EqualsContainer(indicies));
        AssertThat(geometry->positions, EqualsContainer(positions));
        AssertThat(geometry->normals, EqualsContainer(normals));
      });
    });
  });
});