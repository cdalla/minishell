#include "./../minishell.h"


/*
int get_text(char *dollar, char *str, char **res)
{
    if(!dollar || str < dollar)
    {
        *res = ft_strjoin_free(*res, ft_substr(str, 0, dollar - str));
        if(!*res)
            return(0);
    }
}

int replace_var(char *str, char *temp, char **res, t_envp *envp)
{
    char *to_free;
    char *env_value;

    to_free = ft_substr(str, 0, temp - str);
    if(!to_free)
        return(0);
    env_value = get_envp(envp, to_free);
    *res = ft_strjoin_free(*res, env_value);)
    free(to_free);
    if(!res)
        return(0);
    str = temp;
    return(1);
}

int quote_resolver(char *str, char **res)
{
    char *end_quote;

    end_quote = ft_strchr(str, "\'");
    if(!(end_quote - str))
        return(1);
    res = ft_strjoin_free(*res, ft_substr(str, 0, end_quote - str));
    if(!res)
        return(0);
}

int dquote_resolver(char *str, char **res)
{
    char *end_dquote;
    char *dollar;
    char *temp;

    end_dquote = ft_strchr(str, "\"");
    while(str < end_dquote)
    {
        dollar = ft_strchr(str, "$");
        if(!get_text(dollar, &str, &res))
            return(0);
        if(str == dollar)
        {
            temp = str++;
            while(*temp != '$' && *temp < '\"')
                temp++;
            if (temp == str + 1 && *temp == '\"')
            {
                ft_strjoin(*res, ft_strdup("$"));
                if(!*res)
                    return(0);
            }
            else if(!replace_var(str, temp, &res, envp))
                return(0);
        }
    }

}

int plain_resolver(char *str, char **res)
{    
    char *temp;
    char *env_value;
    char *dollar;

    while(*str != '\'' && *str != '\"' && *str)
    {
        dollar = ft_strchr(str, "$");
        if(!get_text(dollar, &str, &res))
            return(0);
        if(str == dollar)
        {
            temp = str++;;
            while(*temp != '\'' && *temp != '\"' && *temp != '$' && *temp)
                temp++;
            if (temp == str + 1 && (*temp == '\'' || *temp == '\"'))
            {
                ft_strjoin(*res, ft_strdup("\"\""));
                if(!*res)
                    return(0);
            }
            if(!replace_var(str, temp, &res, envp))
                return(0);
        }
    }
}

int expander(t_data *data)
{
    t_token *tokens;
    char    *str;
    char    *res;
    //iterate through tokens
    
    tokens = data->token;
    while(tokens)
    {
        str = tokens->word;
        while(*str)
        {
            if(*str == '\'')
            {
                if(!quote_resolver(str + 1, &res))
                    return(NULL);
            }
            else if(*str == '\"')
                dquote_resolver(str, &res);
            else
                plain_resolver(str, &res);
            str++;
        }
        tokens = tokens->next;
    }
}*/