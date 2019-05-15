#include "ft_ssl.h"

char		*ft_md5(char *str)
{
	str[0] = 'M';
	return (str);
}

char		*ft_sha256(char *str)
{
	str[0] = 'S';
	return (str);
}

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

static void	iterator()
{
	// read stdin
	// do the -s "strings"
	// read the files
}

int			main(int argc, char **argv)
{
	t_ssl_disp	disp[DGST_COUNT];
	t_ssl_opt	opt;
	int			digest;

	if (argc < 2)
		ssl_perr(0, 0, 0, no_arg);
	else
	{
		dispatcher_init(disp);
		options_init(&opt);
		if ((digest = find_dgst(argv[1], disp, &opt) == -1))
			ssl_perr(&opt, disp, argv[1], inv_cmd);
		else
		{
			if (!(argv = ssl_parser(argc - 2, &argv[2], &opt)))
				return (1);
			else
				iterator();
		}
	}
}
