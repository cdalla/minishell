#include "./../minishell.h"


int get_text(char *delimitor, char **str, char **res, char *end_dquote)
{
    char *substr;

    if(!delimitor || delimitor > end_dquote)
        delimitor = end_dquote;
    if(*str < delimitor)
    {
        substr = ft_substr(*str, 0, delimitor - *str);
        *res = ft_strjoin_free(*res, substr);
        if(!*res || !substr)
            return(0);
    }
    *str = delimitor;
    return (1);
}


int replace_var(char **str, char *temp, char **res, t_envp *envp)
{
    char *env_name;
    char *env_value;
    char *tmp;

    (*str)++;
    env_name = ft_substr(*str, 0, temp - *str);
    if(!env_name)
        return(0);
    env_value = get_envp(envp, env_name);
    if(!*res)
        *res = ft_strdup("");
    tmp = ft_strjoin(*res, env_value);
    free(*res);
    *res = tmp;
    free(env_name);
    if(!res)
        return(0);
    return(1);
}

int quote_resolver(char **str, char **res)
{
    char *end_quote;
    char *substr;
    char *strduped;

    (*str)++;
    end_quote = ft_strchr(*str, '\'');
    if (!(end_quote - *str))
    {
        strduped = ft_strdup("\'\'");
        *res = ft_strjoin_free(*res, strduped);
        if(!*res || !strduped)
            return (0);
    }
    else
    {
        substr = ft_substr(*str, 0, end_quote - *str);
        *res = ft_strjoin_free(*res, substr);
        if(!*res || !substr)
            return (0);
    }
    *str = end_quote; 
    return(1);
}
int dquote_resolver(char **str, char **res, t_envp *envp)
{
    char *end_dquote;
    char *dollar;
    char *temp;
    char *dupped;

    ++*str;
    while(*str < (end_dquote = ft_strchr(*str, '"')))
    {
        dollar = ft_strchr(*str, '$');
        if(!get_text(dollar, str, res, end_dquote))
            return(0);
        if(*str == dollar)
        {
            temp = (*str) + 1;
            while(*temp != '$' && *temp != '"')
                temp++;
            if (temp == (*str + 1) && *temp == '\"')
            {
                dupped = ft_strdup("$");
                *res = ft_strjoin(*res, dupped);
                if(!*res || !dupped)
                    return(0);
            }
            else if(!replace_var(str, temp, res, envp))
                return(0);
            *str = temp + 1; 
        }
    }

    return(1);

}

char *choose_delimitor(char *str)
{
    while(*str != '\'' && *str != '\"' && *str != '$' && *str)
        str++;
    return(str);
}

int plain_resolver(char **str, char **res, t_envp *envp)
{    
    char *temp;
    char *dollar;
    char *dupped;
    char *delimitor;

    while(**str != '\'' && **str != '\"' && **str)
    {
        dollar = ft_strchr(*str, '$');
        delimitor = choose_delimitor(*str);
        if(!get_text(delimitor, str, res, choose_delimitor(*str)))
             return(0);
        if(*str == dollar)
        {
            temp = *str + 1;
            while(*temp != '\'' && *temp != '\"' && *temp != '$' && *temp)
                temp++;
            if (temp == *str + 1 && (*temp == '\'' || *temp == '\"')
                 && (*(temp + 1) == '\'' || *(temp + 1) == '\"'))
            {
                dupped = ft_strdup("\"\"");
                *res = ft_strjoin_free(*res, dupped);
                if(!*res || !dupped)
                    return(0);
            }
            else if(!replace_var(str, temp, res, envp))
                return(0);
            *str = temp; 
        }
    }
    return(1);
}

int expander(t_data *data)
{
    t_token *tokens;
    char    *str;
    char    *res;
    
    res = NULL;
    tokens = data->token;
    while(tokens)
    {
        str = tokens->word;
        while(*str)
        {
            if(*str == '\'')
            {
                 if(!quote_resolver(&str, &res))
                    return(0);
            }
            else if(*str == '\"')
            {
                if(!dquote_resolver(&str, &res, data->envp))
                    return(0);
            }
            else
                if(!plain_resolver(&str, &res, data->envp))
                    return(0);
            str++;
        }
        tokens = tokens->next;
        printf("%s\n", res);
    }

    return(1);
}