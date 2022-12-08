char	*ft_strrchr(const char *s, int c)
{
	int		index;
	char	*ptr;

	index = 0;
	ptr = 0;
	while (s[index])
	{
		if (s[index] == (char)c)
			ptr = (char *)s + index;
		index++;
	}
	if (s[index] == (char)c)
		return ((char *)s + index);
	return (ptr);
}
