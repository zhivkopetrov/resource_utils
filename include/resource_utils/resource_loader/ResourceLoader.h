#ifndef RESOURCE_UTILS_RESOURCELOADER_H_
#define RESOURCE_UTILS_RESOURCELOADER_H_

// System headers
#include <cstdint>
#include <fstream>
#include <string>

// Other libraries headers
#include "utils/ErrorCode.h"

// Own components headers
#include "resource_utils/defines/ResourceDefines.h"

// Forward declarations
struct ResourceData;
struct FontData;
struct SoundData;
struct DataHeader;
enum class FieldType : uint8_t
;

/** @brief used for containing all resources/fonts/sounds listed in
 *         for resource/font/sounds bin files at
 *         project start up and set the total count of widgets/fonts/sounds.
 *
 *  @param uint64_t - total widgets count
 *  @param uint64_t - total fonts count
 *  @param uint64_t - total musics count
 *  @param uint64_t - total sound chunks count
 *  @param int32_t  - total widgets file size
 *  @param int32_t  - total fonts file size
 *  @param int32_t  - total sounds file size
 *  */
struct EgnineBinHeadersData {
  uint64_t staticWidgetsCount = 0;
  uint64_t dynamicWidgetsCount = 0;
  uint64_t fontsCount = 0;
  uint64_t musicsCount = 0;
  uint64_t chunksCount = 0;
  int32_t widgetsFileSize = 0;
  int32_t fontsFileSize = 0;
  int32_t soundsFileSize = 0;
};

class ResourceLoader {
public:
  /** @brief used to initialize the ResourceLoader internal streams
   *
   *  @returns ErrorCode - error code
   * */
  ErrorCode init(const std::string &resourcesFolderLocation);

  /** @brief used to load and populate the EgnineBinHeadersData
   *
   *  @returns ErrorCode - error code
   * */
  ErrorCode readEngineBinHeaders(EgnineBinHeadersData &outData);

  /** @brief used to parse single resource from resource bin file
   *
   *  @param ResourceData & - fully parsed ResourceData chunk
   *
   *  @return bool          - successful read or not
   *
   *                 NOTE: unsuccessful read means
   *                                resource bin file.eof() is reached.
   * */
  bool readResourceChunk(ResourceData &outData);

  /** @brief used to parse single resource from fonts bin file
   *
   *  @param ResourceData& - fully parsed FontData chunk
   *
   *  @return bool - successful read or not
   *                 NOTE: unsuccessful read means
   *                                    fonts bin file.eof() is reached.
   * */
  bool readFontChunk(FontData &outData);

  /** @brief used to parse single resource from sound bin file
   *
   *  @param ResourceData * - fully parsed SoundData chunk
   *
   *  @return bool          - successful read or not
   *
   *                 NOTE: unsuccessful read means
   *                                    sound bin file.eof() is reached.
   * */
  bool readSoundChunk(SoundData &outData);

private:
  /** @brief used to open file streams for resource/font/sounds bin files
   *
   *  @returns ErrorCode - error code
   * */
  ErrorCode openSourceStreams(const std::string &resourcesBinLocation);

  /** @brief used to close file streams for resource/font/sounds bin files
   * */
  void closeSourceStreams();

  /** @brief used to read  total count of widgets
   *         and their respective file size from resource bin file
   *
   *  @param uint64_t &  - total static widgets count
   *  @param uint64_t &  - total dynamic widgets count
   *  @param int32_t &   - total widgets file size
   *
   *  @returns ErrorCode - error code
   * */
  ErrorCode readResourceBinHeader(uint64_t &outStaticWidgetsSize,
                                  uint64_t &outDynamicWidgetsSize,
                                  int32_t &outWidgetFileSize);

  /** @brief used to read  total count of fonts
   *         and their respective file size from fond bin file
   *
   *  @param uint64_t *  - total fonts count
   *  @param int32_t *   - total fonts file size
   *
   *  @returns ErrorCode - error code
   * */
  ErrorCode readFontBinHeader(uint64_t &outFontsSize,
                              int32_t &outFontsFileSize);

  /** @brief used to read  total count of musics and sound chunks
   *         and their respective file size from sound bin file
   *
   *  @param uint64_t & - total musics count
   *  @param uint64_t &   - total sound chunks count
   *  @param int32_t &   - total sounds file size
   *
   *  @returns ErrorCode - error code
   * */
  ErrorCode readSoundBinHeader(uint64_t &outMusicsSize, uint64_t &outChunksSize,
                             int32_t &outSoundsFileSize);

  /** @brief used to parse single DataHeader from
   *         resource/font/sounds bin files (they share common header).
   *
   *  @param const FieldType - IMAGE, SPRITE or FONT
   *  @param DataHeader &    - fully parsed DataHeader chunk
   *
   *  @return bool           - successful read or not
   *
   *                 NOTE: unsuccessful read means
   *                                destinationStream.eof() is reached.
   * */
  bool readChunkHeaderInternal(const ResourceDefines::FieldType fieldType,
                               DataHeader &outData);

  // Input file stream for the project resource file
  std::ifstream _resSourceStream;

  // Input file stream for the project font file
  std::ifstream _fontsSourceStream;

  // Input file stream for the project sounds file
  std::ifstream _soundsSourceStream;
};

#endif /* RESOURCE_UTILS_RESOURCELOADER_H_ */
