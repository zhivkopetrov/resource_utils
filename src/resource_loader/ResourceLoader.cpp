// Corresponding header
#include "resource_utils/resource_loader/ResourceLoader.h"

// C system headers

// C++ system headers
#include <cstring>
#include <sstream>

// Other libraries headers

// Own components headers
#include "resource_utils/structs/ResourceData.h"
#include "resource_utils/structs/FontData.h"
#include "resource_utils/structs/SoundData.h"
#include "resource_utils/common/ResourceFileHeader.h"
#include "utils/data_type/StringUtils.h"
#include "utils/ErrorCode.h"
#include "utils/Log.h"

int32_t ResourceLoader::init(const std::string &resourcesBinLocation) {
  if (SUCCESS != openSourceStreams(resourcesBinLocation)) {
    LOGERR("Error in ResourceLoader::openSourceStream() -> Terminating...");
    LOGC("Developer hint: Run the resourcebuilder tool in the project /build "
         "directory and make before starting engine");
    return FAILURE;
  }

  return SUCCESS;
}

int32_t ResourceLoader::readEngineBinHeaders(EgnineBinHeadersData& outData) {
  if (SUCCESS != readResourceBinHeader(outData.staticWidgetsCount,
                                            outData.dynamicWidgetsCount,
                                            outData.widgetsFileSize)) {
    LOGERR("Error in readResourceBinHeader()");
    return FAILURE;
  }

  if (SUCCESS !=
      readFontBinHeader(outData.fontsCount, outData.fontsFileSize)) {
    LOGERR("Error in readFontBinHeader()");
    return FAILURE;
  }

  if (SUCCESS != readSoundBinHeader(outData.musicsCount,
                                         outData.chunksCount,
                                         outData.soundsFileSize)) {
    LOGERR("Error in readSoundBinHeader()");
    return FAILURE;
  }

  return SUCCESS;
}

int32_t ResourceLoader::openSourceStreams(
    const std::string &resourcesBinLocation) {
  const std::string resFile =
      resourcesBinLocation + ResourceFileHeader::getResourceBinName();
  _resSourceStream.open(resFile.c_str(),
                        std::ifstream::in | std::ifstream::binary);
  if (!_resSourceStream) {
    LOGERR("Error, could not open ifstream for fileName: %s, "
           "reason: %s", resFile.c_str(), strerror(errno));
    return FAILURE;
  }

  const std::string fontFile =
      resourcesBinLocation + ResourceFileHeader::getFontBinName();
  _fontsSourceStream.open(fontFile.c_str(),
                          std::ifstream::in | std::ifstream::binary);
  if (!_fontsSourceStream) {
    LOGERR("Error, could not open ifstream for fileName: %s,"
           " reason: %s", fontFile.c_str(), strerror(errno));
    return FAILURE;
  }

  const std::string soundFile =
      resourcesBinLocation + ResourceFileHeader::getSoundBinName();
  _soundsSourceStream.open(soundFile.c_str(),
                           std::ifstream::in | std::ifstream::binary);
  if (!_soundsSourceStream) {
    LOGERR("Error, could not open ifstream for fileName: %s,"
           " reason: %s", soundFile.c_str(), strerror(errno));
    return FAILURE;
  }

  return SUCCESS;
}

int32_t ResourceLoader::readResourceBinHeader(uint64_t& outStaticWidgetsSize,
                                              uint64_t& outDynamicWidgetsSize,
                                              int32_t& outWidgetFileSize) {
  const uint64_t RES_HEADER_SIZE =
      ResourceFileHeader::getEngineResHeader().size();
  const uint64_t ENGINE_RESERVED_SLOT_SIZE =
      ResourceFileHeader::getEngineValueReservedSlot().size();
  const uint64_t RES_HEADER_ADDITION_SIZE =
      ResourceFileHeader::getEngineResHeaderAddition().size();

  // move the file pointer to the proper place
  _resSourceStream.seekg(RES_HEADER_SIZE, std::ifstream::beg);

  std::string line = "";
  if (!std::getline(_resSourceStream, line)) {
    LOGERR("Internal error, Could not parse widgetsCount");
    return FAILURE;
  }

  int32_t parsedArgs = sscanf(line.c_str(), "%lu", &outStaticWidgetsSize);
  if (1 != parsedArgs) {
    LOGERR("Internal error, sscanf parsed %d arguments instead of 1",
        parsedArgs);
    return FAILURE;
  }

  const uint64_t OFFSET = RES_HEADER_SIZE + ENGINE_RESERVED_SLOT_SIZE +
                          RES_HEADER_ADDITION_SIZE +
                          2;  //+2 for the 2 newline characters

  // move the file pointer to the proper place
  _resSourceStream.seekg(OFFSET, std::ifstream::beg);

  if (!std::getline(_resSourceStream, line)) {
    LOGERR("Internal error, Could not parse widgetsCount");
    return FAILURE;
  }

  parsedArgs = sscanf(line.c_str(), "%lu", &outDynamicWidgetsSize);
  if (1 != parsedArgs) {
    LOGERR("Internal error, sscanf parsed %d arguments instead of 1",
        parsedArgs);
    return FAILURE;
  }

  // 3, because we expect 1 newline + 1 line of resource file size header
  // 3th line is the actual data we want to parse with sscanf
  for (int32_t i = 0; i < 3; ++i) {
    if (!std::getline(_resSourceStream, line)) {
      LOGERR("Internal error, not enough data");
      return FAILURE;
    }
  }

  parsedArgs = sscanf(line.c_str(), "%d", &outWidgetFileSize);
  if (1 != parsedArgs) {
    LOGERR("Internal error, sscanf parsed %d arguments instead of 1",
        parsedArgs);
    return FAILURE;
  }

  return SUCCESS;
}

