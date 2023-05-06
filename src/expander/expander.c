/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 16:36:22 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/05/06 17:46:43 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_free(char *s1, char *s2);
int		len_to_trim(char *str);
int		multi_var(char *str);

/*look for var_name in envp, return a copy of var->value*/
char	*expand_value(char *var_name, t_token *prev, t_data *data, int dquote)
{
	char	*ret;

	if (!ft_strncmp("?", var_name, 2))
		return (ft_itoa(data->exit_code));
	if (!ft_strncmp("", var_name, 2) && dquote)
		return (ft_strdup("$"));
	if (!var_exist(data->envp, var_name))
	{
		if (prev && (prev->type == READ || prev->type == WRITE
				|| prev->type == APPEND))
			ret = ft_strdup(var_name); //this in case of redirection should fail and throw an error ambiguos redirection
		else
			ret = (ft_strdup(""));
	}
	else
		ret = ft_strdup(get_env_value(var_name, data));
	free(var_name);
	return (ret);
}

/*trim part from copy_str and join it with token->word,
if var expands value*/
// int	trim_join(t_token *token, t_token *prev, t_data *data, char *str, int w_len)
// {
// 	char	*tmp;
// 	char	*to_join;

// 	to_join = ft_substr(str, 0, w_len);
// 	if (!to_join)
// 		return (0);
// 	if (to_join[0] == '$' && w_len > 1)
// 	{
// 		tmp = ft_strdup(to_join);
// 		free(to_join);
// 		if (!tmp)
// 			return (0);
// 		to_join = expand_value(tmp, prev, data);
// 		free(tmp);
// 		if (!to_join)
// 			return (0);
// 	}
// 	if (token->word)
// 		token->word = ft_strjoin_free(token->word, to_join);
// 	else
// 		token->word = ft_strjoin_free(ft_strdup(""), to_join);
// 	if (!token->word)
// 		return (0);
// 	return (1);
// }

/*count len part to join to new str, call join_expansion function*/
// int	expand_in_str(t_token *token, t_data *data)
// {
// 	char	*copy;
// 	char	*keep_copy;
// 	int		w_len;

// 	copy = ft_strdup(token->word);
// 	if (!copy)
// 		return (0);
// 	keep_copy = copy;
// 	free(token->word);
// 	token->word = 0;
// 	while (*copy)
// 	{
// 		w_len = len_to_trim(copy);
// 		if (w_len && !(w_len == 1 && *copy == '$'
// 				&& ((*(copy + 1) == '\'') || *(copy + 1) == '\"')))
// 		{
// 			if (!trim_join(token, data, copy, w_len))
// 				return (free(keep_copy), 0);
// 		}
// 		copy += w_len;
// 	}
// 	free(keep_copy);
// 	return (1);
// }

// int	expand_in_str(t_token *token, t_token *prev, t_data *data)
// {
// 	char	*copy;
// 	char	*keep_copy;
// 	int		w_len;

// 	copy = ft_strdup(token->word);//get a copy of value
// 	if (!copy)
// 		return (0);
// 	keep_copy = copy;
// 	free(token->word);
// 	token->word = 0;
// 	while (*copy)
// 	{
// 		w_len = len_to_trim(copy);
// 		if (w_len && !(w_len == 1 && *copy == '$'
// 				&& ((*(copy + 1) == '\'') || *(copy + 1) == '\"')))
// 		{
// 			if (!trim_join(token, prev, data, copy, w_len))
// 				return (free(keep_copy), 0);
// 		}
// 		copy += w_len;
// 	}
// 	free(keep_copy);
// 	return (1);
// }

/*check if expand in a str(quoted) or only var name*/
// int	expand_check(t_token *token, t_token *prev, t_data *data)
// {
	//char	*new_value;

	// if (token->word[0] == '$' && ft_strlen(token->word) > 1
	// 	&& ft_isalpha(token->word[1]) && !multi_var(token->word))
	// {
	// 	new_value = expand_value(token->word, prev, data);
	// 	if (!new_value)
	// 		return (0);
	// 	free(token->word);
	// 	token->word = new_value;
	// }
	// else
	// {
		// if (!expand_in_str(token, prev, data))
		// 	return (0);
	//}
	//return (1);
//}



int	add_to_new_value(char **new, char *to_add)
{
	if (*new)
		*new = ft_strjoin_free(*new, to_add);
	else
		*new = ft_strjoin_free(ft_strdup(""), to_add);
	if (!*new)
		return (0);
	return (1);
}

char	*trim_var_name(char *str)
{
	int	len;

	len = 1;

	if ((*(str + 1) == '?' || ft_isdigit(*(str + 1))))
		len++;
	while (*(str + len) && (ft_isalpha(*(str + len)) || ft_isdigit(*(str + len)) || *(str + len) == '_'))
		len++;
	if (len == 1)
		return (ft_strdup(""));
	return (ft_substr(str, 1, len));
}

char	*expand_str(char *str, t_token *prev, t_data *data)//remember to free str
{
	char	*new_value = NULL;
	char	*var_name;
	char	*quoted_str;
	int		quote = 0;
	int		d_quote = 0;
	int		w_len = 0;
	
	while (*str)
	{
		if(*str != '$' || quote) //nothing to expand
		{
			if (*str == '\'' || *str == '\"')
			{
				quote_check(&quote, &d_quote, *str);
				if (*str == '\"')
				{
					while ()
					quoted_str = ft_substr()
					if (!add_to_new_value(&new_value, expand_str(str, prev, data)))
						return (0);
				}
				else 
				{
					if (!add_to_new_value(&new_value, ft_substr(str, 0, 1)))
						return (0); //error malloc
					str++;
				}
			}
		}
		else //if there is a dollar sign
		{
			var_name = trim_var_name(str); //trim the var name
			printf("var_name = %s\n", var_name);
			if (!var_name)
				return (0);// malloc error
			if(!add_to_new_value(&new_value, expand_value(var_name, prev, data, d_quote))) //add expanded value to new_value
					return (0);
			str = str + ft_strlen(var_name) + 1;
		}
	}
	return (new_value);
}

//parse tokens and check if there is a var to expand
int	expander(t_data *data)
{
	t_token	*ptr;
	t_token	*prev;
	char	*new_value;

	ptr = data->token;
	prev = 0;
	while (ptr)
	{
		if (ft_strchr(ptr->word, '$'))
		{
			new_value = expand_str(ft_strdup(ptr->word), prev, data);
			if (!new_value)
				return (107);
			free(ptr->word);
			ptr->word = new_value;
		}
		prev = ptr;
		ptr = ptr->next;
	}
	return (0);
}