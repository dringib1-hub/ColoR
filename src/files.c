void load_file_sector(int sector, unsigned char* buffer) {
    __asm__ volatile (
        "mov $0x02, %%ah\n\t"
        "mov $1, %%al\n\t"
        "mov %0, %%cl\n\t"
        "mov $0x80, %%dl\n\t"
        "mov %1, %%bx\n\t"
        "int $0x13"
        :
        : "r"((char)sector), "r"(buffer)
        : "ax", "bx", "cx", "dx"
    );
}
