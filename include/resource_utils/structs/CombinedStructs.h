#ifndef RESOURCE_UTILS_COMBINEDSTRUCTS_H_
#define RESOURCE_UTILS_COMBINEDSTRUCTS_H_

// System headers
#include <cstdint>
#include <string>
#include <vector>

// Other libraries headers
#include "utils/drawing/Rectangle.h"

// Own components headers
#include "resource_utils/structs/DataHeader.h"

// Forward declarations

// combination of ResourceData + FontData + SoundData
// this struct is used for parsing the individual .rsrc files
// from resourceBuilderTool
struct CombinedData {
  CombinedData();

  void reset();

  DataHeader header;
  int32_t fontSize;
  int32_t textureLoadType;
  std::string soundType;
  std::string soundLevel;
  std::string tagName;
  std::string type;
  Rectangle imageRect;
  std::vector<Rectangle> spriteData;
};

#endif /* RESOURCE_UTILS_COMBINEDSTRUCTS_H_ */
