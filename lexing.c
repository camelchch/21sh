/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 15:41:00 by saxiao            #+#    #+#             */
/*   Updated: 2018/06/27 15:41:11 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "twenty_one.h"

void		less_and(char *line, int *index, t_word *add)
{
	if (*index + 2 < ft_strlen(line) && line[*index + 2] == '-' && \
			(*index + 3 >= ft_strlen(line) || is_seprator_w(line, *line + 3 )))
	{
		ft_strcpy(add->word, "<&-");
		add->type = LESSANDMINUS;
		*index = *index + 3;
	}
	else
	{
		ft_strcpy(add->word, "<&");
		add->type = LESSAND;
		*index = *index + 2;
	}
}

t_word		*less_type(char *line, int *index)
{
	t_word		*add;

	add = malloc_add();
	if (*index + 1 < ft_strlen(line) && line[*index + 1] == '<')
	{
		ft_strcpy(add->word, "<<");
		add->type = DLESS;
		*index = *index + 2;
	}
	else if (*index + 1 < ft_strlen(line) && line[*index + 1] == '&')
		less_and(line, index, add);
	else
	{
		ft_strcpy(add->word, "<");
		add->type = LESS;
		*index = *index + 1;
	}
	return (add);
}

void		great_and(char *line, int *index, t_word *add)
{
	if (*index + 2 < ft_strlen(line) && line[*index + 2] == '-' && \
			(*index + 3 >= ft_strlen(line) || is_seprator_w(line, *line + 3 )))
	{
		ft_strcpy(add->word, ">&-");
		add->type = GREATANDMINUS;
		*index = *index + 3;
	}
	else
	{
		ft_strcpy(add->word, ">&");
		add->type = GREATAND;
		*index = *index + 2;
	}
}

t_word		*great_type(char *line, int *index)
{
	t_word		*add;

	add = malloc_add();
	if (*index + 1 < ft_strlen(line) && line[*index + 1] == '>')
	{
		ft_strcpy(add->word, ">>");
		add->type = DGREAT;
		*index = *index + 2;
	}
	else if (*index + 1 < ft_strlen(line) && line[*index + 1] == '&')
		great_and(line, index, add);
	else
	{
		ft_strcpy(add->word, ">");
		add->type = GREAT;
		*index = *index + 1;
	}
	return (add);
}

t_word		*pipe_or_type(char *line, int *index)
{
	t_word		*add;

	add = malloc_add();
	if (*index + 1 < ft_strlen(line) && line[*index + 1] == '|')
	{
		ft_strcpy(add->word, "||");
		add->type = OR;
		*index = *index + 2;
	}
	else
	{
		ft_strcpy(add->word, "|");
		add->type = PIPE;
		*index = *index + 1;
	}
	return (add);
}

t_word		*and_type(char *line, int *index)
{
	t_word		*add;

	add = malloc_add();
	if (*index + 1 < ft_strlen(line) && line[*index + 1] == '&')
	{
		ft_strcpy(add->word, "&&");
		add->type = AND;
		*index = *index + 2;
	}
	return (add);
}

t_word		*semidot_type(char *line, int *index)
{
	t_word		*add;

	add = malloc_add();
	ft_strcpy(add->word, ";");
	add->type = SEMI_DOT;
	*index = *index + 1;
	return (add);
}

t_word		*init_seprator(char *line, int *index)
{
	if (line[*index] == '<')
		return (less_type(line, index));
	else if (line[*index] == '>')
		return (great_type(line, index));
	else if (line[*index] == '|')
		return (pipe_or_type(line, index));
	else if (line[*index] == '&')
		return (and_type(line, index));
	else if (line[*index] == ';')
		return (semidot_type(line, index));
	else if (line[*index] == ';')
		return (semidot_type(line, index));
	else if (line[*index] == ' ')
		*index = *index + 1;
	return (NULL);
}

int		return_message(char *message, int re_value)
{
	ft_printf("%s", message);
	return (re_value);
}
