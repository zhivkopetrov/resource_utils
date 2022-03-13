#ifndef RESOURCE_UTILS_FONT_DATA_H_
#define RESOURCE_UTILS_FONT_DATA_H_

// System headers
#include <cstdint>
#include <string>

// Other libraries headers

// Own components headers
#include "resource_utils/structs/DataHeader.h"

// Forward declarations

struct FontData {
  FontData();

  // piecewise constructor - used for emplace_back move semantics
  FontData(const DataHeader& inputHeader, const int32_t inputFontSize);

  void reset();

  DataHeader header;
  int32_t fontSize;
};

#endif /* RESOURCE_UTILS_FONT_DATA_H_ */
