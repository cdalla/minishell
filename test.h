#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize);
void	*ft_memset(void *dest, int c, size_t len);

#endif