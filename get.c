/*
** EPITECH PROJECT, 2022
** minishell1
** File description:
** get
*/

#include "my.h"
#include "include/structs.h"

int check_if_same(char *file, char *program)
{
    if (my_strcmp(file, program) == 0)
        return 1;
    else
        return 0;
}

char *get_prog_fp(char *program, char *dirpath)
{
    char *file;
    char *filepath = NULL;
    int a = 0;
    DIR *d;
    struct dirent *dir;
    d = opendir(dirpath);
    if (d) {
        while ((dir = readdir(d)) != NULL && a == 0) {
            file = dir->d_name;
            a = check_if_same(file, program);
        }
    }
    if (a == 1)
        filepath = concatenate(dirpath, file);
    closedir(d);
    return filepath;
}

char *my_getenv(char *str, linked_t *env)
{
    int b = 1;
    char *result = NULL;

    while (env->next != NULL) {
        b = my_strcmp(str, env->var);
        if (b == 0) {
            result = env->value;
            break;
        }
        env = env->next;
    }
    return result;
}

char *get_pwd(void)
{
    char *tmp;
    size_t buf = 255;

    tmp = malloc(sizeof(char) * 255);
    getcwd(tmp, buf);
    return tmp;
}
