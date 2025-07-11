/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:25:15 by antbonin          #+#    #+#             */
/*   Updated: 2025/06/27 19:17:39 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdarg.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
#  define HEXACAPS "0123456789ABCDEF"
#  define HEXAMIN "0123456789abcdef"

# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

# define HEXA_CAPS "0123456789ABCDEF"
# define HEXA_MIN "0123456789abcdef"

/**************************************************************/

int					ft_printhexa(int fd, unsigned long int n, char hex);
int					ft_printf(const char *format, ...);
int					ft_printf_fd(int fd, const char *format, ...);
int					ft_printf_format(int fd, char format, va_list arg);
int					ft_printdecimal(int fd, long int n);
int					ft_printpointer(int fd, void *s);

/***************************************************************/

int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);

/****************************************************************/

size_t				ft_strlen(const char *str);
int					ft_aclen(char **str);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
size_t				ft_strlcpy(char *src, const char *dst, size_t n);
size_t				ft_strlcat(char *src, const char *dest, size_t n);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strcpy(char *dest, const char *src);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
int					ft_atoi(const char *nptr, int *test);
int					ft_memcmp(const void *ptr1, const void *ptr2, size_t num);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
char				*ft_strdup(const char *s);
char				*ft_substr(const char *str, unsigned int start, size_t len);
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strjoin3(const char *s1, const char *s2,
						const char *s3);
void				*ft_calloc(size_t count, size_t size);
char				*ft_itoa(int n);
long long			ft_atoll(const char *str, int *error);

/*******************************************************************/

int					ft_putstr_fd(char *s, int fd);
int					ft_putnbr_fd(long int n, int fd);
int					ft_putchar_fd(char c, int fd);
char				*ft_strtrim(const char *s1, const char *set);
void				ft_putendl_fd(char *s, int fd);
char				**ft_split(char *str, char c);
void				free_tab(char **tab);
char				*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char				*ft_striteri(char *s, void (*f)(unsigned int, char *));

/********************************************************************/

void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstnew(void *content);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

/**********************************************************************/

char				*ft_strdup_gnl(const char *src);
char				*ft_strjoin_gnl(char *dest, const char *src);
size_t				ft_strlen_gnl(const char *str);
char				*get_next_line(int fd);
int					ft_strcmp(char *s1, char *s2);

#endif