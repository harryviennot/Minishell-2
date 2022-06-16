/*
** EPITECH PROJECT, 2022
** minishell1
** File description:
** main
*/

#include "my.h"
#include "include/structs.h"

char **split_str(char *str, char c)
{
    char **array = malloc(sizeof(char *) * 3);
    int i = 0;
    int j = 0;

    for (i = 0; str[i] != c; i++);
    array[0] = malloc(sizeof(char) * (i + 1));
    array[1] = malloc(sizeof(char) * (my_strlen(str) - i));
    for (j = 0, i = 0; str[i] != c; i++, j++)
        array[0][j] = str[i];
    array[0][j] = '\0';
    i++;
    for (j = 0; str[i] != '\0'; i++, j++)
        array[1][j] = str[i];
    array[1][j] = '\0';
    array[2] = NULL;
    return array;
}

linked_t *create_linked_list(char **envi, linked_t *env)
{
    env = malloc(sizeof(linked_t));
    char **temp2 = split_str(envi[0], '=');
    env->var = temp2[0];
    env->value = temp2[1];
    env->next = NULL;
    linked_t *head = env;

    for (int i = 1; envi[i] != NULL; i++) {
        env->next = malloc(sizeof(linked_t));
        temp2 = split_str(envi[i], '=');
        env->next->var = temp2[0];
        env->next->value = temp2[1];
        env->next->next = NULL;
        env = env->next;
    }
    return head;
}

char **list_to_array(linked_t *env)
{
    int i = 0;
    char **array = NULL;
    linked_t *temp = env;

    while (temp->next != NULL) {
        i++;
        temp = temp->next;
    }
    array = malloc(sizeof(char *) * (i + 1));
    for (int j = 0; j <= i; j++) {
        array[j] = env->var;
        array[j] = my_strcat(array[j], "=");
        array[j] = my_strcat(array[j], env->value);
        env = env->next;
    }
    array[i] = NULL;
    return array;
}

void p_my_env(char **args, linked_t *env)
{
    while (env->next != NULL) {
        my_printf("%s=%s\n", env->var, env->value);
        env = env->next;
    }
    return;
}

int main(int ac, char **av, char **envi)
{
    linked_t *env = NULL;
    env = create_linked_list(envi, env);
    if (ac == 1) {
        my_minishell(env);
    } else
        return 84;
    return 0;
}
