/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapark <dapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 17:44:23 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/13 21:37:14 by dapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_cmdline(t_cmdline *cmdline)
{
	t_token	*token_f;
	t_token *token_n;

	token_f = cmdline->token;
	token_n = cmdline->token;
	while (token_n != NULL)
	{
		token_f = token_n;
		token_n = token_f->next;
		if (ft_strncmp(token_f->value, "", 1) != 0){
			printf("token free : %s\n", token_f->value);
			free(token_f->value);
		}
		free(token_f);
	}
	free(cmdline);
}
