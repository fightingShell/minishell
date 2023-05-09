/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 23:32:49 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/07 23:32:49 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

void    init_signal(void);
void	sigint_handler(int sig);
void	print_error(char *errmsg, int flag, int status);
char	*errmsg(int flag, char *cmd1, char *cmd2, char *msg);

#endif