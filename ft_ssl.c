#include "ft_ssl.h"

t_ssl_opt	g_opt;

static int	parse_arg(char *arg)
{
	int	j;

	j = -1;
	while (arg[++j])
	{
		if (arg[j] == 'p')
			g_opt.p = 1;
		else if (arg[j] == 'q')
			g_opt.q = 1;
		else if (arg[j] == 'r')
			g_opt.r = 1;
		else
		{
			g_opt.ill = arg[j];
			ssl_perr(0, 0, ill_opt);
		}
	}
	return (1);
}

/*
** parse options (and skip them as args)
** check all -s options: if last -s is missing a string,
**							print error and decrement argc
*/

static void	ssl_parser(int *argc, char **argv, int *i)
{
	int	j;

	while (*i < *argc && argv[*i][0] == '-' && argv[*i][1] != 's')
	{
		parse_arg(&argv[*i][1]);
		(*i)++;
	}
	j = *i;
	while (j < *argc && argv[j][0] == '-' && argv[j][1] == 's')
	{
		if (!g_opt.p)
			g_opt.printed = 1;
		if (j == *argc - 1)
		{
			ssl_perr(0, 0, no_string);
			(*argc)--;
		}
		j += 2;
	}
}

static void	find_dgst(char *arg, const char **cmds, const t_dgst *digs)
{
	int	i;

	i = -1;
	while (++i < DGST_COUNT)
	{
		if (!ft_strcmp(arg, cmds[i]))
		{
			g_opt.cmd = cmds[i];
			g_opt.dgst = digs[i];
			return ;
		}
	}
	ssl_perr(cmds, arg, inv_cmd);
}

/*
** find digest command, if it exists
** parse options if there are any
** iterate through sources
*/

int			main(int argc, char **argv)
{
	const char		*cmds[] = {"md5", "sha256"};
	const t_dgst	digs[] = {ft_md5, ft_sha256};
	int				i;

	if (argc < 2)
		ssl_perr(0, 0, no_arg);
	find_dgst(argv[1], cmds, digs);
	i = 2;
	if (argc > 2)
		ssl_parser(&argc, argv, &i);
	if (i == argc)
		ssl_iterator(0, 0);
	else
		ssl_iterator(argc - i, &argv[i]);
}
