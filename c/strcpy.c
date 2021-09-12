#include <stdio.h>

int main() {
    char *src = "hello world!", dst_[13];
    char *dst = dst_;

    while (*dst++ = *src++) ;

    printf("%s\n", dst_);
}