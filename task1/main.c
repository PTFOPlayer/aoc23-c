#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "vector.h"

char partation_left(char *buff)
{
    size_t len = strlen(buff);
    for (size_t i = 0; i < len; i++)
    {
        if (buff[i] >= '0' && buff[i] <= '9')
        {
            return buff[i];
        }
    }
}

char partation_right(char *buff)
{
    size_t len = strlen(buff);
    for (size_t i = len - 1; i >= 0; i--)
    {
        if (buff[i] >= '0' && buff[i] <= '9')
        {
            return buff[i];
            break;
        }
    }
}

int main(int argc, char const *argv[])
{
    FILE *f = fopen("file.txt", "r");
    char buff[255];
    char num_buff[4];
    int *data = (int *)malloc(0 * sizeof(int));

    vector v = create_from_ptr(data, 0);

    while (fgets(buff, 250, f))
    {
        sprintf(num_buff, "%c%c", partation_left(buff), partation_right(buff));

        push(&v, atoi(num_buff));
    }

    int res = 0;
    for (size_t i = 0; i < v_size(&v); i++)
    {
        int val = 0;
        v_index(&v, i, &val);
        printf("%d\n", val);
        res += val;
    }
    printf("\n  solution is: %d \n", res);

    return 0;
}
