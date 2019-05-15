#include "ft_ssl.h"

static int	find_dgst(char *str, t_ssl_disp *disp, t_ssl_opt *opt)
{
	int	i;

	i = -1;
	while (++i < DGST_COUNT)
	{
		if (!ft_strcmp(str, disp[i].cmd))
		{
			opt->func = &disp[i];
			return (i);
		}
	}
	return (-1);
}

static void	options_init(t_ssl_opt *opt)
{
	opt->func = NULL;
	opt->p = 0;
	opt->q = 0;
	opt->r = 0;
	opt->ill = 0;
}

static void	dispatcher_init(t_ssl_disp *disp)
{
	disp[0].cmd = "md5";
	disp[0].dgst = ft_md5;
	disp[1].cmd = "sha256";
	disp[1].dgst = ft_sha256;
}

int			main(int argc, char **argv)
{
	t_ssl_disp	disp[DGST_COUNT];
	t_ssl_opt	opt;

	if (argc < 2)
		ssl_perr(0, 0, 0, no_arg);
	else
	{
		/* inititalize the dispatch table and options struct */
		dispatcher_init(disp);
		options_init(&opt);
		/* find digest command, if it exists */
		if ((find_dgst(argv[1], disp, &opt) == -1))
			ssl_perr(&opt, disp, argv[1], inv_cmd);
		else
		{
			/* parse options */
			if (!(argv = ssl_parser(argc - 2, &argv[2], &opt)))
				return (1);
			///
			printf("opt p %i, q %i, r %i\n", opt.p, opt.q, opt.r);
			printf("next arg %s\n", argv[0]);
			///
			/* iterate through sources */
			ssl_iterator(argv, &opt);
		}
	}
}
