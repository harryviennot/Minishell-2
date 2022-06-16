/*
** EPITECH PROJECT, 2022
** B-PSU-101-TLS-1-1-minishell1-harry.viennot
** File description:
** my_setenv
*/

#include "my.h"
#include "include/structs.h"

void my_setenv(linked_t *env, char *var, char *val)
{
    while (env->next != NULL) {
        if (my_strcmp(var, env->var) == 0) {
            env->value = my_strdup(val);
            return;
        }
        else
            env = env->next;
    }
    env->next = malloc(sizeof(linked_t));
    env->var = my_strdup(var);
    env->value = my_strdup(val);
    env->next->next = NULL;
    return;
}

void my_ready_setenv(char **args, linked_t *env)
{
    int len = my_arraylen(args);

    if (len > 3) {
        write(2, "too many arguments to function 'setenv'\n", 40);
        return;
    } else if (len < 2) {
        write(2, "too few arguments to function 'setenv'\n", 39);
        return;
    }
    if (len == 2)
        my_setenv(env, args[1], "");
    else
        my_setenv(env, args[1], args[2]);
    return;
}
