/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 15:45:31 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/07/25 16:50:54 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H
# define MAX_LEN 100
# include "../libft/libft.h"

typedef enum token_type{
	CMD_TOKEN,
	ARGUMENT_TOKEN,
	INPUT_REDIRECT_TOKEN,
	OUTPUT_REDIRECT_TOKEN,
	PIPE_TOKEN,
	END_OF_CMD_TOKEN
}t_tokentype;

typedef struct token{
	t_tokentype	type;
	char		value[MAX_LEN];
}t_token;

#endif