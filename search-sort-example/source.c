

void bubble_sort(quad array, quad length)
{
    quad i;
    quad temp;
    quad current;
    quad before;
    quad swapped;
    swapped = 1;
    while (swapped)
    {
        swapped = 0;
        i = 1;
        while (i < length)
        {
            current = array + i*8;
            before = array + ((i - 1)*8);
            if (*current < *before)
            {
                temp = *before;
                *before = *current;
                *current = temp;
                swapped = 1;
            }
            i = i + 1;
        }
    }
}



void binary_search(quad array, quad length, quad key)
{
    quad half;

    while (length > 0)
    {
        half = length / 2;

        if (*(array + half * 8) > key)
        {
            length = half;
        }
        else if (*(array + half * 8) < key)
        {
            array = array + (half + 1) * 8;
            length = half;
        }
        else
        {
            print_number(*(array + half * 8));
            length = 0;
        }
    }
}

