#include <Utility/UUID.h>

static std::random_device              rd;
static std::mt19937                    gen(rd());
static std::uniform_int_distribution<> distribution(0, 15);
static std::uniform_int_distribution<> distribution2(8, 11);

namespace UUID
{
    // xxxxxxxx-xxxx-Mxxx-Nxxx-xxxxxxxxxxxx, where M is 4 (as UUIDv4) and N is variant (variant 1-2 for me)
    std::string Generate_UUID_V4() {
        std::stringstream ss;
        int i;
        ss << std::hex;
        for (i = 0; i < 8; i++) {
            ss << distribution(gen);
        }
        ss << "-";
        for (i = 0; i < 4; i++) {
            ss << distribution(gen);
        }
        ss << "-4"; // UUID version
        for (i = 0; i < 3; i++) {
            ss << distribution(gen);
        }
        ss << "-";
        ss << distribution2(gen); // UUID variant
        for (i = 0; i < 3; i++) {
            ss << distribution(gen);
        }
        ss << "-";
        for (i = 0; i < 12; i++) {
            ss << distribution(gen);
        };
        return ss.str();
    }
};