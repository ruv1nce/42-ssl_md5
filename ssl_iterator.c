#include "ft_ssl.h"

extern t_ssl_opt	g_opt;

static void	read_stdin(void)
{
	char	buf[BUF_SIZE + 1];
	int32_t	ret;
	char	*tmp;

	buf[BUF_SIZE] = 0;
	while ((ret = read(0, buf, BUF_SIZE)))
	{
		if (ret == -1)
			ssl_perr(0, 0, bad_read);
		if (ret < BUF_SIZE)
			buf[ret] = 0;
		tmp = (g_opt.msg) ? g_opt.msg : NULL;
		g_opt.msg = ft_strjoin(g_opt.msg, buf);
		if (tmp)
			free(tmp);
	}
	g_opt.msglen = ft_strlen(g_opt.msg);
	g_opt.lentmp = ft_strlen(g_opt.msg);
	g_opt.lentmp = g_opt.msglen;
	g_opt.src = std_input;
	if (g_opt.p)
		ft_printf("%s", g_opt.msg);
	tmp = (g_opt.msg) ? g_opt.msg : NULL;

	// write(1, "\n", 1);
	// int i = -1;///
	// while (++i < (int)g_opt.msglen)///
	// 	ft_printf("%hhi ", g_opt.msg[i]);///
	// write(1, "\n", 1);///

	(*g_opt.dgst)(0);
	print_hash();
	if (tmp)
		free(tmp);
	g_opt.printed = 1;
	g_opt.msg = 0;
}

static void	read_string(char *str)
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

static void	read_file(char *file)
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

void		ssl_iterator(int argc, char **argv)
{
	int	i;

	/* read stdin */
	if (g_opt.p)
		read_stdin();
	if (argv)
	{
		/* do the -s "strings" */
		i = -1;
		while (++i < argc)
		{
			if (argv[i][0] == '-' && argv[i][1] == 's')
				read_string(argv[++i]);
			else
				break;
		}
		g_opt.msg = 0;
		/* read files */
		i--;
		while (++i < argc)
			read_file(argv[i]);
	}
	if (!g_opt.printed)
	 	read_stdin();
}
