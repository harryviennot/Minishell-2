/*
** EPITECH PROJECT, 2022
** minishell1
** File description:
** minishell
*/

#include "my.h"
#include "include/structs.h"

void built_in(char **args, linked_t *env)
{
    char **bins = my_str_to_word_array(my_getenv("PATH", env), ':');
    char *prog_fp = NULL;
    for (int i = 0; bins[i] != NULL && prog_fp == NULL; i++) {
        prog_fp = get_prog_fp(args[0], bins[i]);
    }
    if (prog_fp == NULL)
        my_printf_err("%s: command not found.\n", args[0]);
    else {
        args[0] = prog_fp;
        run_program(args, env);
    }
}

void check_da_program2(char **args, linked_t *env, int save_in)
{
    if (count_occurences(args[0], '/') != 0)
        run_program(args, env);
    else
        built_in(args, env);
    if (save_in != -1)
        dup2(save_in, 0);
}

void check_da_program(char *tmp, linked_t *env)
{
    char **args = create_wordarray(tmp, " \t");
    operator_t *operators = get_operators(operators, args, tmp);
    stdout_to_file(operators);
    if (operators->pipes > 0) {
        perform_pipes(operators, env);
        file_to_stdout(operators);
        return;
    }
    int save_in = left_redirections(args);
    for (int i = 0; i < 4; i++) {
        if (my_strcmp(flag_TAB[i].attrib, args[0]) == 0) {
            flag_TAB[i].find(args, env);
            file_to_stdout(operators);
            return;
        }
    }
    check_da_program2(args, env, save_in);
    file_to_stdout(operators);
    return;
}

void ready_for_program(char *tmp, linked_t *env)
{
    char **cmds = NULL;

    if (my_strlen(tmp) == 1 && tmp[0] == '\n')
        return;
    tmp = remove_n(tmp);
    if (check_multiple_cmds(tmp) == 1) {
        cmds = my_str_to_word_array(tmp, ';');
        for (int i = 0; cmds[i] != NULL; i++) {
            check_da_program(cmds[i], env);
        }
        my_free_array(cmds);
        return;
    }
    check_da_program(tmp, env);
    return;
}

int my_minishell(linked_t *env)
{
    int b = 1;
    int val;
    char *tmp = NULL;
    size_t buf = 32;

    do {
        write(1, "$> ", 3);
        val = getline(&tmp, &buf, stdin);
        if (check_exit(tmp, val) == 0)
            return 0;
        ready_for_program(tmp, env);
    } while (b);
    return 0;
}
