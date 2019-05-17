#include "ft_ssl.h"

extern t_ssl_opt	g_opt;

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
			return (0);
		}
	}
	return (1);
}

int	ssl_parser(int argc, char **argv, int *i)
{
	/* iterate through args */
	while (*i < argc)
	{
		/* return current argument if it's a file name */
		if (argv[*i][0] != '-')
			return (1);
		/* if it's an -s option, check that there's a string after it */
		if (argv[*i][0] == '-' && argv[*i][1] == 's')
		{
			if (*i == argc - 1)
			{
				ssl_perr(0, 0, no_string);
				return (0);
			}
			else
				return(1);
		}
		/* iterate through chars of current arg, starting from 1, because
			there was a '-' in position 0 */
		if (!(parse_arg(&argv[*i][1])))
			return (0);
		(*i)++;
	}
	return (1);
}
