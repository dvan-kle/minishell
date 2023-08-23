/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 13:48:40 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/08/21 16:46:03 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_env_list	t_env_list;
typedef struct s_env_list
{
	char		*key;
	char		*value;
	t_env_list	*next;
}t_env_list;

t_env_list	*make_env_list(char	**envp);
void		env_add_back(char *env, t_env_list **env_list);

#endif
