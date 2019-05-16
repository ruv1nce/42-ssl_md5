#include "ft_ssl.h"

t_ssl_opt	g_opt;

static int	find_dgst(char *arg, const char **cmds, const t_dgst *digs)
{
	int	i;

	i = -1;
	while (++i < DGST_COUNT)
	{
		if (!ft_strcmp(arg, cmds[i]))
		{
			g_opt.cmd = cmds[i];
			g_opt.dgst = digs[i];
			return (i);
		}
	}
	return (-1);
}

int			main(int argc, char **argv)
{
	const char		*cmds[] = {"md5", "sha256"};
	const t_dgst	digs[] = {ft_md5, ft_sha256};
	int				i;

	if (argc < 2)
		ssl_perr(0, 0, no_arg);
	else
	{
		/* find digest command, if it exists */
		if ((find_dgst(argv[1], cmds, digs) == -1))
			ssl_perr(cmds, argv[1], inv_cmd);
		else
		{
			argc -= 2;
			i = 0;
			/* parse options if there are any */
			if (argc && !(i = ssl_parser(argc, &argv[2], i)))
				return (1);
			///
			printf("opt: cmd %s, p %u, q %u, r %u, printed %u\n", g_opt.cmd, g_opt.p, g_opt.q, g_opt.r, g_opt.printed);
			if (i != argc)
				printf("next arg %s\n", argv[i]);
			///

			/* iterate through sources */
			if (i == argc)
				ssl_iterator(NULL);
			else
				ssl_iterator(&argv[i]);
			///
			printf("%s\n", g_opt.msg);
		}
	}
}
