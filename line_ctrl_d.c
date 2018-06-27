/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_ctrl_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 15:43:52 by saxiao            #+#    #+#             */
/*   Updated: 2018/06/27 15:45:19 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "twenty_one.h"

int			delete_at_position(t_line *line)
{
	if(line->pos < line->buf_len)
	{
		move_right(line);
		delete_key(line);
		move_left(line);
	}
	return (0);
}

int			ctrl_d(t_line *line)
{

	if (with_termcap && line->buf_len)
		delete_at_position(line);
	else
	{
		ft_printf("exit");
		exit(0);
	}
	return (0);
}
