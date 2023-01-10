#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>


char	*ft_itoa(int n);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strchr( char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *src);
char	**ft_split(char const *s, char c);
char	*ft_strtrim(char *s1, char *set);
char	**ft_realoc(char **tab, int size);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	*ft_memset(void *ptr, int c, size_t num);
void	ft_bzero(void *ptr, size_t num);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
int		ft_atoi(const char *str);
bool	ft_isdigit(char *str);
size_t	ft_strlen(char *str);

#endif