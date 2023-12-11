#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

void parse_line(char[256], uint64_t *);

int main(int argc, char const *argv[])
{
    FILE *f = fopen("./file.txt", "r");

    char line[256] = {0};

    uint64_t time;
    uint64_t distance;

    fgets(line, 250, f);
    parse_line(line, &time);
    fgets(line, 250, f);
    parse_line(line, &distance);

    uint8_t b_min = 0;
    uint64_t min = 0, max = 0;

    for (size_t j = 1; j < time; j++)
    {
        uint64_t speed = j;
        uint64_t rem_time = time - j;
        uint64_t n_distance = speed * rem_time;
        if (n_distance > distance)
        {
            if (!b_min && (b_min = 1))
                min = j;
            else
                max = j;
        }
    }
    printf("%llu\n", max - min + 1);
}

void parse_line(char line[256], uint64_t *arr)
{
    size_t temp_size = 1;
    size_t data_start = 0;
    while (line[data_start] != ':')
        data_start++;
    data_start++;

    char final_buff[64] = {0};
    size_t final_len = 0;
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

        strncpy(final_buff + final_len, line + num_start, num_end - num_start);
        final_len += num_end - num_start;
        num_start = num_end + 1;
    }
    *arr = atoll(final_buff);
}