// Corresponding header
#include "resource_utils/structs/DataHeader.h"

// C system headers

// C++ system headers

// Other libraries headers

// Own components headers

DataHeader::DataHeader() : fileSize(0), hashValue(0) {

}

void DataHeader::reset() {
    fileSize = 0;
    hashValue = 0;
    path.clear();
}
