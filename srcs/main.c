/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:11:00 by yejinkim          #+#    #+#             */
/*   Updated: 2023/04/15 22:51:02 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_status = 0;

int main(int argc, char **argv, char **envp)
{
    char		*line;
	t_cmdline	*cmdline;
	t_env		env;

	(void)argc;
	(void)argv;
	env.value = init_env(envp);
	init_signal();
	while(1)
    {
        line = readline("minishell$ ");
		if (!line)
		{
			ft_putstr_fd("\x1b[1A", STDOUT_FILENO);
			ft_putstr_fd("\033[11C", STDOUT_FILENO);
			ft_putendl_fd("exit", STDOUT_FILENO);
			exit(0);
		}
		else if (!ft_strncmp(line, "", 1))
			continue ;
		else
		{
			cmdline = parsing(line, &env);
			// t_token *tmp=cmdline->token;
			// while (tmp)
			// {
			// 	printf("value: %s, type: %d, pipe: %d\n", tmp->value, tmp->type, tmp->pipe_flag);
			// 	tmp = tmp->next;
			// }
			execute(cmdline, &env);
			add_history(line);
			free(line);
		}
	}
	free_env(&env);
    return(0);
}
