
void fibonacci(quad n)
{
    quad previous;
    quad current;
    quad temp;

    previous = 0;
    current = 1;

    while (n > 0)
    {
        print_number(current);

        temp = previous;
        previous = current;
        current = current + temp;

        n = n - 1;
    }
}

