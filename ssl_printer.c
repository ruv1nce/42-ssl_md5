#include "ft_ssl.h"

extern t_ssl_opt	g_opt;

void	print_uppercase_cmd(void)
{
	int		i;
	char	c;

	i = -1;
	while (g_opt.cmd[++i])
	{
		c = g_opt.cmd[i];
		if (c >= 'a' && c <= 'z')
			c -= 32;
		write(1, &c, 1);
	}
}

void	print_hash()
{
	if (g_opt.src != std_input && !g_opt.q && !g_opt.r)
	{
		print_uppercase_cmd();
		if (g_opt.src == string_arg)
			ft_printf(" (\"%s\") = ", g_opt.filename);
		if (g_opt.src == file_arg)
			ft_printf(" (%s) = ", g_opt.filename);
	}
	ft_printf("%s", g_opt.hash);
	if (g_opt.src != std_input && g_opt.r && !g_opt.q)
	{
		if (g_opt.src == string_arg)
			ft_printf(" \"%s\"", g_opt.filename);
		if (g_opt.src == file_arg)
			ft_printf(" %s", g_opt.filename);
	}
	write(1, "\n", 1);
}

void	ssl_perr(const char **cmds, char *arg, t_err err)
{
	int	i;

	if (err == no_string)
	{
		ft_printf("ft_ssl: %s: option requires an argument -- s\nusage: \
ft_ssl %s [-pqr] [-s string] [files ...]\n", g_opt.cmd, g_opt.cmd);
		return ;
	}
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
	else if (err == bad_read)
		ft_printf("ft_ssl: Error: cannot read file\n");
	exit(1);
}
