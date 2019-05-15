#include "ft_ssl.h"

static int	parse_arg(char *arg, t_ssl_opt *opt)
{
	int	j;

	j = -1;
	while (arg[++j])
	{
		if (arg[j] == 'p')
			opt->p = 1;
		else if (arg[j] == 'q')
			opt->q = 1;
		else if (arg[j] == 'r')
			opt->r = 1;
		else
		{
			opt->ill = arg[j];
			ssl_perr(opt, 0, 0, ill_opt);
			return (0);
		}
	}
	return (1);
}

char	**ssl_parser(int argc, char **argv, t_ssl_opt *opt)
{
	int	i;

	/* iterate through args */
	i = -1;
	while (++i < argc)
	{
		/* return current argument if it's a file name or -s option */
		if (argv[i][0] != '-' || (argv[i][0] == '-' && argv[i][1] == 's'))
			return (&argv[i]);
		/* iterate through chars of current arg, starting from 1, because
			there was a '-' in position 0 */
		if (!(parse_arg(&argv[i][1], opt)))
			return (0);
	}
	ssl_perr(opt, 0, 0, file_unspec);
	return (0);
}
