/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_ctrl_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 15:43:52 by saxiao            #+#    #+#             */
/*   Updated: 2018/06/28 23:41:27 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "twenty_one.h"

int			delete_at_position(t_line *line)
{
	if (line->pos < line->buf_len)
	{
		move_right(line);
		delete_key(line);
		move_left(line);
	}
	return (0);
}

int			ctrl_d(t_line *line)
{
	if (with_termcap && (line->pos < line->buf_len) && line->buf_len)
		delete_at_position(line);
	else
	{
		if (inside_doc_quote)
		{
			end_line = 1;
			inside_doc_quote = 0;
			return (0);
		}
		else
		{
			init_attr(SETOLD);
			ft_printf("exit");
			exit(0);
		}
	}
	return (0);
}
