#include "ft_ssl.h"

extern t_ssl_opt	g_opt;

static void	read_stdin()
{
	char		buf[BUF_SIZE];
	uint32_t	ret;
	char		*tmp;

	while ((ret = read(0, buf, BUF_SIZE)))
	{
		g_opt.printed = 1;
		tmp = NULL;
		if (g_opt.msg)
			tmp = g_opt.msg;
		g_opt.msg = ft_strjoin(g_opt.msg, buf);
		if (tmp)
			free(tmp);
	}
}

void		ssl_iterator(char **argv)
{
	/* read stdin */
	if (argv)
		argv = argv + 1;
	read_stdin();

	// do the -s "strings"
	// read the files
}
