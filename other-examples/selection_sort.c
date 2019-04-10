
void selection_sort(quad array, quad length)
{
    quad i;
    quad j;
    quad position;
    quad temp;
    quad thing;
    i = 0;
    while (i < length - 1)
    {
        position = i;
        j = i + 1;
        while (j < length)
        {
            temp = *(array + position * 8);
            thing = *(array + j * 8);
            if (temp > thing)
                position = j;
            j = j + 1;
        }
        if (position != i)
        {
            temp = *(array + i * 8);
            *(array + i * 8) = *(array + position * 8);
            *(array + position * 8) = temp;
        }
        i = i + 1;
    }
}

