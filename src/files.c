#include <stdint.h>
#include <stddef.h>
#include <string.h>

void memset(void* dst, uint8_t val, size_t n) {
    volatile uint8_t* p = (uint8_t*)dst;
    while (n--) *p++ = val;
}

int strlen(const char* s) {
    int i = 0;
    while (s[i]) i++;
    return i;
}
