/*
** EPITECH PROJECT, 2022
** B-PSU-210-TLS-2-1-minishell2-harry.viennot
** File description:
** pipes
*/

#include "my.h"
#include "include/structs.h"

int first_fork(operator_t *operators, int *fd[], linked_t *env)
{
    char **tmp = create_wordarray(operators->args[0], " ");
    char *prgm = get_bin(env, tmp[0]);
    int save_in;
    if (prgm == NULL)
        return -1;
    save_in = left_redirections(tmp);
    int pid1 = fork();
    if (pid1 == 0) {
        dup2(fd[0][1], STDOUT_FILENO);
        for (int i = 0; i < operators->pipes; i++) {
            close(fd[i][0]);
            close(fd[i][1]);
        }
        execve(prgm, tmp, list_to_array(env));
        exit(0);
    }
    if (save_in != -1)
        dup2(save_in, 0);
    return pid1;
}

int middle_forks(operator_t *operators, int *fd[], linked_t *env, int i)
{
    char **tmp = create_wordarray(operators->args[i], " ");
    char *prgm = get_bin(env, tmp[0]);
    int save_in;
    if (prgm == NULL)
        return -1;
    save_in = left_redirections(tmp);
    int pid = fork();
    if (pid == 0) {
        dup2(fd[i - 1][0], STDIN_FILENO);
        dup2(fd[i][1], STDOUT_FILENO);
        for (int j = 0; j < operators->pipes; j++) {
            close(fd[j][0]);
            close(fd[j][1]);
        }
        execve(prgm, tmp, list_to_array(env));
        exit(0);
    }
    if (save_in != -1)
        dup2(save_in, 0);
    return pid;
}

int last_fork(operator_t *operators, int *fd[], linked_t *env)
{
    char **tmp = create_wordarray(operators->args[operators->pipes], " ");
    char *prgm = get_bin(env, tmp[0]);
    int save_in;
    if (prgm == NULL)
        return -1;
    save_in = left_redirections(tmp);
    int pid = fork();
    if (pid == 0) {
        dup2(fd[operators->pipes - 1][0], STDIN_FILENO);
        for (int i = 0; i < operators->pipes; i++) {
            close(fd[i][0]);
            close(fd[i][1]);
        }
        execve(prgm, tmp, list_to_array(env));
        exit(0);
    }
    if (save_in != -1)
        dup2(save_in, 0);
    return pid;
}

void waits(operator_t *operators, int *pids)
{
    int status;
    int i = 0;

    while (operators->pipes-- > 0) {
        status = 0;
        if (waitpid(pids[i], &status, 0) == -1)
            my_putstr("ERROR");
        if (WTERMSIG(status) == 11)
            my_putstr("Segmentation fault (core dumped)\n");
        if (WIFSTOPPED(status))
            my_putstr("Stopped\n");
        i++;
    }
}

void perform_pipes(operator_t *operators, linked_t *env)
{
    int **fd = malloc(sizeof(int *) * operators->pipes);
    int *pids = malloc(sizeof(int) * operators->pipes);
    for (int i = 0; i < operators->pipes; i++) {
        fd[i] = malloc(sizeof(int) * 2);
        pipe(fd[i]);
    }
    pids[0] = first_fork(operators, fd, env);
    for (int i = 1; i < operators->pipes; i++) {
        pids[i] = middle_forks(operators, fd, env, i);
    }
    pids[operators->pipes - 1] = last_fork(operators, fd, env);
    for (int i = 0; i < operators->pipes; i++) {
        close(fd[i][0]);
        close(fd[i][1]);
    }
    waits(operators, pids);
}
