#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

typedef struct entry_t
{
    uint64_t dest_start;
    uint64_t src_start;
    uint64_t range;
} entry_t;

int main(int argc, char const *argv[])
{
    FILE *f = fopen("./file.txt", "r");

    size_t seeds_c = 0;
    uint64_t seeds[64] = {0};

    char line[512] = {0};
    fgets(line, 500, f);
    size_t len = strlen(line);
    size_t data_start = 0;
    while (line[data_start] != ':')
        data_start++;

    size_t num_start = data_start;
    size_t num_end = 0;
    while (num_start < len)
    {
        while (num_start < len && !(line[num_start] <= '9' && line[num_start] >= '0') && line[num_start] != '\n')
            num_start++;
        num_end = num_start;
        while (num_end < len && line[num_end] <= '9' && line[num_end] >= '0' && line[num_start] != '\n')
            num_end++;

        if (line[num_start] == '\n')
            break;
        else
        {
            char num_buff[32] = {0};

            strncpy(num_buff, line + num_start, num_end - num_start);
            seeds[seeds_c] = atoll(num_buff);
            seeds_c++;
        }
        num_start = num_end + 1;
    }

    while (fgets(line, 500, f))
    {
        entry_t entries[64] = {0};
        size_t e_size = 0;

        while (fgets(line, 500, f) && strlen(line) > 2)
        {

            size_t num_start = 0;
            size_t num_end = 0;
            uint64_t entry_buff[3] = {0};
            size_t entry_c = 0;

            size_t len = strlen(line);
            while (num_start < len)
            {
                while (num_start < len && !(line[num_start] <= '9' && line[num_start] >= '0'))
                    num_start++;
                num_end = num_start;
                while (num_end < len && line[num_end] <= '9' && line[num_end] >= '0')
                    num_end++;

                char num_buff[64] = {0};

                strncpy(num_buff, line + num_start, num_end - num_start);
                entry_buff[entry_c] = atoll(num_buff);
                entry_c++;

                num_start = num_end + 1;
            }

            entry_t entry = {
                .dest_start = entry_buff[0],
                .src_start = entry_buff[1],
                .range = entry_buff[2]};

            entries[e_size] = entry;
            e_size++;
        }

        for (size_t i = 0; i < seeds_c; i++)
            for (size_t j = 0; j < e_size; j++)
            {
                entry_t e = entries[j];
                if (seeds[i] >= e.src_start && seeds[i] < e.src_start + e.range)
                {
                    seeds[i] = e.dest_start + (seeds[i] - e.src_start);
                    break;
                }
            }
    }

    uint64_t min = seeds[0];
    for (size_t i = 0; i < seeds_c; i++)
        if (seeds[i] < min)
            min = seeds[i];
    printf("\n\n%llu\n\n", min);

    return 0;
}
