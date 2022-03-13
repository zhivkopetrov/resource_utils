// Corresponding header
#include "resource_utils/defines/SoundDefines.h"

// System headers

// Other libraries headers

// Own components headers

SoundLevel& operator++(SoundLevel& instance) {
  switch (instance) {
    case SoundLevel::NONE:
      return instance = SoundLevel::LOW;

    case SoundLevel::LOW:
      return instance = SoundLevel::MEDIUM;

    case SoundLevel::MEDIUM:
      return instance = SoundLevel::HIGH;

    case SoundLevel::HIGH:
      return instance = SoundLevel::VERY_HIGH;

    case SoundLevel::VERY_HIGH:
      return instance = SoundLevel::NONE;

    case SoundLevel::UNKNOWN:
      return instance = SoundLevel::UNKNOWN;
  }

  return instance = SoundLevel::UNKNOWN;
}
