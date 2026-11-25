#include "inspection/inspection.hpp"

namespace inspection {
bool meets_threshold(unsigned score, unsigned minimum) noexcept {
    return score >= minimum;
}
}
