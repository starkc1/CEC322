#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define __IO volatile

// Functions defined in a .s file which have do be declared before being used
extern int32_t accumulate_values(int32_t x1, int32_t x2, int32_t h1, int32_t h2);
extern void strcpy_from_rom_to_ram(const char *src, char *dst);
extern void asm_and(__IO uint32_t *result, uint32_t n1, uint32_t n2);
extern void asm_or(__IO uint32_t *result, uint32_t n1, uint32_t n2);
extern void asm_xor(__IO uint32_t *result, uint32_t n1, uint32_t n2);
extern void asm_set_value(__IO uint32_t *reg, uint32_t value, uint32_t mask, uint32_t shift);

// Variables defined in a .s file which have do be declared before being used
extern uint8_t mask;
extern uint16_t shift;
extern uint32_t nouse;

// Define a data structure, simulating the control registers of GPIOs
typedef struct
{
  __IO uint32_t REG1;
  __IO uint32_t REG2;
  __IO uint32_t REG3;
} RAM_IO;

uint8_t count = 20;

int main(void) {
    int32_t y = 10, x = 3, h = 4;

    // Accumulate values using an assembly function
    y = accumulate_values(x, x, h, h);
    printf("The result of x * h + x * h is %d\n", y);

    // The location of the following const char src_str is depending on the compiler:
    // it can be 1) in the ROM or 2) in the RAM.
    // To check where it is saved, print the address using printf("%p\n", src_str).
    const char src_str[] = "Copy me if you can---this is a long string.";
    printf("Original string at %p: '%s'\n", src_str, src_str);

    // The following dst_str is not allocated in the memory; we just want to point it
    // to a memory block we are sure that is empty.
    // We configure the RAM into the following two blocks in "Options for Target..." ->
    // "Target" -> "IRAM1 and IRAM2", with the first being default:
    // 1) Starting: 0x20000000; size: 0x10000 (2^16 B = 2^6 kB)
    // 2) Starting: 0x20010000; size: 0x10000 (2^16 B = 2^6 kB)
    // As a result, we can put the dst_str at 0x20010000.
    char *dst_str = (char *)0x20010000;

    // Copy "acount" number chars from src_str to dst_str using an assembly function
    strcpy_from_rom_to_ram(src_str, dst_str);
    printf("Copied   string at %p: '%s'\n", dst_str, dst_str);

    // Define a few pointers of RAM_IO, leaving enough space in between.
    // We can then use the Memory view to see the contents of these memory locations
    RAM_IO *ram1 = (RAM_IO *)(0x20010000 + 0x40);
    RAM_IO *ram2 = (RAM_IO *)(0x20010000 + 0x80);
    RAM_IO *ram3 = (RAM_IO *)(0x20010000 + 0xC0);
    RAM_IO *ram4 = (RAM_IO *)(0x20010000 + 0x100);

    ram1->REG2 = 0x1234;                // Just define the lowerst 16 bits,
    ram1->REG3 = 0x5432;                // leading the highest 16 bits to zeros.
    asm_and(&ram1->REG1, ram1->REG2, ram1->REG3);
    printf("The AND of 0x%X and 0x%X is 0x%X\n", ram1->REG2, ram1->REG3, ram1->REG1);

    ram2->REG1 = ram1->REG1;
    ram2->REG2 = ram1->REG2 + 0x1111;
    ram2->REG3 = ram1->REG3;    // We can see the value of REG3 before calling the fun below
    asm_or(&ram2->REG3, ram2->REG1, ram2->REG2);
    printf("The OR  of 0x%X and 0x%X is 0x%X\n", ram2->REG1, ram2->REG2, ram2->REG3);

    ram3->REG1 = ram2->REG1;
    ram3->REG2 = 0xFFFF;
    asm_xor(&ram3->REG3, ram3->REG1, ram3->REG2);
    printf("The XOR of 0x%X and 0x%X is 0x%X\n", ram3->REG1, ram3->REG2, ram3->REG3);

    mask = 7;
    shift = 4;
    ram4->REG1 = 0x1234;
    asm_set_value(&ram4->REG1, 5, mask, shift);
    printf("The set result is 0x%X\n", ram4->REG1);

    while (1);
}
