#ifndef RESOURCE_UTILS_SOUND_DATA_H_
#define RESOURCE_UTILS_SOUND_DATA_H_

// System headers
#include <cstdint>

// Other libraries headers

// Own components headers
#include "resource_utils/structs/DataHeader.h"
#include "resource_utils/defines/SoundDefines.h"

// Forward declarations

struct SoundData {
  SoundData();

  // move piecewise constructor - used for emplace_back move semantics
  SoundData(const DataHeader& inputHeader, const SoundType inputSoundType,
            const SoundLevel inputSoundLevel);

  void reset();

  DataHeader header;
  SoundType soundType;
  SoundLevel soundLevel;
};

#endif /* RESOURCE_UTILS_SOUND_DATA_H_ */
