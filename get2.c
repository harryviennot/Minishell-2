/*
** EPITECH PROJECT, 2022
** B-PSU-101-TLS-1-1-minishell1-harry.viennot
** File description:
** get2
*/

#include "my.h"
#include "include/structs.h"

int check_for_redir(char **args)
{
    for (int i = 0; args[i] != NULL; i++) {
        if (my_strcmp(args[i], ">") == 0 || my_strcmp(args[i], ">>") == 0)
            return i;
    }
    return 0;
}

int count_pipes(char *tmp)
{
    int count = 0;

    for (int i = 0; tmp[i] != '\0'; i++) {
        if (tmp[i] == '|')
            count++;
    }
    return count;
}

void get_pipes(operator_t *operators, char *tmp)
{
    char **temp = NULL;
    operators->pipes = count_pipes(tmp);
    if (operators->pipes == 0)
        return;
    temp = create_wordarray(tmp, operators->redir);
    operators->args = create_wordarray(temp[0], "|");
    return;
}

operator_t *get_operators(operator_t *operators, char **args, char *tmp)
{
    int redir = 0;

    operators = malloc(sizeof(operator_t));
    redir = check_for_redir(args);
    if (redir != 0) {
        operators->redir = args[redir];
        operators->filename = args[redir + 1];
        operators->args = args;
        operators->args[redir] = NULL;
        operators->args[redir + 1] = NULL;
    } else {
        operators->redir = "\0";
        operators->filename = NULL;
        operators->args = args;
    }
    get_pipes(operators, tmp);
    return operators;
}

char *get_bin(linked_t *env, char *pgrm)
{
    char **bins = my_str_to_word_array(my_getenv("PATH", env), ':');
    char *prog_fp = NULL;
    for (int i = 0; bins[i] != NULL && prog_fp == NULL; i++) {
        prog_fp = get_prog_fp(pgrm, bins[i]);
    }
    if (prog_fp == NULL)
        my_printf_err("%s: command not found.\n", pgrm);
    return prog_fp;
}
