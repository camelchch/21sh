#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

static t_save_fd	*add_2recover(t_save_fd *recover, int nb_fd)
{
	t_save_fd	*add;
	t_save_fd	*cp;
	int			save_in2;

	cp = recover;
	add = NULL;
	add = malloc(sizeof(t_save_fd));
	if ((save_in2 = dup(nb_fd)) < 0)
		ft_putendl_fd("dup inside add_2recover failed", 2);
	add->fd_2be_saved = nb_fd;
	add->fd_saved_in2 = save_in2;
	if (!recover)
		return (add);
	while (cp->next)
		cp = cp->next;
	cp->next = add;
	return (recover);
}

t_save_fd		*fd_restorage(t_word *l, t_save_fd *recover)
{
	int			nb_fd;

	while (l && !is_logic(l->type) && l->type != SEMI_DOT)
	{
		if (l->type == LESS || l->type == LESSAND || l->type == LESSANDMINUS)
		{
			if (l->pre && l->pre->type == FD)
				nb_fd = ft_atoi(l->pre->word);
			else
				nb_fd = 0;
			recover = add_2recover(recover, nb_fd);
		}
		if (l->type == GREAT || l->type == GREATAND || l->type == GREATANDMINUS || l->type == DGREAT)
		{
			if (l->pre && l->pre->type == FD)
				nb_fd = ft_atoi(l->pre->word);
			else
				nb_fd = 1;
			recover = add_2recover(recover, nb_fd);
		}
		l = l->next;
	}
return(recover);
}

void		recover_fd(t_save_fd *recover)
{
	while (recover)
	{
		if (dup2(recover->fd_saved_in2, recover->fd_2be_saved) < 0)
			ft_putendl_fd("dup failled in recover_fd", 2);
		close(recover->fd_saved_in2);
		recover = recover->next;
	}
}

void		free_saver_fd(t_save_fd *recover)
{
	t_save_fd	*temp;

	temp = NULL;
	while(recover)
	{
		temp = recover;
		close(temp->fd_saved_in2);
		recover = recover->next;
		free(temp);
	}
}
