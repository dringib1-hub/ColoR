void _start() {
    __asm__ volatile ("mov $0x13, %%ax; int $0x10" ::: "ax");

    // Вывод надписи "MyOS"
    for (int i = 0; i < 4; ++i) {
        __asm__ volatile (
            "mov $0x0C, %%ah\n\t"
            "mov %0, %%al\n\t"
            "mov %1, %%cx\n\t"
            "mov $50, %%dx\n\t"
            "mov $0x0D, %%bh\n\t"
            "int $0x10"
            :
            : "r"('M' + i), "r"(i * 10)
            : "ax", "cx", "dx", "bh"
        );
    }
}
