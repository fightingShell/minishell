/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapark <dapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:16:08 by dapark            #+#    #+#             */
/*   Updated: 2023/05/13 15:28:11 by dapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_dollar(char *str, t_parse *parse, int flag)
{
	int	cnt_dollar;
	int	i;
	int	quote;

	cnt_dollar = 0;
	i = 0;
	quote = 0;
	while (str[i] != '\0')
	{
		quote = quote_status(str[i], quote);
		if ((quote == 2 && str[i] == '$') || \
			(quote == 0 && str[i] == '$'))
		{
			cnt_dollar++;
			while (str[i + 1] == '$')
				i++;
		}
		i++;
	}
	if (flag == 1 && parse != NULL)
		parse->dollar_cnt = cnt_dollar;
	return (cnt_dollar);
}

void	question_mark_str(char *str, t_envval *env_var, int j, int start)
{
	char	*tmp;
	char	*g_str;
	char	*ret;
	int		l;
	int		i;

	l = start;
	i = 0;
	g_str = ft_itoa(g_status);
	tmp = malloc(sizeof(char) * l - start + 1);
	while (start < l)
	{
		tmp[i] = str[start];
		i++;
		start++;
	}
	tmp[i] = '\0';
	ret = ft_strdup(g_str);
	free(g_str);
	ret = ft_strjoin(ret, tmp);
	env_var[j].value = ret;
	env_var[j].size_v = ft_strlen(ret);
	env_var[j].ori = ft_strjoin("$?", tmp);
	free(tmp);
}

void	trans_question_mark(t_envval *env_var, char *str, int start, int j)
{
	int		l;

	l = start;
	while (!(check_sep(str[l], " ><|") == 1 || str[l] == '\0'))
		l++;
	if (l - start == 0)
	{
		env_var[j].value = ft_itoa(g_status);
		env_var[j].size_v = 1;
		env_var[j].ori = ft_strdup("?");
		return ;
	}
	else
		question_mark_str(str, env_var, j, start);
}

int	dollar_dollar(char *str, t_envval *env_var, \
		t_dollar_idx *dollar_i, int count)
{
	int		cnt;
	char	*tmp;

	cnt = 1;
	while (str[count++] == '$')
		cnt++;
	tmp = malloc(sizeof(char) * cnt + 1);
	tmp[cnt] = '\0';
	while (cnt-- >= 0)
		tmp[cnt] = '$';
	env_var[dollar_i->j].value = "";
	env_var[dollar_i->j].size_v = 0;
	env_var[dollar_i->j].ori = tmp;
	return (count);
}

void	dollar_case(char *str, t_envval *env_var, \
		t_dollar_idx *dollar_i, t_env *env)
{
	int	count;

	count = dollar_i->i + 1;
	if (str[count] == '?')
		trans_question_mark(env_var, str, count + 1, dollar_i->j);
	else if (str[count] == '$')
		count = dollar_dollar(str, env_var, dollar_i, count);
	else if (str[count] == ' ' || str[count] == '\0')
	{
		env_var[dollar_i->j].value = ft_strdup("$");
		env_var[dollar_i->j].size_v = 1;
		env_var[dollar_i->j].ori = "";
	}
	else
	{
		while (check_sep(str[count], " |<\">$") != 1 && str[count] != '\0')
			count++;
		env_var[dollar_i->j].value = trans_env(env, str, dollar_i->i + 1, \
									count - dollar_i->i - 1);
		env_var[dollar_i->j].ori = strdup_ori(str, dollar_i->i + 1, count - 1);
		env_var[dollar_i->j].size_v = ft_strlen(env_var[dollar_i->j].value);
	}
	dollar_i->j++;
	dollar_i->i = count;
}
