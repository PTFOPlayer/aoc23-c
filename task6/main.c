#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

void parse_line(char[256], uint32_t *, size_t *);

int main(int argc, char const *argv[])
{
    FILE *f = fopen("./file.txt", "r");

    char line[256] = {0};

    uint32_t *time = (uint32_t *)malloc(sizeof(uint32_t));
    size_t time_c;
    uint32_t *distance = (uint32_t *)malloc(sizeof(uint32_t));
    size_t distance_c;

    fgets(line, 250, f);
    parse_line(line, time, &time_c);
    fgets(line, 250, f);
    parse_line(line, distance, &distance_c);

    if (time_c != distance_c)
    {
        printf("error: data corupted");
        exit(-1);
    }

    uint32_t res = 1;
    for (size_t i = 0; i < time_c; i++)
    {
        uint32_t t_time = time[i];
        uint32_t t_distance = distance[i];

        uint8_t b_min = 0;
        uint32_t min = 0, max = 0;

        for (size_t j = 1; j < t_time; j++)
        {
            uint32_t speed = j;
            uint32_t rem_time = t_time - j;
            uint32_t n_distance = speed * rem_time;
            if (n_distance > t_distance)
            {
                if (!b_min && (b_min = 1))
                    min = j;
                else
                    max = j;
            }
        }
        res *= (max - min + 1);
    }
    printf("%d\n", res);

    return 0;
}

void parse_line(char line[256], uint32_t *arr, size_t *size)
{
    size_t temp_size = 1;
    size_t data_start = 0;
    while (line[data_start] != ':')
        data_start++;
    data_start++;

    size_t len = strlen(line);

    size_t num_start = data_start;
    size_t num_end = num_start;
    while (num_start < len)
    {
        while (num_start < len && !(line[num_start] <= '9' && line[num_start] >= '0') && line[num_start] != '\n')
            num_start++;
        num_end = num_start;
        while (num_end < len && line[num_end] <= '9' && line[num_end] >= '0' && line[num_start] != '\n')
            num_end++;

        char num_buff[8] = {0};
        strncpy(num_buff, line + num_start, num_end - num_start);
        num_start = num_end + 1;
        arr[temp_size - 1] = atoi(num_buff);
        temp_size++;
        arr = realloc(arr, sizeof(uint32_t) * temp_size);
    }

    *size = temp_size - 1;
}