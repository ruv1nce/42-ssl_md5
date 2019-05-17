#include "ft_ssl.h"

extern t_ssl_opt	g_opt;

static void	read_stdin()
{
	char		buf[BUF_SIZE + 1];
	int32_t	ret;
	char		*tmp;

	buf[BUF_SIZE] = 0;
	while ((ret = read(0, buf, BUF_SIZE)))
	{
		if (ret == -1)
			ssl_perr(0, 0, bad_read);
		// ft_printf("ret %u\n", ret);
		if (ret < BUF_SIZE)
			buf[ret] = 0;
		tmp = (g_opt.msg) ? g_opt.msg : NULL;
		g_opt.msg = ft_strjoin(g_opt.msg, buf);
		if (tmp)
			free(tmp);
	}
	if (g_opt.p)
		ft_printf("%s", g_opt.msg);
	g_opt.src = std_input;
	(*g_opt.dgst)(0);
	g_opt.printed = 1;
	free(g_opt.msg);
	g_opt.msg = 0;
}

static void	read_file(char *file)
{
	int	fd;

	if ((fd = open(file, O_RDONLY)) == -1)
	{
		ft_printf("ft_ssl: %s: %s: No such file or directory\n",\
		g_opt.cmd, file);
		return ;
	}
	g_opt.src = file_arg;
	g_opt.filename = file;
	(*g_opt.dgst)(fd);
	// ft_printf("%s\n", file);
	close(fd);
	g_opt.printed = 1;
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
			{
				g_opt.msg = argv[++i];
				g_opt.src = string_arg;
				(*g_opt.dgst)(0);
				// ft_printf("%s\n", g_opt.msg);
			}
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
