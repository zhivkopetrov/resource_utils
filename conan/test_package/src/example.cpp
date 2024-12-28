// System headers
#include <cstdint>
#include <iostream>

// Other libraries headers
#include "resource_utils/common/ResourceFileHeader.h"

// Own components headers

int32_t main() {
    std::cout << ResourceFileHeader::getEngineResHeader();

    return EXIT_SUCCESS;
}
