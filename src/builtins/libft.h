/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 15:43:31 by tde-brui      #+#    #+#                 */
<<<<<<< HEAD:src/builtins/libft.h
/*   Updated: 2023/07/25 16:01:19 by dvan-kle      ########   odam.nl         */
=======
/*   Updated: 2023/08/02 13:03:39 by tde-brui      ########   odam.nl         */
>>>>>>> master:libft/libft.h
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_node{
	int				index;
	int				data;
	struct s_node	*next;
}t_list;

void		ft_bzero(void *str, size_t size);
void		*ft_calloc(size_t num, size_t size);
int			ft_isalnum(int a);
int			ft_isalpha(int a);
int			ft_isascii(int a);
int			ft_isdigit(int a);
int			ft_isprint(int a);
int			ft_isspace(int c);
void		*ft_memcpy(void *dest, const void *src, size_t size);
void		*ft_memmove(void *dest, const void *src, size_t num);
void		*ft_memset(void *str, int val, size_t size);
char		*ft_strchr(const char *str, int character);
char		*ft_strdup(const char *str);
size_t		ft_strlcat(char *dest, const char *src, size_t size);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
size_t		ft_strlen(const char *str);
int			ft_strncmp(const char *str1, const char *str2, size_t size);
char		*ft_strnstr(const char *str1, const char *str2, size_t size);
void		*ft_memchr(const void *ptr, int value, size_t size);
char		*ft_strrchr(const char *str, int a);
char		*ft_substr(char const *str, unsigned int start, size_t len);
int			ft_tolower(int a);
int			ft_toupper(int a);
int			ft_atoi(const char *str);
int			ft_memcmp(const void *s1, const void *s2, size_t size);
char		*ft_strjoin(char const *str1, char const *str2);
char		*ft_strtrim(char const *s, char const *d);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
char		**ft_split(char const *str1, char c);
char		*get_next_line(int fd);
int			ft_stringsnum(char const *str1, char c);
int			ft_printf(const char *str, ...);
int			printf_putstr(char *str);
int			printf_putchar(int c);
int			ft_hexa_len(unsigned int n);
int			ft_get_int(int n);
int			ft_unsigned_dec(unsigned int num);
int			ft_lower_hexa(unsigned int n);
int			ft_upper_hexa(unsigned int n);
int			ft_put_addr(void *ptr);
int			ft_len(int n);
int			list_len(t_list **stack);
t_list		*list_new(int value);

#endif
