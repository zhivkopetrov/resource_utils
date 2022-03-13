#ifndef RESOURCE_UTILS_SOUNDDEFINES_H_
#define RESOURCE_UTILS_SOUNDDEFINES_H_

// System headers
#include <cstdint>

// Other libraries headers

// Own components headers

// Forward declarations

enum class SoundType : uint8_t { UNKNOWN = 0, MUSIC, CHUNK };

enum class SoundLevel : uint8_t {
  NONE = 0,
  LOW = 32,
  MEDIUM = 64,
  HIGH = 96,
  VERY_HIGH = 128,

  UNKNOWN = 255
};

SoundLevel& operator++(SoundLevel& instance);

#endif /* RESOURCE_UTILS_SOUNDDEFINES_H_ */
