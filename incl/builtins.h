#ifndef BUILTINS_H
# define BUILTINS_H

# include "main.h"

//builtins.c
int cd(const char *path);
void pwd(void);
void echo(t_cmd_table *cmd_table);

//builtins2.c
void	env(t_env_list *env_list);
void	export(t_env_list *env_list, char *input);
void	unset(t_env_list *env_list, char *input);

//exit.c
void	ft_exit(t_cmd_table *cmd_table);

#endif