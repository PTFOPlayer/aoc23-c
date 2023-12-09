#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char const *argv[])
{
    FILE *f = fopen("./file.txt", "r");
    char line[255];

    uint32_t sum = 0;
    while (fgets(line, 250, f))
    {
        size_t len = strlen(line);

        size_t id_start = 0;
        while (line[id_start] != ' ')
            id_start++;

        size_t id_end = id_start;
        while (line[id_end] != ':')
            id_end++;

        char id_buff[8];
        strncpy(id_buff, line + id_start, id_end - id_start);

        size_t w_count = 1;
        uint16_t *win_num = (uint16_t *)malloc(sizeof(uint16_t) * 1);
        size_t m_count = 1;
        uint16_t *my_num = (uint16_t *)malloc(sizeof(uint16_t) * 1);

        size_t num_start = id_end;
        size_t num_end = 0;
        while (num_start < len)
        {
            while (num_start < len && !(line[num_start] <= '9' && line[num_start] >= '0') && line[num_start] != '|')
                num_start++;
            num_end = num_start;
            while (num_end < len && line[num_end] <= '9' && line[num_end] >= '0' && line[num_start] != '|')
                num_end++;

            if (line[num_start] == '|')
                break;
            else
            {
                char num_buff[8] = {0};

                strncpy(num_buff, line + num_start, num_end - num_start);
                win_num[w_count - 1] = atoi(num_buff);
                w_count++;
                win_num = (uint16_t *)realloc(win_num, sizeof(uint16_t) * w_count);
            }
            num_start = num_end + 1;
        }

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
                char num_buff[8] = {0};

                strncpy(num_buff, line + num_start, num_end - num_start);
                my_num[m_count - 1] = atoi(num_buff);
                m_count++;
                my_num = (uint16_t *)realloc(my_num, sizeof(uint16_t) * m_count);
            }
            num_start = num_end + 1;
        }

        uint32_t points = 0;

        for (size_t i = 0; i < w_count - 1; i++)
        {
            for (size_t j = 0; j < m_count; j++)
            {
                if (win_num[i] == my_num[j])
                    if (points == 0)
                        points++;
                    else
                        points *= 2;
            }
        }
        sum += points;
    }
    printf("%d\n", sum);
    return 0;
}
