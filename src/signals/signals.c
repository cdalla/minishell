/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/07 13:30:43 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/01/07 13:58:13 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <readline/readline.h>

/*handle the signal*/
void	sig_int_parent(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_int_heredoc(int signum)
{
	(void)signum;
	exit(1);
}

void	signals_heredoc(void)
{
	signal(SIGINT, sig_int_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

/*signals in parent*/
void	signals_parent(void)
{
	signal(SIGINT, sig_int_parent);
	signal(SIGQUIT, SIG_IGN);
}

/*signal in child*/
void	signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
