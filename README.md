# Minishell-2

- **Language:** C

# Subject

The goal of the project is to enrich your minishell1 project by adding semicolons (‘;’), pipes (‘|’), and the four redirections (‘>’, ‘<’, ‘>>’, ‘<<’) management.
Here is a simple example of a command you must hanlde:

```
∼/B-PSU-210> ./mysh
> mkdir test ; cd test ; ls -a ; ls | cat | wc -c > tutu ; cat tutu
...
5
>
```

> :bulb: Error output, standard input and standard output redirections will be considered as bonuses.

## Authorized functions

- malloc, free, exit, opendir, readdir, closedir, getcwd, chdir
- fork, stat, lstat, fstat, open, close, getline
- read, write, execve, isatty, wait, waitpid
- wait3, wait4, signal, kill, getpid, strerror, perror, strsignal
- pipe, dup, dup2
