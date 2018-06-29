/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 17:25:25 by saxiao            #+#    #+#             */
/*   Updated: 2018/06/29 12:29:19 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include "twenty_one.h"

void	signal_inh(int sign)
{
	if (sign == SIGINT)
	{
		init_attr(SETOLD);
		ft_printf("\n$> ");
		ft_bzero(g_new_line, MAX_BUF);
		init_line("$> ", &g_line);
		init_attr(SETNEW);
		g_inside_doc_quote = 0;
		g_clc = 1;
	}
//	if (sign == SIGQUIT)
//		exit(0);
}
