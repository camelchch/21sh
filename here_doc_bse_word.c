#include <fcntl.h>
#include <unistd.h>
#include "twenty_one.h"

static void	for_here_doc(int *temp_fd, t_line *doc_line)
{
	doc_line->here_end = 0;
	ft_bzero(doc_line->here_mark, MAX_BUF);
	*temp_fd = open(temp_file, O_CREAT | O_TRUNC | O_RDWR | O_APPEND,\
			S_IWUSR | S_IRUSR);
	if (temp_fd < 0)
		ft_putendl_fd("temp file failed to be opened", 2);
}

static void	write2_temp_file(char *word)
{
	int		i;
	int		temp_fd;
	t_line	doc;

	for_here_doc(&temp_fd, &doc);
	i = 1;
	while (inside_doc_quote)
	{
		ft_bzero(doc.here, MAX_BUF);
		i == 0 ? ft_printf("\n") : (void)i;
		i = 0;
		get_line("heredoc> ",(char *)doc.here, &doc);
		if (ft_strcmp(word, (char *)doc.here))
		{
		if (write(temp_fd, doc.here, ft_strlen((char *)doc.here)) < 0)
			ft_putendl_fd("write into temp file failed", 2);
			write(temp_fd, "\n",1);
		}
		else
			inside_doc_quote = 0;
	}
	ft_printf("\n");
	if (close(temp_fd) == -1)
		ft_putendl_fd("close temp file failed", 2);
}

void	my_here_doc_word(t_word *list)
{
	while (list && !is_logic(list->type) && list->type != SEMI_DOT && \
			list->type != PIPE)
	{
	if (list->type == DLESS)
	{
		inside_doc_quote = 1;
		write2_temp_file(list->next->word);
		list->type = LESS;
		list->next->type = FILES;
		ft_bzero(list->word, MAX_BUF);
		ft_strcpy(list->word, "<");
		ft_bzero(list->next->word, MAX_BUF);
		ft_strcpy(list->next->word, temp_file);
	}
		list = list->next;
	}
}
