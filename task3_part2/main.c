#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

typedef struct num
{
    uint16_t val;
    uint16_t h;
    uint16_t w;
    uint16_t l;
} num;

typedef struct star
{
    uint16_t h;
    uint16_t w;
} star;

int main(int argc, char const *argv[])
{
    FILE *f = fopen("./file.txt", "r");

    char **file = (char **)malloc(sizeof(char) * 256);
    file[0] = (char *)malloc(sizeof(char) * 256);
    file[0] = memset(file[0], 0, 256);
    int lines = 1;

    while (fgets(file[lines - 1], 250, f))
    {
        lines++;
        file = (char **)realloc(file, sizeof(char) * lines * 256);
        file[lines - 1] = (char *)malloc(sizeof(char) * 256);
        file[lines - 1] = memset(file[lines - 1], 0, 256);
    }
    lines--;
    int sum = 0;

    num *num_map = (num *)malloc(sizeof(num) * 1);
    size_t num_c = 1;
    star *star_map = (star *)malloc(sizeof(star) * 1);
    size_t star_c = 1;
    for (size_t i = 0; i < lines; i++)
    {
        size_t len = strlen(file[i]);
        size_t num_start = 0;
        size_t num_end = 0;
        size_t star_ind = 0;

        while (num_start < len)
        {

            while (num_start < len && !(file[i][num_start] <= '9' && file[i][num_start] >= '0'))
                num_start++;
            num_end = num_start;
            while (num_end < len && file[i][num_end] <= '9' && file[i][num_end] >= '0')
                num_end++;
            size_t test = 0;
            if (num_start < len)
            {

                char num_buffer[16] = {0};
                strncpy(num_buffer, file[i] + num_start, num_end - num_start);
                num temp = {
                    .h = i,
                    .w = num_start,
                    .l = num_end - num_start,
                    .val = atoi(num_buffer)};
                num_map[num_c - 1] = temp;
                num_c++;
                num_map = (num *)realloc(num_map, sizeof(num) * num_c);
            }
            num_start = num_end + 1;
        }

        while (star_ind < len)
        {
            while (star_ind < len && file[i][star_ind] != '*')
                star_ind++;

            if (star_ind < len)
            {
                star temp = {
                    .h = i,
                    .w = star_ind};
                star_map[star_c - 1] = temp;
                star_c++;
                star_map = (star *)realloc(star_map, sizeof(star) * star_c);
            }
            star_ind++;
        }
    }
    
    for (size_t i = 0; i < star_c - 1; i++)
    {
        size_t connected_c = 0;
        int nums[2] = {0};
        size_t sh = star_map[i].h;
        size_t sw = star_map[i].w;
        for (size_t j = 0; j < num_c - 1; j++)
        {
            size_t nh = num_map[j].h;
            size_t nbw = num_map[j].w;
            size_t new = num_map[j].w + num_map[j].l - 1;
            if (nh <= sh + 1 && nh >= sh - 1)
                if ((nbw <= sw + 1 && nbw >= sw - 1) || (new <= sw + 1 && new >= sw - 1))
                {
                    nums[connected_c] = num_map[j].val;
                    connected_c++;
                }
        }
        if (connected_c == 2)
        {
            sum += nums[0] * nums[1];
        }
    }
    printf("\nsol: %d", sum);

    return 0;
}
