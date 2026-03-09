#include <stdint.h>
#include <string.h>  // да, теперь нормально — strlen из libc

extern void vga_clear();
extern void vga_put_char(char c, uint8_t attr, int x, int y);

// ... остальное без изменений
void handle_key(uint8_t sc);
void draw_menu();

int sel = 0;

void draw_menu() {
    vga_clear();
    const char* m[] = {"Start", "Reboot", "Exit"};
    for (int i = 0; i < 3; i++) {
        uint8_t a = (i == sel) ? 0x70 : 0x07;
        vga_put_char('>', a, 2, 5+i);
        for (int j = 0; j < strlen(m[i]); j++)
            vga_put_char(m[i][j], a, 4+j, 5+i);
    }
}

void handle_key(uint8_t sc) {
    if (sc == 0x48) { sel = (sel+2)%3; draw_menu(); }
    if (sc == 0x50) { sel = (sel+1)%3; draw_menu(); }
}
