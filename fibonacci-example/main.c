
#include <stdio.h>
#include <stdint.h>

void fibonacci(int64_t n);

void print_number(int64_t x)
{
    printf("%lld\n", x);
}

int main(int argc, char** argv)
{
    fibonacci(20);


    return 0;
}
