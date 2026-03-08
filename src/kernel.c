// kernel.c — 12 строк, запускается по 0x8000
void _start() {
    // Вывод 'K' через BIOS (проверка передачи управления)
    __asm__ volatile (
        "mov $0x0E, %%ah\n\t"
        "mov $'K', %%al\n\t"
        "mov $0x00, %%bh\n\t"
        "int $0x10"
        :
        :
        : "ah", "al", "bh"
    );

    // Зацикливаемся — загрузчик считает, что ядро загружено
    while (1) {
        __asm__ volatile ("hlt");
    }
}
