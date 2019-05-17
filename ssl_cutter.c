#include "ft_ssl.h"

extern t_ssl_opt	g_opt;

void	get_block(int fd, char buf[BUF_SIZE + 1])
{
	static uint32_t	i;
	int	ret;

	if (fd)
		if ((ret = read(fd, buf, BUF_SIZE)) == -1)
			ssl_perr(0, 0, bad_read);
	else
	{

	}

}
