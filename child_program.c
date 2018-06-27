#include <unistd.h>
#include <stdlib.h>
#include "twenty_one.h"

char		*path_in_sh(char *app, t_sh *table)
{
	int			index;
	t_table		*cp;

	index = calcu_index(app);
	cp = table[index].sh_ta;
	while (cp)
	{
		if (!strcmp(app, cp->name))
			return (cp->path);
		cp = cp->next;
	}
	return (NULL);
}

void		child_pro_bin(char **paras, char **env, t_sh *table)
{
	char	*path;

	if (!access(*paras, F_OK))
	{
		update_lastapp(*paras, &env);
		execve(*paras, paras, env);
		put2_str_fd(*paras, " permission denied for this program.\n", 2);
		exit(0);
	}
	else
	{
		path = path_in_sh(*paras, table);
		update_lastapp(path, &env);
		execve(path, paras, env);
		put2_str_fd(*paras, " permission denied for this program.\n", 2);
		exit(0);
	}
}

static void	child_pro_buildin(char **paras, char **env, t_sh *table)
{

	do_build(paras, &env, table);
	if (ft_strcmp(*paras, "exit"))
	exit(0);
}

void		do_child_pro(t_word *list, char **paras, char **env, t_sh *table)
{
	if (is_buildin(*paras))
		child_pro_buildin(paras, env, table);
	else
		child_pro_bin(paras, env, table);
}
