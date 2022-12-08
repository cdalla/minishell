int	ft_atoi(const char *str)
{
	int	index;
	int	num;
	int	sign;

	index = 0;
	num = 0;
	sign = 1;
	while (str[index] == '\t' || str[index] == '\v' || str[index] == '\f'
		|| str[index] == '\r' || str[index] == '\n' || str[index] == ' ')
		index++;
	if (str[index] == '-')
	{
		sign = -sign;
		index++;
	}
	else if (str[index] == '+')
		index++;
	while (str[index] >= '0' && str[index] <= '9')
	{
		num = num * 10 + (str[index] - 48);
		index++;
	}
	return (num * sign);
}
