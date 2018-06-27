/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 14:39:10 by saxiao            #+#    #+#             */
/*   Updated: 2018/06/27 19:31:15 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "twenty_one.h"

t_table			*malloc_add_sh(void)
{
	t_table		*add;

	add = (t_table *)malloc(sizeof(t_table));
	ft_bzero(add->name, NAME_MAX + 1);
	ft_bzero(add->path, PATH_MAX + 1);
	add->next = NULL;
	return (add);
}
/*
int			replace_home(char *word, char **env)
{
	char	temp[MAX_BUF];
	char	*vari_value;

	ft_bzero(temp, MAX_BUF);
	if (*word && *word == '~')
	{
		vari_value = ft_getenv(env, "HOME");
		if (!vari_value)
			return(return_message("Undefined HOME variable.\n", 1, 2));
		ft_strcpy(tem
	}
}
*/
