#include <cstdint>

// for TASK_3
static std::uint64_t get_current_time() {
    static std::uint64_t current_time = 0;
    return current_time++;
}
