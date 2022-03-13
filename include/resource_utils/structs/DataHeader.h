#ifndef RESOURCE_UTILS_DATA_HEADER_H_
#define RESOURCE_UTILS_DATA_HEADER_H_

// System headers
#include <cstdint>
#include <string>

// Other libraries headers

// Own components headers

// Forward declarations

// Common header for resources/fonts/sounds specific data
struct DataHeader {
  DataHeader();

  void reset();

  int32_t fileSize;  // in kBytes
  uint64_t hashValue;
  std::string path;
};


#endif /* RESOURCE_UTILS_DATA_HEADER_H_ */
