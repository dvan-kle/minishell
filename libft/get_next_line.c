/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 15:17:59 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/02/21 11:40:24 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*gnl_strjoin(char const *str1, char const *str2)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str1)
		str1 = ft_calloc(1, sizeof(char));
	if (!str1)
		return (NULL);
	ptr = malloc((sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1)));
	if (!ptr)
		return (NULL);
	while (str1 && str1[i])
	{
		ptr[i] = str1[i];
		i++;
	}
	while (str2[j])
	{
		ptr[i + j] = str2[j];
		j++;
	}
	ptr[i + j] = '\0';
	return (free((char *)str1), ptr);
}

// gets the correct line to return
char	*returned_line(char *str)
{
	char	*good_line;
	int		i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		good_line = ft_calloc((i + 2), sizeof(char));
	else
		good_line = ft_calloc((i + 1), sizeof(char));
	if (!good_line)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		good_line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		good_line[i] = str[i];
	return (good_line);
}

//leftover of buff is put into new_string
char	*leftover_buff(char *str)
{
	int		i;
	int		j;
	char	*new_string;

	i = 0;
	j = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\0')
		return (free(str), NULL);
	i++;
	new_string = ft_calloc(ft_strlen(str) - i + 1, sizeof(char));
	if (!new_string)
		return (NULL);
	while (str[i])
	{
		new_string[j] = str[i];
		i++;
		j++;
	}
	free(str);
	return (new_string);
}

// reads the file
// put all of buffer into str
char	*read_file(int fd, char *str)
{
	char	*buff;
	int		bytes_read;

	bytes_read = 1;
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	while (!ft_strchr(str, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buff), free(str), NULL);
		buff[bytes_read] = '\0';
		str = gnl_strjoin(str, buff);
		if (!str || str[0] == '\0')
		{
			free(str);
			free(buff);
			return (NULL);
		}
	}
	free(buff);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_file(fd, line);
	if (!line)
		return (NULL);
	ret = returned_line(line);
	if (!ret)
		return (free(ret), NULL);
	line = leftover_buff(line);
	return (ret);
}
