// Corresponding header
#include "resource_utils/structs/CombinedStructs.h"

// C system headers

// C++ system headers

// Other libraries headers

// Own components headers

CombinedData::CombinedData() : fontSize(0), textureLoadType(0) {

}

void CombinedData::reset() {
  header.reset();
  fontSize = 0;
  textureLoadType = 0;
  soundType.clear();
  soundLevel.clear();
  tagName.clear();
  type.clear();
  imageRect = Rectangle::ZERO;
  spriteData.clear();
}
