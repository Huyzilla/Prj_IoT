#ifndef PATTERN_STORAGE_HPP
#define PATTERN_STORAGE_HPP

#include <cstdint>

#define MAX_PATTERN_LENGTH 9
#define MAX_PATTERN_SLOTS 50
#define PATTERN_FLASH_START_ADDRESS 0x080E0000

void savePatternToFlash(const uint8_t* pattern, uint8_t length);
bool findPatternMatch(const uint8_t* pattern, uint8_t length);
uint8_t getNextPatternIndex();
void deleteAllSavedPatterns();
#endif // PATTERN_STORAGE_HPP
