#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void count_characters(FILE *file) 
{
    int count = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) 
    {
        count++;
    }
    printf("字符数：%d\n", count);
}

void count_words(FILE *file) 
{
    int count = 0;
    int in_word = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) 
    {
        if (ch == ' ' || ch == ',') 
        {
            if (in_word) 
            {
                in_word = 0;
                count++;
            }
        } 
        else 
        {
            in_word = 1;
        }
    }
    if (in_word) 
    {
        count++;
    }
    printf("单词数：%d\n", count);
}

int main(int argc, char *argv[]) 
{
    if (argc != 3) 
    {
        fprintf(stderr, "用法: %s [-c|-w] [input_file_name]\n", argv[0]);
        return 1;
    }

    char *parameter = argv[1];
    char *input_file_name = argv[2];

    FILE *file = fopen(input_file_name, "r");
    if (file == NULL) 
    {
        perror("无法打开文件");
        return 1;
    }

    if (strcmp(parameter, "-c") == 0) 
    {
        count_characters(file);
    } 
    else if (strcmp(parameter, "-w") == 0) 
    {
        count_words(file);
    } 
    else 
    {
        fprintf(stderr, "无效的参数: %s\n", parameter);
        fclose(file);
        return 1;
    }

    fclose(file);
    return 0;
}
