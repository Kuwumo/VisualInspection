#include "inspection/inspection.hpp"

int main() {
    using inspection::meets_threshold;
    return meets_threshold(79, 80) || !meets_threshold(80, 80) ||
           !meets_threshold(81, 80);
}
