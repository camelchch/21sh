/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 17:25:25 by saxiao            #+#    #+#             */
/*   Updated: 2018/06/28 15:17:47 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include "twenty_one.h"

void	signal_inh(int sign)
{
	if (sign == SIGINT)
	{
	//	if (line_edition_ing)
	//	{
		init_attr(SETOLD);
		ft_printf("\n$> ");
		ft_bzero(new_line, MAX_BUF);
		init_line("$> ", &a_line);
		init_attr(SETNEW);
		inside_doc_quote = 0;
//		}
//		else
//		init_attr(SETOLD);
	}
	if (sign == SIGQUIT)
		exit(0);
}
