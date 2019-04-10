
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


void bubble_sort(int64_t* a, int64_t l); // compiled by my compiler
void binary_search(int64_t* a, int64_t l, int64_t k); // compiled by my compiler


void print_array(int64_t* array, int64_t length)
{
    size_t i;
    printf("array:");
    for (i = 0; i < length; i++)
        printf(" %lli", array[i]);
    printf("\n");
}

void print_number(int64_t x) // linked to by source.c
{
    printf("number: %lli\n", x);
}

int main(int argc, char** argv)
{
    int64_t length = 25;
    int64_t* array = malloc(length * sizeof(int64_t));
    int64_t i;
    int64_t search_key;

    for (i = 0; i < length; i++)
        array[i] = rand() % 100;

    search_key = array[rand() % length];

    print_array(array, length);

    printf("...about to sort array\n");
    bubble_sort(array, length);
    print_array(array, length);

    printf("...about to do a binary search for %lld\n", search_key);
    binary_search(array, length, search_key);

    free(array);

    return 0;
}

