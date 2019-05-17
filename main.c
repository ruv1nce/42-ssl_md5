#include "ft_ssl.h"

t_ssl_opt	g_opt;

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

int			main(int argc, char **argv)
{
	const char		*cmds[] = {"md5", "sha256"};
	const t_dgst	digs[] = {ft_md5, ft_sha256};
	int				i;

	if (argc < 2)
		ssl_perr(0, 0, no_arg);
	/* find digest command, if it exists */
	find_dgst(argv[1], cmds, digs);
	i = 2;
	/* parse options if there are any */
	if (argc > 2)
		ssl_parser(&argc, argv, &i);
	///
	// printf("opt: cmd %s, p %u, q %u, r %u, printed %u\n", g_opt.cmd, g_opt.p, g_opt.q, g_opt.r, g_opt.printed);
	// if (i < argc)
		// printf("next arg = argv[%i] %s\n", i, argv[i]);
	///

	/* iterate through sources */
	// printf("i %i, argc %i\n", i, argc);	//////

	if (i == argc)
		ssl_iterator(0, 0);
	else
		ssl_iterator(argc - i, &argv[i]);
}
