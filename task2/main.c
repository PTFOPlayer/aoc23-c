#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

const size_t R = 12;
const size_t G = 13;
const size_t B = 14;

int main(int argc, char const *argv[])
{
    FILE *f = fopen("file.txt", "r");
    char buff[255];

    size_t sum = 0;
    while (fgets(buff, 250, f))
    {
        size_t len = strlen(buff);
        int i = 0;

        size_t first_space_ind = 0;
        while (buff[first_space_ind] != ' ')

            first_space_ind++;

        size_t start_ind = 0;
        while (buff[start_ind] != ':')
            start_ind++;
        start_ind++;

        char id_buff[8] = {0};

        strncpy(id_buff, buff + first_space_ind + 1, start_ind - first_space_ind - 2);
        size_t id = atoi(id_buff);
        sum += id;

        uint16_t blue = 0;
        uint16_t green = 0;
        uint16_t red = 0;

        while (i < len - 1)
        {

            size_t end_ind = start_ind;
            size_t space_ind = start_ind + 2;

            while (buff[end_ind] != ',' && buff[end_ind] != ';' && buff[end_ind] != '\n')
                end_ind++;

            while (buff[space_ind] != ' ')
                space_ind++;

            char name_buff[8] = {0};
            char num_buff[8] = {0};
            strncpy(num_buff, buff + start_ind, space_ind - start_ind);
            strncpy(name_buff, buff + space_ind, end_ind - space_ind);

            if (strcmp(" blue", name_buff) == 0)
                blue += atoi(num_buff);
            if (strcmp(" green", name_buff) == 0)
                green += atoi(num_buff);
            if (strcmp(" red", name_buff) == 0)
                red += atoi(num_buff);

            if (buff[end_ind] == ';' || buff[end_ind] == '\n')
            {
                if (red > R || green > G || blue > B)
                {
                    sum -= id;
                    break;
                }
                blue = 0;
                green = 0;
                red = 0;
            }

            start_ind = end_ind + 1;
            i = end_ind;
        }
    }
    printf("%d", sum);

    return 0;
}
