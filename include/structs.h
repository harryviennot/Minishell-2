/*
** EPITECH PROJECT, 2022
** $
** File description:
** structs
*/

#ifndef STRUCTS_H_
    #define STRUCTS_H_

    typedef struct {
        char *redir;
        char *filename;
        char **args;
        int pipes;
        int save_out;
        int save_in;
        int fd;
    } operator_t;

    typedef struct linked_s {
        char *var;
        char *value;
        struct linked_s *next;
    } linked_t;

#endif
