char	*ft_strchr(const char *s, int c)
{
	int		index;

	index = 0;
	while (*(s + index))
	{
		if (s[index] == (char)c)
			return ((char *)s + index);
		index++;
	}
	 if (s[index] == (char)c && (char)c == '\0')
		return ((char *)s + index);
	return (0);
}
