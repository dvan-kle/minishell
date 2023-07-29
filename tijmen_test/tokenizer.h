/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 15:45:31 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/07/29 13:49:36 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "../libft/libft.h"
# include <stdbool.h>
# include <stdio.h>

# define MAX_LEN 100

typedef enum token_type{
	CMD_TOKEN,
	ARGUMENT_TOKEN,
	INPUT_REDIRECT_TOKEN,
	OUTPUT_REDIRECT_TOKEN,
	PIPE_TOKEN,
	END_OF_CMD_TOKEN,
	READ_INPUT_TOKEN,
	OUTPUT_REDIRECT_APPEND_TOKEN
}t_tokentype;

typedef struct token{
	t_tokentype	type;
	char		value[MAX_LEN];
	bool		brackets;
	bool		new_cmd;
}t_token;

#endif