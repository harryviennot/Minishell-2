/*
** EPITECH PROJECT, 2022
** B-PSU-101-TLS-1-1-minishell1-harry.viennot
** File description:
** redirect
*/

#include "my.h"
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "include/structs.h"

void my_free_array(char **array)
{
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}

void file_to_stdout(operator_t *operators)
{
    if (operators->redir[0] == '\0')
        return;
    close(operators->fd);
    if (operators->redir[0] == '>')
        dup2(operators->save_out, 1);
    if (operators->redir[0] == '<')
        dup2(operators->save_in, 0);
    free_struct(operators);
}

void stdout_to_file(operator_t *operators)
{
    int fd;

    if (operators->redir[0] == '\0')
        return;
    operators->save_out = dup(STDOUT_FILENO);
    operators->save_in = dup(STDIN_FILENO);
    if (my_strcmp(operators->redir, ">") == 0) {
        fd = open(operators->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(fd, 1);
    }
    if (my_strcmp(operators->redir, ">>") == 0) {
        fd = open(operators->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
        dup2(fd, 1);
    }
    if (my_strcmp(operators->redir, "<") == 0) {
        fd = open(operators->filename, O_RDONLY);
        dup2(fd, 0);
    }
    operators->fd = fd;
}

int left_redirections(char **args)
{
    int fd;
    int i = 0;
    int len;
    int save_in;

    for (i = 0; args[i] != NULL; i++) {
        if (my_strcmp(args[i], "<") == 0)
            break;
    }
    if (args[i] == NULL)
        return -1;
    save_in = dup(STDIN_FILENO);
    fd = open(args[i + 1], O_RDONLY);
    dup2(fd, 0);
    len = my_arraylen(args);
    args[len - 2] = NULL;
    args[len - 1] = NULL;
    return save_in;
}
