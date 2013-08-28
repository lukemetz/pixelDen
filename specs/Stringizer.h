#include <bandit/bandit.h>
#include <glm/glm.hpp>
#include <sstream>

using namespace bandit;

namespace snowhouse {
  template<>
  struct Stringizer <glm::vec4>
  {
    static std::string ToString(const glm::vec4& value)
    {
      std::stringstream ss;
      ss << "glm::vec3(";
      ss << value[0] << ", " << value[1] << ", " << value[2] << ", " << value[3];
      ss << ")";
      return ss.str();
    }
  };
};
