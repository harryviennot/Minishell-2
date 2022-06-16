/*
** EPITECH PROJECT, 2022
** minishell1
** File description:
** my
*/

#ifndef MY_H_
    #define MY_H_

    #include <stdio.h>
    #include <unistd.h>
    #include <stdlib.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <dirent.h>
    #include <stdarg.h>
    #include <signal.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include "../lib/include/my.h"
    #include "structs.h"

    int my_minishell(linked_t *env);
    char *remove_n(char *tmp);
    void my_cd(char **args, linked_t *env);
    void my_ready_setenv(char **args, linked_t *env);
    void my_setenv(linked_t *env, char *name, char *var);
    void my_unsetenv(char **args, linked_t *env);
    char *remove_p(char *str);
    void get_bins(linked_t *env);
    void run_program(char **args, linked_t *env);
    char *get_prog_fp(char *program, char *dirpath);
    char *concatenate(char *strg1, char *strg2);
    char *my_getenv(char *str, linked_t *env);
    void p_my_env(char **args, linked_t *env);
    int get_name_index(char *str, linked_t *env);
    char *get_pwd(void);
    int check_existing_file(char *filep, char *given_file);
    void check_dir(char *filepath);
    int check_multiple_cmds(char *line);
    int check_exit(char *str, int val);
    operator_t *get_operators(operator_t *operators, char **args, char *tmp);
    void stdout_to_file(operator_t *operators);
    void file_to_stdout(operator_t *operators);
    void my_free_array(char **array);
    void perform_pipes(operator_t *operators, linked_t *env);
    char *get_bin(linked_t *env, char *pgrm);
    int left_redirections(char **args);
    char **list_to_array(linked_t *env);

    struct flag {
        char *attrib;
        void (*find)(char **, linked_t *);
    };

    static struct flag const flag_TAB[] = {
        {"cd", &my_cd},
        {"setenv", &my_ready_setenv},
        {"unsetenv", &my_unsetenv},
        {"env", &p_my_env},
    };

#endif
