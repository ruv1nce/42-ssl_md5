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
		}
	}
	return (1);
}

/*
** parse options (and skip them as args)
** check all -s options: if last -s is missing a string,
**							print error and decrement argc
*/

void		ssl_parser(int *argc, char **argv, int *i)
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
