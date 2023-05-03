/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 21:55:30 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/03 14:31:51 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**pars_envp(char **envp)
{
	char	**path;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			break ;
		i++;
	}
	if (!envp[i])
		print_error(NULL, NULL, NO_FILE_ERR, EXIT_Y, 127);
	path = ft_split(envp[i] + 5, ':');
	return (path);
}

char	*find_path(char **cmd, char **envp_path)
{
	char	*tmp;
	char	*path;
	int		i;

	i = 0;
	while (envp_path[i])
	{
		if (cmd[0][0] == '/')
			path = cmd[0];
		else
		{
			tmp = ft_strjoin(envp_path[i], "/");
			path = ft_strjoin(tmp, cmd[0]);
			free(tmp);
		}
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

void	pipe_exec(t_execinfo *execinfo, int flag)
{
	int			fds[2];
	pid_t		pid;
	int			status;

	pipe(fds);
	pid = fork(); // fork 실패 error처리
	if (pid == 0)
	{
		close(fds[0]);
		if (!flag) // 마지막 cmd
			dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);   
		redirection(execinfo);
		if (!check_builtin_fd(execinfo, STDOUT_FILENO))
			exit(0);
		execinfo->path = find_path(execinfo->cmd, pars_envp(execinfo->env->value));
		g_status = 0;
		if (execve(execinfo->path, execinfo->cmd, execinfo->env->value) == -1)
			print_error(NULL, execinfo->cmd[0], CMD_ERR, EXIT_Y, 127);
 	}
	else
	{
		waitpid(pid, &status, 0);
		close(fds[1]);
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
	}
}
