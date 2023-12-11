#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <omp.h>
typedef struct entry_t
{
    uint64_t dest_start;
    uint64_t src_start;
    uint64_t range;
} entry_t;

typedef struct property_t
{
    entry_t *entries;
    size_t size;
} property_t;

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
    property_t *props = (property_t *)malloc(sizeof(property_t));
    size_t props_c = 1;
    while (fgets(line, 500, f))
    {
        entry_t *entries = (entry_t *)malloc(sizeof(entry_t) * 64);
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
        property_t temp = {
            .entries = entries,
            .size = e_size,
        };
        props[props_c - 1] = temp;
        props_c++;
        props = (property_t *)realloc(props, sizeof(property_t) * props_c);
    }

    for (size_t i = 0; i < props_c - 1; i++)
    {
        printf("prop: %d, size: %d \n", i, props[i].size);
        for (size_t j = 0; j < props[i].size; j++)
        {
            printf("%d %d %d\n", props[i].entries[j].dest_start, props[i].entries[j].src_start, props[i].entries[j].range);
        }
    }
    uint64_t min = UINT64_MAX;
    for (size_t i = 0; i < seeds_c; i += 2)
    {
        #pragma omp parallel for
        for (size_t j = 0; j < seeds[i + 1]; j++)
        {
            uint64_t cur_seed = seeds[i] + j;
            for (size_t k = 0; k < props_c; k++)
            {
                property_t temp_prop = props[k];
                for (size_t m = 0; m < temp_prop.size; m++)
                {
                    entry_t e = temp_prop.entries[m];
                    if (cur_seed >= e.src_start && cur_seed < e.src_start + e.range)
                    {
                        cur_seed = e.dest_start + (cur_seed - e.src_start);
                        break;
                    }
                }
            }
            if (cur_seed < min)
                min = cur_seed;
        }
    }

    printf("\n\n %d \n\n", min);

    return 0;
}
