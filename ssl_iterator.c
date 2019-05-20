/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_iterator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfonarev <dfonarev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 00:37:12 by dfonarev          #+#    #+#             */
/*   Updated: 2019/05/20 00:37:14 by dfonarev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

extern t_ssl_opt	g_opt;

/*
** read BUF_SIZE bytes from stdin as long as there's stuff to read
** join all that was read into one string
** echo stdin if there's a -p flag
** generate hash
*/

static void			read_stdin(void)
{
	char	buf[BUF_SIZE + 1];
	int32_t	ret;
	char	*tmp;

	while ((ret = read(0, buf, BUF_SIZE)))
	{
		if (ret == -1)
			ssl_perr(0, 0, bad_read);
		buf[ret] = 0;
		tmp = (g_opt.msg) ? g_opt.msg : NULL;
		g_opt.msg = ft_strjoin(g_opt.msg, buf);
		tmp ? free(tmp) : 0;
	}
	g_opt.msglen = ft_strlen(g_opt.msg);
	g_opt.lentmp = g_opt.msglen;
	g_opt.src = std_input;
	if (g_opt.p)
		ft_printf("%s", g_opt.msg);
	tmp = (g_opt.msg) ? g_opt.msg : NULL;
	(*g_opt.dgst)(0);
	print_hash();
	tmp ? free(tmp) : 0;
	g_opt.printed = 1;
	g_opt.msg = 0;
}

static void			read_string(char *str)
{
	g_opt.msg = str;
	g_opt.filename = g_opt.msg;
	g_opt.msglen = ft_strlen(g_opt.msg);
	g_opt.lentmp = g_opt.msglen;
	g_opt.src = string_arg;
	(*g_opt.dgst)(0);
	print_hash();
	g_opt.printed = 1;
}

static void			read_file(char *file)
{
	int	fd;

	g_opt.printed = 1;
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		ft_printf("ft_ssl: %s: %s: No such file or directory\n",\
		g_opt.cmd, file);
		return ;
	}
	g_opt.src = file_arg;
	g_opt.filename = file;
	(*g_opt.dgst)(fd);
	print_hash();
	close(fd);
}

/*
** read stdin
** do the -s "strings"
** read files
*/

void				ssl_iterator(int argc, char **argv)
{
	int	i;

	if (g_opt.p)
		read_stdin();
	if (argv)
	{
		i = -1;
		while (++i < argc)
		{
			if (argv[i][0] == '-' && argv[i][1] == 's')
				read_string(argv[++i]);
			else
				break ;
		}
		g_opt.msg = 0;
		g_opt.msglen = 0;
		i--;
		while (++i < argc)
			read_file(argv[i]);
	}
	if (!g_opt.printed)
		read_stdin();
}
