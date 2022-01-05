// Corresponding header
#include "resource_utils/structs/FontData.h"

// C system headers

// C++ system headers

// Other libraries headers

// Own components headers

FontData::FontData() : fontSize(0) {

}

FontData::FontData(const DataHeader& inputHeader, const int32_t inputFontSize)
    : header(inputHeader),
      fontSize(inputFontSize) {

}

void FontData::reset() {
  header.reset();
  fontSize = 0;
}
