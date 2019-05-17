#include "ft_ssl.h"

extern t_ssl_opt	g_opt;

void	ssl_perr(const char **cmds, char *arg, t_err err)
{
	int	i;

	if (err == no_string)
		ft_printf("ft_ssl: %s: option requires an argument -- s\nusage: ft_ssl\
 %s [-pqr] [-s string] [files ...]\n", g_opt.cmd, g_opt.cmd);
	else
	{
		if (err == no_arg)
			ft_printf("usage: ft_ssl command [command opts] [command args]\n");
		else if (err == inv_cmd)
		{
			ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\nStandard \
commands:\n\nMessage Digest commands:\n", arg);
			i = -1;
			while (++i < DGST_COUNT)
				ft_printf("%s\n", cmds[i]);
			ft_printf("\nCipher commands:\n");
		}
		else if (err == ill_opt)
			ft_printf("ft_ssl: %s: illegal option -- %c\nusage: ft_ssl %s [-pqr] \
[-s string] [files ...]\n", g_opt.cmd, g_opt.ill, g_opt.cmd);
		exit(1);
	}
}
