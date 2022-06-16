/*
** EPITECH PROJECT, 2022
** B-PSU-210-TLS-2-1-minishell2-harry.viennot
** File description:
** execute
*/

#include "include/my.h"

void run_program(char **args, linked_t *env)
{
    int status;
    int ret;
    pid_t fork_val = fork();

    if (fork_val == 0) {
        ret = execve(args[0], args, list_to_array(env));
        if (ret == -1)
            check_dir(args[0]);
        exit(0);
    }
    waitpid(fork_val, &status, 0);
    if (status == 139)
        my_puterr("Segmentation fault\n");
    free_array(args);
}
