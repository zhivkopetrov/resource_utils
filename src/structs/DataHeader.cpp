// Corresponding header
#include "resource_utils/structs/DataHeader.h"

// System headers

// Other libraries headers

// Own components headers

DataHeader::DataHeader() : fileSize(0), hashValue(0) {

}

void DataHeader::reset() {
    fileSize = 0;
    hashValue = 0;
    path.clear();
}
