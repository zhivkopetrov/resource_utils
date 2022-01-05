// Corresponding header
#include "resource_utils/structs/SoundData.h"

// C system headers

// C++ system headers

// Other libraries headers

// Own components headers

SoundData::SoundData()
    : soundType(SoundType::UNKNOWN), soundLevel(SoundLevel::UNKNOWN) {

}

SoundData::SoundData(const DataHeader &inputHeader,
                     const SoundType inputSoundType,
                     const SoundLevel inputSoundLevel)
    : header(inputHeader), soundType(inputSoundType),
      soundLevel(inputSoundLevel) {
}

void SoundData::reset() {
  header.reset();
  soundType = SoundType::UNKNOWN;
  soundLevel = SoundLevel::UNKNOWN;
}
