#ifndef RESOURCE_UTILS_RESOURCES_DATA_H_
#define RESOURCE_UTILS_RESOURCES_DATA_H_

// C system headers

// C++ system headers
#include <cstdint>
#include <vector>

// Other libraries headers

// Own components headers
#include "resource_utils/structs/DataHeader.h"
#include "utils/drawing/Rectangle.h"

// Forward declarations

struct ResourceData {
  ResourceData();

  // piecewise constructor - used for emplace_back move semantics
  ResourceData(const DataHeader& inputHeader, const Rectangle& inputRect,
               const std::vector<Rectangle>& inputSpriteData,
               const int32_t inputTextureLoadType, const int32_t inputRefCount);

  void reset();

  DataHeader header;
  Rectangle imageRect;
  std::vector<Rectangle> spriteData;
  int32_t textureLoadType;
  int32_t refCount;
};

#endif /* RESOURCE_UTILS_RESOURCES_DATA_H_ */
