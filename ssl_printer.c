/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_printer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfonarev <dfonarev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 00:37:21 by dfonarev          #+#    #+#             */
/*   Updated: 2019/05/20 00:37:24 by dfonarev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

extern t_ssl_opt	g_opt;

char	*stos(uint8_t *hash, int n)
{
	const char	*val = "0123456789abcdef";
	char		*str;
	int			i;

	str = ft_memalloc(sizeof(char) * (n * 2 + 1));
	i = 0;
	while (i < n * 2)
	{
		str[i] = val[*hash / 16];
		str[i + 1] = val[*hash % 16];
		hash++;
		i += 2;
	}
	return (str);
}

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

void	print_hash(void)
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
	free(g_opt.hash);
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
