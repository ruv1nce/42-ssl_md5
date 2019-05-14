#include "ft_ssl.h"

void	ssl_perr(char *cmd, t_ssl_disp *disp, char ill, t_err err)
{
	int	i;

	if (err == no_arg)
		ft_printf("usage: ft_ssl command [command opts] [command args]\n");
	else if (err == inv_cmd)
	{
		ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\n", cmd);
		ft_printf("Standard commands:\n\nMessage Digest commands:\n");
		i = -1;
		while (++i < DGST_COUNT)
			ft_printf("%s\n", disp[i].cmd);
		ft_printf("\nCipher commands:\n");
	}
	else if (err == ill_opt)
	{
		ft_printf("ft_ssl: %s: illegal option -- %c\n", cmd, ill);
		ft_printf("usage: ft_ssl %s [-pqrtx] [-s string] [files ...]\n", cmd);
	}
}
