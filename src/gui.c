#include <stdint.h>

extern void vga_clear();
extern void vga_put_char(char c, uint8_t attr, int x, int y);

#define ATTR_SEL  0x70
#define ATTR_NORM 0x07
#define MAX_ITEMS 3

const char* menu[] = {
    "Start Shell",
    "Reboot",
    "Shutdown"
};

int sel = 0;

void draw_menu() {
    vga_clear();
    for (int i = 0; i < MAX_ITEMS; i++) {
        uint8_t attr = (i == sel) ? ATTR_SEL : ATTR_NORM;
        vga_put_char('>', attr, 2, 5 + i);
        for (int j = 0; j < strlen(menu[i]); j++) {
            vga_put_char(menu[i][j], attr, 4 + j, 5 + i);
        }
    }
}

void handle_key(uint8_t sc) {
    if (sc == 0x48) { sel = (sel - 1 + MAX_ITEMS) % MAX_ITEMS; draw_menu(); }
    if (sc == 0x50) { sel = (sel + 1) % MAX_ITEMS; draw_menu(); }
    if (sc == 0x1C) { /* Enter */ }
}
