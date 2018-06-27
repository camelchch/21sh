#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include "twenty_one.h"

static t_word	*close_fd_mv_list(t_word *l, int i, int *pipe_fd, int nb_pipe)
{
	if (i > 0)
	{
		if (close(pipe_fd[i * 2 - 2]) < 0)
			ft_printf("close fd inside mv list failed\n");
	}
	if (i < nb_pipe)
	{
		if (close(pipe_fd[i * 2 + 1]) < 0)
			ft_printf("close fd inside mv list failed\n");
	}
	while (l && !is_logic(l->type) && l->type != SEMI_DOT && l->type != PIPE)
		l = l->next;
	if (l && l->type == PIPE)
		l = l->next;
	return (l);
}

static int	wait_all_pid(int *nb_pid, int i)
{
	int		j;
	int		status;

	j = -1;
	while (++j <= i)
	{
		if (nb_pid[j] != -1)
			waitpid(nb_pid[j], &status, WUNTRACED);
	}
	return (0);
}

static void	init_for_each_bloc(t_program *pro, int j,  int *nb_pid, int *pp_fd)
{
	int		i;

	i = -1;
	while (++i < j)
		pro[i].pro_args = NULL;
	init_int_table(nb_pid, MAX_BUF);
	init_int_table(pp_fd, MAX_BUF);
}

static void	init_for_each_bloc_2(t_word *list, int *nb_pipe, int *i)
{
	*nb_pipe = nb_pipe_eachbloc(list);
	*i = -1;
}

int			actions_each_bloc(t_word *list, char ***env, t_sh *table)
{
	int			pipe_fd[MAX_BUF];
	t_program	pro[MAX_BUF];
	int			nb_pid[MAX_BUF];
	int			i;
	int			nb_pipe;

	init_for_each_bloc_2(list, &nb_pipe, &i);
	if (first_buildin_no_pipe(nb_pipe, list))
		return (pro_is_buildin_no_pipe(list, env, table));
	init_for_each_bloc(pro, MAX_BUF,  nb_pid, pipe_fd);
	do_all_pipe(pipe_fd, nb_pipe);
	while (list && !is_logic(list->type) && list->type != SEMI_DOT)
	{
		my_here_doc_word(list);
		pro[++i].pro_args = args_each_exev(list, *env);
		if (valide_program(pro[i].pro_args, table))
		{
			if ((nb_pid[i] = fork()) == 0)
				(do_all_redirection(list, pipe_fd, nb_pipe, i)) ? exit(0) :\
					do_child_pro(list, pro[i].pro_args, *env, table);
		}
		list = close_fd_mv_list(list, i , pipe_fd, nb_pipe);
	}
	free_pro_args(pro, MAX_BUF);
	return (wait_all_pid(nb_pid, i));
}
