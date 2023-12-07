#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

    for (size_t i = 0; i < lines; i++)
    {
        size_t len = strlen(file[i]);
        size_t num_start = 0;
        size_t num_end = 0;

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

                if (i == 0)
                {
                    if (num_start == 0 && num_end < len - 1)
                    {
                        for (size_t j = num_start; j <= num_end; j++)
                            if (file[i + 1][j] != '.' && !(file[i + 1][j] <= '9' && file[i + 1][j] >= '0'))
                                test++;
                        size_t post = num_end;
                        if (file[i][post] != '.' && !(file[i][post] <= '9' && file[i][post] >= '0'))
                            test++;
                    }
                    if (num_start > 0 && num_end < len - 1)
                    {
                        for (size_t j = num_start - 1; j <= num_end; j++)
                            if (file[i + 1][j] != '.' && !(file[i + 1][j] <= '9' && file[i + 1][j] >= '0'))
                                test++;
                        size_t pre = num_start - 1;
                        if (file[i][pre] != '.' && !(file[i][pre] <= '9' && file[i][pre] >= '0'))
                            test++;
                        size_t post = num_end;
                        if (file[i][post] != '.' && !(file[i][post] <= '9' && file[i][post] >= '0'))
                            test++;
                    }
                    if (num_start > 0 && num_end == len - 1)
                    {
                        for (size_t j = num_start - 1; j < num_end; j++)
                            if (file[i + 1][j] != '.' && !(file[i + 1][j] <= '9' && file[i + 1][j] >= '0'))
                                test++;
                        size_t pre = num_start - 1;
                        if (file[i][pre] != '.' && !(file[i][pre] <= '9' && file[i][pre] >= '0'))
                            test++;
                    }
                }
                else if (i < lines - 1)
                {
                    if (num_start == 0 && num_end < len - 1)
                    {
                        for (size_t j = num_start; j <= num_end; j++)
                        {
                            if (file[i + 1][j] != '.' && !(file[i + 1][j] <= '9' && file[i + 1][j] >= '0'))
                                test++;
                            if (file[i - 1][j] != '.' && !(file[i - 1][j] <= '9' && file[i - 1][j] >= '0'))
                                test++;
                        }
                        size_t post = num_end;
                        if (file[i][post] != '.' && !(file[i][post] <= '9' && file[i][post] >= '0'))
                            test++;
                    }
                    if (num_start > 0 && num_end < len - 1)
                    {
                        for (size_t j = num_start - 1; j <= num_end; j++)
                        {
                            if (file[i + 1][j] != '.' && !(file[i + 1][j] <= '9' && file[i + 1][j] >= '0'))
                                test++;
                            if (file[i - 1][j] != '.' && !(file[i - 1][j] <= '9' && file[i - 1][j] >= '0'))
                                test++;
                        }
                        size_t pre = num_start - 1;
                        if (file[i][pre] != '.' && !(file[i][pre] <= '9' && file[i][pre] >= '0'))
                            test++;
                        size_t post = num_end;
                        if (file[i][post] != '.' && !(file[i][post] <= '9' && file[i][post] >= '0'))
                            test++;
                    }
                    if (num_start > 0 && num_end == len - 1)
                    {
                        for (size_t j = num_start - 1; j < num_end; j++)
                        {
                            if (file[i + 1][j] != '.' && !(file[i + 1][j] <= '9' && file[i + 1][j] >= '0'))
                                test++;
                            if (file[i - 1][j] != '.' && !(file[i - 1][j] <= '9' && file[i - 1][j] >= '0'))
                                test++;
                        }
                        size_t pre = num_start - 1;
                        if (file[i][pre] != '.' && !(file[i][pre] <= '9' && file[i][pre] >= '0'))
                            test++;
                    }
                }

                else if (i == lines - 1)
                {
                    if (num_start == 0 && num_end < len - 1)
                    {
                        for (size_t j = num_start; j <= num_end; j++)
                            if (file[i - 1][j] != '.' && !(file[i - 1][j] <= '9' && file[i - 1][j] >= '0'))
                                test++;
                        size_t post = num_end;
                        if (file[i][post] != '.' && !(file[i][post] <= '9' && file[i][post] >= '0'))
                            test++;
                    }
                    if (num_start > 0 && num_end < len - 1)
                    {
                        for (size_t j = num_start - 1; j <= num_end; j++)
                            if (file[i - 1][j] != '.' && !(file[i - 1][j] <= '9' && file[i - 1][j] >= '0'))
                                test++;
                        size_t pre = num_start - 1;
                        if (file[i][pre] != '.' && !(file[i][pre] <= '9' && file[i][pre] >= '0'))
                            test++;
                        size_t post = num_end;
                        if (file[i][post] != '.' && !(file[i][post] <= '9' && file[i][post] >= '0'))
                            test++;
                    }
                    if (num_start > 0 && num_end == len - 1)
                    {
                        for (size_t j = num_start - 1; j < num_end; j++)
                            if (file[i - 1][j] != '.' && !(file[i - 1][j] <= '9' && file[i - 1][j] >= '0'))
                                test++;
                        size_t pre = num_start - 1;
                        if (file[i][pre] != '.' && !(file[i][pre] <= '9' && file[i][pre] >= '0'))
                            test++;
                    }
                }
                if (test)
                {
                    // printf("passed: %s %d, coords: %d %d %d \n", num_buffer, test, i, num_start, num_end);
                    sum += atoi(num_buffer);
                }

                num_start = num_end;
            }
        }
    }

    printf("%d\n", sum);
    return 0;
}
