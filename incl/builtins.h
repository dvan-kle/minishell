/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 16:14:04 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/10/06 17:59:51 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "main.h"

//builtins.c
void	set_new_pwd(t_env_list *env_list);
void	pwd(void);
void	echo(t_cmd_table *cmd_table);

//builtins2.c
void	env(t_env_list *env_list);
void	export(t_env_list *env_list, char **input);
void	unset(t_env_list *env_list, char *input);

//exit.c
void	ft_exit(t_cmd_table *cmd_table);

//cd.c
int		cd(const char *path, t_cmd_table *cmd_table);
void	set_new_pwd(t_env_list *env_list);
char	*replace_pwd(t_env_list *env_list);
void	replace_old_pwd(t_env_list *env_list, char *old_pwd);


#endif