int32_t ResourceLoader::readFontBinHeader(uint64_t& outFontsSize,
                                          int32_t& outFontsFileSize) {
  // move the file pointer to the proper place
  _fontsSourceStream.seekg(ResourceFileHeader::getEngineFontHeader().size(),
                           std::ifstream::beg);
  std::string line = "";
  if (!std::getline(_fontsSourceStream, line)) {
    LOGERR("Internal error, Could not parse fontsCount");
    return FAILURE;
  }

  int32_t parsedArgs = sscanf(line.c_str(), "%lu", &outFontsSize);
  if (1 != parsedArgs) {
    LOGERR("Internal error, sscanf parsed %d arguments instead of 1",
        parsedArgs);
    return FAILURE;
  }

  // 3, because we expect 1 newline + 1 line of fonts file size header
  // 3th line is the actual data we want to parse with sscanf
  for (int32_t i = 0; i < 3; ++i) {
    if (!std::getline(_fontsSourceStream, line)) {
      LOGERR("Internal error, not enough data");
      return FAILURE;
    }
  }

  parsedArgs = sscanf(line.c_str(), "%d", &outFontsFileSize);
  if (1 != parsedArgs) {
    LOGERR("Internal error, sscanf parsed %d arguments instead of 1",
        parsedArgs);
    return FAILURE;
  }

  return SUCCESS;
}

int32_t ResourceLoader::readSoundBinHeader(uint64_t& outMusicsSize,
                                           uint64_t& outChunksSize,
                                           int32_t& outSoundsFileSize) {
  // move the file pointer to the proper place
  _soundsSourceStream.seekg(ResourceFileHeader::getEngineSoundHeader().size(),
                            std::ifstream::beg);

  std::string line = "";
  if (!std::getline(_soundsSourceStream, line)) {
    LOGERR("Internal error, Could not parse soundsCount");
    return FAILURE;
  }

  int32_t parsedArgs = sscanf(line.c_str(), "%lu", &outMusicsSize);
  if (1 != parsedArgs) {
    LOGERR("Internal error, sscanf parsed %d arguments instead of 1",
        parsedArgs);
    return FAILURE;
  }

  // 3, because we expect 1 newline + 1 line of file sound addition header
  // 3th line is the actual data we want to parse with sscanf
  for (int32_t i = 0; i < 3; ++i) {
    if (!std::getline(_soundsSourceStream, line)) {
      LOGERR("Internal error, not enough data");
      return FAILURE;
    }
  }

  parsedArgs = sscanf(line.c_str(), "%lu", &outChunksSize);
  if (1 != parsedArgs) {
    LOGERR("Internal error, sscanf parsed %d arguments instead of 1",
        parsedArgs);
    return FAILURE;
  }

  // 3, because we expect 1 newline + 1 line of sound file size header
  // 3th line is the actual data we want to parse with sscanf
  for (int32_t i = 0; i < 3; ++i) {
    if (!std::getline(_soundsSourceStream, line)) {
      LOGERR("Internal error, not enough data");
      return FAILURE;
    }
  }

  parsedArgs = sscanf(line.c_str(), "%d", &outSoundsFileSize);
  if (1 != parsedArgs) {
    LOGERR("Internal error, sscanf parsed %d arguments instead of 1",
        parsedArgs);
    return FAILURE;
  }

  return SUCCESS;
}

void ResourceLoader::closeSourceStreams() {
  // close the stream and reset stream flags
  _resSourceStream.close();
  _resSourceStream.clear();

  // close the stream and reset stream flags
  _fontsSourceStream.close();
  _fontsSourceStream.clear();

  // close the stream and reset stream flags
  _soundsSourceStream.close();
  _soundsSourceStream.clear();
}

