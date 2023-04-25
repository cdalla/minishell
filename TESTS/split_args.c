int	split_args(char **split, char *str, char c)
{
	int		w_len;

	w_len = 0;
	while (*(str + w_len) != c && *(str + w_len)) //count until = sign
		w_len++;
	if (w_len)	//if w_len > 0 there is something
		split[0] = ft_substr(str, 0, w_len);
	if (!split[0])
		return (0);
	str += (w_len + 1); //move the pointer after the first word skips the = sign
	w_len = 0;
	while (*(str + w_len)) //count len of value
		w_len++;
	if (w_len) //if value is something trim it
	{
		split[1] = ft_substr(str, 0, w_len); 
		if (!split[1])
			return (free(split[0]), 0);
	}
	else // if there is no value, if there is = -> value == "\0", if no = value == NULL
	{
		if (*(str + w_len - 1) == '=') //if previous char is = need to create value 
		{
			split[1] = ft_strdup("\0");
			if (!split[1])
				return (free(split[0]), 0);
		}
		else //if there is no = then empty value
			split[1] = 0;
	}
	return (1);
}

int	*trim_arg1(char **split, char *str, char c)
{
	int		w_len;

	w_len = 0;
	while (*(str + w_len) != c && *(str + w_len))
		w_len++;
	if (w_len)	//if w_len > 0 there is something
		split[0] = ft_substr(str, 0, w_len);
	if (!split[0])
		return (0); //failed malloc
	return (1);
}

int	*trim_arg2(char **split, char *str)
{
	int		w_len;

	w_len = 0;
	while (*(str + w_len)) //count len of value
		w_len++;
	if (w_len) //if value is something trim it
	{
		split[1] = ft_substr(str, 0, w_len); 
		if (!split[1])
			return (0);
	}
	else // if there is no value, if there is = -> value == "\0", if no = value == NULL
	{
		if (*(str + w_len - 1) == '=') //if previous char is = need to create value 
		{
			split[1] = ft_strdup("\0");
			if (!split[1])
				return (0);
		}
		else //if there is no = then empty value
			split[1] = 0;
	}
	return (1);
}

int	split_args(char **split, char *str, char c)
{
	if (!trim_arg1(split, str, c))
		return (0);
	else
		str += (ft_strlen(split[0]) + 1);
	if (!trim_arg2(split, str))
		return (free(split[0]), 0);
	return (1);
}





/*create new envp node and fill some fields*/
t_envp	*new_envp(char *arg, enum e_var_type type)
{
	t_envp	*new_node;
	char	**args;

	new_node = (t_envp *)malloc(sizeof(t_envp)); //malloc new node
	if (!new_node)
		return (0);
	new_node->input = ft_strdup(arg); //copy input
	if (!new_node->input)
		return (new_node, 0);
	args = split_var(arg, '='); //split args
	if (!args) //malloc fail in split args
		return (0); //free new_node
	if (!fill_env)
		return (free(new_node, 0))
	new_node->type = type;
	new_node->next = 0;
	new_node->prev = 0;
	return (free(args[0]), free(args[1]), free(args), new_node); 
}

int	fill_env(t_envp *new, char **args)
{
	if (args[0])
	{
		new->env = ft_strdup(args[0]);
		if (!new->env) //if malloc fail
		{
			if (args[1])
				free(args[1]);
			return (free(args), free(args), 0); //free new node
		}
	}
	if (args[1]) //if value is something or '\0'
	{
		new->value = ft_strdup(args[1]); //copy value
		if (!new->value)
			return (free(args[0]), free(args[1]), free(args), 0); //if malloc fail free, free new_node
	}
	else
		new->value = NULL; //if no value and no = empty
	return (1);
}