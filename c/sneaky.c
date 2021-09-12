#include <stdio.h>

typedef struct {
    int *ptr;
} Container;

void inc_1(Container *ct) {
    (*ct->ptr)++;
}

void inc_2(Container ct) {
    (*ct.ptr)++;
}

void print(Container *ct) {
    printf("Container { *ptr: %d }\n", *ct->ptr);
}

int main() {
    int a = 5;
    Container one = {&a};

    print(&one);
    inc_1(&one);
    inc_2(one);
    print(&one);
}