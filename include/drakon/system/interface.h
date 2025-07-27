#include <drakon/error.h>
#include <optional>

namespace drakon {
class System {
public:
  virtual ~System() = default;
  virtual std::optional<Error> process() = 0;
};
} // namespace drakon
