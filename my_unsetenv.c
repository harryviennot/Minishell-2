/*
** EPITECH PROJECT, 2022
** B-PSU-101-TLS-1-1-minishell1-harry.viennot
** File description:
** my_unsetenv
*/

#include "my.h"
#include "include/structs.h"

void my_unsetenv(char **args, linked_t *env)
{
    while (env->next != NULL) {
        if (my_strcmp(args[1], env->next->var) == 0) {
            env->next = env->next->next;
            return;
        }
        env = env->next;
    }
    return;
}
