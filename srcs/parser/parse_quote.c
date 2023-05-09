/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daheepark <daheepark@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:16:45 by dapark            #+#    #+#             */
/*   Updated: 2023/05/09 23:55:25 by daheepark        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	chk_str_len(char *str)
{
	int	i;
	int	quote;
	int	flag_q;
	int	cnt_q;

	i = -1;
	quote = 0;
	cnt_q = 0;
	while (str[++i] != '\0')
	{
		quote = quote_status(str[i], quote);
		if (quote != 0)
			flag_q = 1;
		if (flag_q == 1 && quote == 0)
		{
			cnt_q++;
			flag_q = 0;
		}
	}
	return (cnt_q);
}

void	make_ret_str(char *str, char *ret)
{
	int			i;
	int			j;
	t_rmv_quote	*rmv;

	i = -1;
	j = -1;
	rmv = malloc(sizeof(t_rmv_quote));
	init_rmv(rmv);
	while (str[++i] != '\0')
	{
		rmv->quote = quote_status(str[i], rmv->quote);
		if (rmv->curr_q == rmv->quote)
			ret[++j] = str[i];
		if (rmv->quote != 0)
		{
			rmv->flag_q = 1;
			rmv->curr_q = rmv->quote;
		}
		if (rmv->flag_q == 1 && rmv->quote == 0)
		{
			rmv->curr_q = rmv->quote;
			rmv->flag_q = 0;
		}
	}
	ret[++j] = '\0';
}

char	*remove_quote(char *str)
{
	int		cnt_q;
	char	*ret;
	int		len;

	len = strlen(str);
	cnt_q = chk_str_len(str);
	if (cnt_q == 0)
		return (str);
	ret = (char *)malloc(sizeof(char) * (len - (2 * cnt_q) + 1));
	make_ret_str(str, ret);
	return (ret);
}
