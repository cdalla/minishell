#include <stdio.h>
#include "minishell.h"


// void increase(char **str, int *value)
// {
// 	int i = 0;
// 	while (i < 4)
// 	{
// 		printf("%c\n", *(*str + i));
// 		//(*str)++;
// 		(*value)++;
// 		i++;
// 	}
// }

// int main (void)
// {
// 	char *str = "ciao mona";
// 	int value = 0;
// 	increase(&str, &value);
// 	printf("%s and %d\n", str, value);
// 	return (0);
// }

int add_token(t_token **token, char *word, int type);

int	is_space(int c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == ' ' || c == '\n')
		return (1);
	return (0);
}

int quote_check(int value)
{
	if (value == 0)
	{	
		//*value = 1;
		return (1);
	}
	//*value = 0;
	return (0);
}

void    print_tokens(t_token *token) //print only one var or more? 
{
	t_token	*ptr;

	ptr = token;
    while(ptr)
    {
    	printf("\"%s\" type = %d\n", ptr->word, ptr->type);
        ptr = ptr->next;
    }
}


char	*trim_word(char **str, int *w_len)
{
	char	*word;
	int		quote;
	int		dquote;

	quote = 0;
	dquote = 0;
	while (is_space(**str) && **str != '\0')
		(*str)++;
	while (((!is_space(*(*str + *w_len))) || quote || dquote)
			&& *(*str + *w_len) != '\0')
	{
		if (*(*str + *w_len) == '\'')
			quote = quote_check(quote);
		if (*(*str + *w_len) == '\"')
			dquote = quote_check(dquote);
		(*w_len)++;
	}
	if (*w_len)
		word = ft_substr(*str, 0, *w_len);
	if (!word)
		return (0);
	return (word);
}
int	type_recogn(char *word)
{
	if (!ft_strncmp(word, "||", 3))
		return (PIPE);
	else if (!ft_strncmp(word, "<", 2))
		return (REDI);
	else if (!ft_strncmp(word, ">", 2))
		return (REDO);
	else if (!ft_strncmp(word, ">>", 3))
		return (REDOA);
	else if (!ft_strncmp(word, "<<", 2))
		return (HERED);
	else
		return (WORD);
}

/*
	split input into words and put it directly into token list
*/
int tokenize(char *str, t_data *data)
{
	int		w_len;
	char	*word;
	int		type;

	while (*str)
	{
		type = 0;
		w_len = 0;
		word = trim_word(&str, &w_len);
		if (!word)
			return (0); //failure error in substr
		type = type_recogn(word);
		if (!add_token(&data->token, word, type)) // type not recognized yet, to change or to evaluate later
			return (0); //failed malloc
		str += w_len;
	}
	return (1); //success
}


int main(void)
{
	t_data	data;

	data.token = NULL;
	//char *str = "cat -e \"hello chico\"";
	//char *str = "cat -e hello";
	char *str = "echo > \"ciao\'Rafa\'nice >> covid\" >> ||";

	// add_token(&data.token, "ciao", 0);
	// add_token(&data.token, "ciao", 0);
	// add_token(&data.token, "ciao", 0);
	tokenize(str, &data);
	print_tokens(data.token);
}


//	while (!is_space((*(*str + *w_len)) || quote_check(&quote, (*(*str + *w_len)))
			//|| quote_check(&dquote, (*(*str + *w_len))))