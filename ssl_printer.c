#include "ft_ssl.h"

void	ssl_perr(t_ssl_opt *opt, t_ssl_disp *disp, char *cmd, t_err err)
{
	int	i;

	if (err == no_arg)
		ft_printf("usage: ft_ssl command [command opts] [command args]\n");
	else if (err == inv_cmd)
	{
		ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\nStandard commands:\n\nMessage Digest commands:\n", cmd);
		i = -1;
		while (++i < DGST_COUNT)
			ft_printf("%s\n", disp[i].cmd);
		ft_printf("\nCipher commands:\n");
	}
	else if (err == ill_opt)
	{
		ft_printf("ft_ssl: %s: illegal option -- %c\nusage: ft_ssl %s [-pqr] [-s string] [files ...]\n", opt->func->cmd, opt->ill, opt->func->cmd);
	}
	else if (err == file_unspec)
		ft_printf("ft_ssl: %s: file not specified.\nusage: ft_ssl %s [-pqr] [-s string] [files ...]\n", opt->func->cmd, opt->func->cmd);
}
