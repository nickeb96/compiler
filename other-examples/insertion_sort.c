
void insertion_sort(quad array, quad length)
{
    quad i;
    quad j;
    quad temp;
    quad a;
    quad b;

    i = 0;
    while (i < length)
    {
        j = i;
        while (j > 0)
        {
            a = array + j * 8;
            b = array + (j - 1) * 8;
            if (*a < *b)
            {
                temp = *a;
                *a = *b;
                *b = temp;
            }

            j = j - 1;
        }

        i = i + 1;
    }
}

