// files.c — общие утилиты (латиница!)
#include <stdint.h>

void memset(void* dst, uint8_t val, size_t n) {
    uint8_t* p = (uint8_t*)dst;
    while (n--) *p++ = val;
}

void memcpy(void* dst, const void* src, size_t n) {
    uint8_t* d = (uint8_t*)dst;
    const uint8_t* s = (const uint8_t*)src;
    while (n--) *d++ = *s++;
}

int strlen(const char* s) {
    int len = 0;
    while (*s++) len++;
    return len;
}

void itoa(int n, char* buf, int base) {
    static char digits[] = "0123456789ABCDEF";
    int i = 0;
    if (n < 0) { buf[i++] = '-'; n = -n; }
    do {
        buf[i++] = digits[n % base];
        n /= base;
    } while (n);
    buf[i] = 0;
    // reverse
    for (int l = 0, r = i-1; l < r; l++, r--) {
        char t = buf[l]; buf[l] = buf[r]; buf[r] = t;
    }
}
