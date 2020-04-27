// Corresponding header
#include "resource_utils/structs/ResourceData.h"

// C system headers

// C++ system headers

// Other libraries headers

// Own components headers

ResourceData::ResourceData()
    : textureLoadType(0), refCount(0) {
}

// piecewise constructor - used for emplace_back move semantics
ResourceData::ResourceData(const DataHeader &inputHeader,
                           const Rectangle &inputRect,
                           const std::vector<Rectangle> &inputSpriteData,
                           const int32_t inputTextureLoadType,
                           const int32_t inputRefCount)
    : header(inputHeader), imageRect(inputRect), spriteData(inputSpriteData),
      textureLoadType(inputTextureLoadType), refCount(inputRefCount) {
}

void ResourceData::reset() {
  header.reset();
  imageRect = Rectangle::ZERO;
  spriteData.clear();
  textureLoadType = 0;
  refCount = 0;
}
