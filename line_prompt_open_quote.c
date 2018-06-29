/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_prompt_open_quote.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 15:52:52 by saxiao            #+#    #+#             */
/*   Updated: 2018/06/29 13:33:57 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one.h"

static int			open_quote_exit(char *line)
{
	int		i;

	i = -1;
	g_open_squote = -1;
	g_open_dquote = -1;
	g_open_backslash = -1;
	while (line[++i])
	{
		if (line[i] == '"' && g_open_squote < 0 && dslash_before(line, i))
			g_open_dquote = -g_open_dquote;
		else if (line[i] == '\'' && g_open_dquote < 0 && \
				!(!dslash_before(line, i) && g_open_squote < 0))
			g_open_squote = -g_open_squote;
		else if (line[i] == '\\' && g_open_dquote < 0 && g_open_squote < 0 && \
				dslash_before(line, i) && !line[i + 1])
			g_open_backslash = -g_open_backslash;
	}
	if (g_open_dquote > 0 || g_open_squote > 0 || g_open_backslash > 0)
	{
		g_inside_doc_quote = 1;
		return (1);
	}
		g_inside_doc_quote = 0;
	return (0);
}

int				prompt_open_quote(char *line)
{
	char	new_line[MAX_BUF];
	t_line	quote_line;

	while (open_quote_exit(line))
	{
		ft_bzero(new_line, MAX_BUF);
		if (g_open_backslash > 0)
		{
			get_line("> ", new_line, &quote_line);
			line[ft_strlen(line) - 1] = '\0';
			ft_strcat(line, new_line);
			(g_with_termcap && !g_clc) ? ft_printf("\n") : (void)g_with_termcap;
		}
		else
		{
			if (!g_clc)
				ft_strcat(line, "\n");
			if (g_open_dquote > 0)
				get_line("dquote> ", new_line, &quote_line);
			else
				get_line("quote> ", new_line, &quote_line);
			ft_strcat(line, new_line);
			(g_with_termcap && !g_clc) ? ft_printf("\n") : (void)g_with_termcap;
		}
		if (g_clc)
			return (1);
	}
	return (0);
}
