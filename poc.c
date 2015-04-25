/*
 *  gcc poc.c -fstack-protector-all -Wl,-z,now,-z,-relro
 */

#include <stdio.h>
#include <stdlib.h>

void stack_overflow(void) {
    char stack_buf[16];

    fread(stack_buf, 1, 48, stdin);
    return;
}

int main(void) {
    size_t alloc_size = 0;
    size_t read_size = 0;
    char *heap_buf;

    if (scanf("%zu", &alloc_size) != 1) return -1;
    if (scanf("%zu", &read_size) != 1) return -1;

    heap_buf = (char*)malloc(alloc_size);
    if (!heap_buf) return -1;

    fread(heap_buf, sizeof(char), read_size, stdin);
    stack_overflow();
    free(heap_buf);
    return 0;
}
