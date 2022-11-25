/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpicot <rpicot@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 16:27:35 by rpicot        #+#    #+#                 */
/*   Updated: 2022/11/25 15:06:31 by rpicot        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>

/*STRUCT LINKED LIST */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

/*ASCII CLASSIFYING*/
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);

/*BYTES SEARCH*/
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
void	*ft_memchr(const void *s, int c, size_t n);
size_t	ft_strlen(const char *s);

/*STRING SEARCH*/
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

/*STRING COPY AND CONCAT*/
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
void	*ft_memcpy(void *dst, const void *src, size_t n);

/*STRING COMPARISON*/
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);

/*Byte Search*/
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);

//Type casting
int		ft_atoi(const char *str);
char	*ft_itoa(int n);

/*Mallocating stuff*/
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);

/*DYNAMIC OPE STRINGS*/
char	**ft_split(const char *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_strtrim(char const *s1, char const *set);

/*POINTEUR SUR FONCTIONS --> CHARS*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

/*FILE DESCRIPTOR VERSION*/
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putendl_fd(char *s, int fd);

//LINKED LIST CRUD
//create
t_list	*ft_lstnew(void *content);
//read
t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);
//update
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstiter(t_list *lst, void (*f)(void *));
//delete
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
//All
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
