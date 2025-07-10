#include "PatternStorage.hpp"
#include "stm32f4xx_hal.h"
#include <cstring>

#define PATTERN_SLOT_SIZE     10  // 1 byte length + 9 bytes pattern
#define FLASH_SECTOR_NUMBER   FLASH_SECTOR_11
#define FLASH_PAGE_SIZE       0x20000  // 128KB
#define FLASH_END_ADDRESS     (PATTERN_FLASH_START_ADDRESS + FLASH_PAGE_SIZE)

static uint8_t nextPatternIndex = 0;

// Trả về địa chỉ flash cho 1 slot
static uint32_t getPatternAddress(uint8_t index) {
    return PATTERN_FLASH_START_ADDRESS + index * PATTERN_SLOT_SIZE;
}

// Xóa toàn bộ sector
static void eraseFlashSector() {
    HAL_FLASH_Unlock();

    FLASH_EraseInitTypeDef eraseInit;
    uint32_t sectorError;

    eraseInit.TypeErase = FLASH_TYPEERASE_SECTORS;
    eraseInit.Sector = FLASH_SECTOR_NUMBER;
    eraseInit.NbSectors = 1;
    eraseInit.VoltageRange = FLASH_VOLTAGE_RANGE_3;

    HAL_FLASHEx_Erase(&eraseInit, &sectorError);

    HAL_FLASH_Lock();
}

// Kiểm tra slot còn trống không (0xFF)
static bool isSlotEmpty(uint32_t addr) {
    return (uint8_t)addr == 0xFF;
}

// Tìm index tiếp theo để ghi (slot trống đầu tiên)
uint8_t getNextPatternIndex() {
    for (uint8_t i = 0; i < MAX_PATTERN_SLOTS; ++i) {
        uint32_t addr = getPatternAddress(i);
        if (isSlotEmpty(addr)) {
            nextPatternIndex = i;
            return i;
        }
    }

    // Nếu không còn slot trống → flash đầy
    return MAX_PATTERN_SLOTS;
}

// Lưu pattern mới
void savePatternToFlash(const uint8_t* pattern, uint8_t length) {
    if (length == 0 || length > MAX_PATTERN_LENGTH) return;

    uint8_t index = getNextPatternIndex();

    // Nếu hết bộ nhớ → xóa sector và ghi lại từ đầu
    if (index >= MAX_PATTERN_SLOTS) {
        eraseFlashSector();
        index = 0;
    }

    uint32_t addr = getPatternAddress(index);

    HAL_FLASH_Unlock();

    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, addr, length) != HAL_OK) goto end;
    for (uint8_t i = 0; i < length; ++i) {
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, addr + 1 + i, pattern[i]) != HAL_OK) break;
    }

end:
    HAL_FLASH_Lock();
    nextPatternIndex = (index + 1) % MAX_PATTERN_SLOTS;
}

// So sánh pattern nhập với tất cả pattern đã lưu
bool findPatternMatch(const uint8_t* pattern, uint8_t length) {
    for (uint8_t i = 0; i < MAX_PATTERN_SLOTS; ++i) {
        uint32_t addr = getPatternAddress(i);
        uint8_t savedLength = (uint8_t)addr;

        if (savedLength == 0xFF || savedLength == 0 || savedLength != length) continue;

        const uint8_t* savedPattern = (const uint8_t*)(addr + 1);
        if (memcmp(savedPattern, pattern, length) == 0) {
            return true;
        }
    }
    return false;
}

void deleteAllSavedPatterns() {
    eraseFlashSector();
    // Cần reset lại index để bắt đầu ghi từ đầu sau khi xóa
    nextPatternIndex = 0;
}
