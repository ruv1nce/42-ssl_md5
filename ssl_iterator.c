#include "ft_ssl.h"

extern t_ssl_opt	g_opt;

static void	read_stdin()
{
	char		buf[BUF_SIZE + 1];
	uint32_t	ret;
	char		*tmp;

	buf[BUF_SIZE] = 0;
	while ((ret = read(0, buf, BUF_SIZE)))
	{
		ft_printf("ret %u\n", ret);
		if (ret < BUF_SIZE)
			buf[ret] = 0;
		g_opt.printed = 1;
		tmp = (g_opt.msg) ? g_opt.msg : NULL;
		g_opt.msg = ft_strjoin(g_opt.msg, buf);
		if (tmp)
			free(tmp);
	}
	if (g_opt.p && !g_opt.q)
		ft_printf("%s", g_opt.msg);
	// hash_string();
	g_opt.printed = 1;
	free(g_opt.msg);
}

void		ssl_iterator(int argc, char **argv)
{
	int	i;

	/* read stdin */
	if (g_opt.p)
		read_stdin();
	/* do the -s "strings" */
	i = -1;
	while (++i < argc)
	{
		if (argv[i][0] == '-' && argv[i][1] == 's')
		{
			g_opt.msg = argv[++i];
			// hash_string();
			ft_printf("%s\n", g_opt.msg);
		}
		else
			break;
	}
	/* read files */
	// while (i < argc)
	// {

	// }

	// if (!g_opt.printed)
		// read_stdin();
}
