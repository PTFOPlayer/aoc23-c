#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
typedef struct num
{
    uint16_t val;
    uint16_t h;
    uint16_t w;
    uint8_t l;
    bool added;
} num;

typedef struct symbol
{
    uint16_t h;
    uint16_t w;
} symbol;

int main(int argc, char const *argv[])
{
    FILE *f = fopen("./file.txt", "r");

    char line[256] = {0};

    num *num_map = (num *)malloc(sizeof(num) * 1);
    size_t num_c = 1;
    symbol *symbol_map = (symbol *)malloc(sizeof(symbol) * 1);
    size_t symbol_c = 1;

    int i = 0;
    while (fgets(line, 250, f))
    {
        size_t len = strlen(line);
        size_t num_symbolt = 0;
        size_t num_end = 0;
        size_t symbol_ind = 0;

        while (num_symbolt < len)
        {

            while (num_symbolt < len && !(line[num_symbolt] <= '9' && line[num_symbolt] >= '0'))
                num_symbolt++;
            num_end = num_symbolt;
            while (num_end < len && line[num_end] <= '9' && line[num_end] >= '0')
                num_end++;
            size_t test = 0;
            if (num_symbolt < len)
            {

                char num_buffer[16] = {0};
                strncpy(num_buffer, line + num_symbolt, num_end - num_symbolt);
                num temp = {
                    .h = i,
                    .w = num_symbolt,
                    .l = num_end - num_symbolt,
                    .val = atoi(num_buffer),
                    .added = false};
                num_map[num_c - 1] = temp;
                num_c++;
                num_map = (num *)realloc(num_map, sizeof(num) * num_c);
            }
            num_symbolt = num_end + 1;
        }

        while (symbol_ind < len - 1)
        {
            if (line[symbol_ind] != '.' && !(line[symbol_ind] <= '9' && line[symbol_ind] >= '0'))
            {
                symbol temp = {
                    .h = i,
                    .w = symbol_ind};
                symbol_map[symbol_c - 1] = temp;
                symbol_c++;
                symbol_map = (symbol *)realloc(symbol_map, sizeof(symbol) * symbol_c);
            }
            symbol_ind++;
        }
        i++;
    }
    int sum = 0;

    for (size_t i = 0; i < symbol_c - 1; i++)
    {
        size_t sh = symbol_map[i].h;
        size_t sw = symbol_map[i].w;
        for (size_t j = 0; j < num_c - 1; j++)
        {
            size_t nh = num_map[j].h;
            size_t nbw = num_map[j].w;
            size_t new = num_map[j].w + num_map[j].l - 1;
            if (nh <= sh + 1 && nh >= sh - 1 && !num_map[j].added)
                if ((nbw <= sw + 1 && nbw >= sw - 1) || (new <= sw + 1 && new >= sw - 1))
                {
                    num_map[j].added = true;
                    printf("added: %d\n", num_map[j].val);
                    sum += num_map[j].val;
                }
        }
    }

    printf("%d\n", sum);
    return 0;
}