bool ResourceLoader::readChunkHeaderInternal(
    const ResourceDefines::FieldType fieldType, DataHeader& outData) {
  constexpr int32_t HEADER_SIZE = 3;
  std::string lines[HEADER_SIZE];

  std::ifstream* currStream = nullptr;
  if (ResourceDefines::FieldType::FONT == fieldType) {
    currStream = &_fontsSourceStream;
  } else if (ResourceDefines::FieldType::SOUND == fieldType) {
    currStream = &_soundsSourceStream;
  } else  // FieldType::IMAGE == fieldType || FieldType::SPRITE == fieldType
  {
    currStream = &_resSourceStream;
  }

  // there should be 1 empty newline before each widget internal information
  if (!std::getline(*currStream, lines[0]) || lines[0] != "") {
    return false;
  }

  for (int32_t i = 0; i < HEADER_SIZE; ++i) {
    if (!std::getline(*currStream, lines[i])) {
      return false;
    }
  }

  std::stringstream str(lines[0]);
  str >> std::hex >> outData.hashValue;

  outData.path = lines[1];

  outData.fileSize = StringUtils::safeStoi(lines[2]);

  return true;
}

bool ResourceLoader::readResourceChunk(ResourceData& outData) {
  // for now it doesn't matter if we use FieldType::IMAGE or FieldType::SPRITE,
  // because they both have the same headers
  if (!readChunkHeaderInternal(ResourceDefines::FieldType::SPRITE,
                               outData.header)) {
    return false;
  }

  constexpr int32_t RES_SPECIFIC_SIZE = 3;
  std::string lines[RES_SPECIFIC_SIZE];

  for (int32_t i = 0; i < RES_SPECIFIC_SIZE; ++i) {
    if (!std::getline(_resSourceStream, lines[i])) {
      return false;
    }
  }

  outData.textureLoadType = StringUtils::safeStoi(lines[0]);

  std::vector<int32_t> coordsData;
  if (SUCCESS !=
      StringUtils::extractIntsFromString(lines[1], " ", &coordsData, 4)) {
    LOGERR("Internal error, not valid coordsData");
    return false;
  }

  outData.imageRect.x = coordsData[0];
  outData.imageRect.y = coordsData[1];
  outData.imageRect.w = coordsData[2];
  outData.imageRect.h = coordsData[3];

  const int32_t SPRITE_COUNT = StringUtils::safeStoi(lines[2]);

  outData.spriteData.reserve(SPRITE_COUNT);

  std::vector<int32_t> spriteData;
  for (int32_t i = 0; i < SPRITE_COUNT; ++i) {
    // reuse lines[0] string. don't need to create separate one
    if (!std::getline(_resSourceStream, lines[0])) {
      return false;
    }

    if (SUCCESS !=
        StringUtils::extractIntsFromString(lines[0], " ", &spriteData, 4)) {
      LOGERR("Internal error, not valid sprite data");
      return false;
    }

    outData.spriteData.emplace_back(spriteData[0],   // x
                                    spriteData[1],   // y
                                    spriteData[2],   // w
                                    spriteData[3]);  // h

    // clear vector so we can reuse it
    spriteData.clear();
  }

  return true;
}

bool ResourceLoader::readFontChunk(FontData& outData) {
  if (!readChunkHeaderInternal(ResourceDefines::FieldType::FONT,
                               outData.header)) {
    return false;
  }

  std::string singleLine = "";
  if (!std::getline(_fontsSourceStream, singleLine)) {
    return false;
  }

  outData.fontSize = StringUtils::safeStoi(singleLine);

  return true;
}

bool ResourceLoader::readSoundChunk(SoundData& outData) {
  if (!readChunkHeaderInternal(ResourceDefines::FieldType::SOUND,
                               outData.header)) {
    return false;
  }

  constexpr int32_t SOUND_SPECIFIC_SIZE = 2;
  std::string lines[SOUND_SPECIFIC_SIZE];

  for (int32_t i = 0; i < SOUND_SPECIFIC_SIZE; ++i) {
    if (!std::getline(_soundsSourceStream, lines[i])) {
      return false;
    }
  }

  if ("chunk" == lines[0]) {
    outData.soundType = SoundType::CHUNK;
  } else if ("music" == lines[0]) {
    outData.soundType = SoundType::MUSIC;
  } else {
    LOGERR(
        "Error wrong description in file: %s, with tag: %s. Second "
        "argument must be 'music' or 'chunk'",
        ResourceFileHeader::getSoundBinName().c_str(),
        outData.header.path.c_str());

    outData.soundType = SoundType::UNKNOWN;
    return false;
  }

  if ("low" == lines[1]) {
    outData.soundLevel = SoundLevel::LOW;
  } else if ("medium" == lines[1]) {
    outData.soundLevel = SoundLevel::MEDIUM;
  } else if ("high" == lines[1]) {
    outData.soundLevel = SoundLevel::HIGH;
  } else if ("very_high" == lines[1]) {
    outData.soundLevel = SoundLevel::VERY_HIGH;
  } else {
    LOGERR(
        "Error wrong description in file: %s, with tag: %s. "
        "Third argument must be 'low', 'medium', 'high' or 'very_high'",
        ResourceFileHeader::getSoundBinName().c_str(),
        outData.header.path.c_str());

    outData.soundLevel = SoundLevel::UNKNOWN;
    return false;
  }

  return true;
}
