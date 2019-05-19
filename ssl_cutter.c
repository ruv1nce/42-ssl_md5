#include "ft_ssl.h"

extern t_ssl_opt	g_opt;

static void	ssl_padder(uint8_t *buf, int64_t len, uint8_t *pad_done)
{
	int				padlen;
	static int8_t	oneadded;

	padlen = BUF_SIZE - len - LEN_SIZE - 1;
	/* put the 10000000 after msg and increment len */
	if (!oneadded)
	{
		buf[len++] = 128;
		oneadded = 1;
	}
	else
		buf[len++] = 'W';
	/* if we can fit 8B of msglen in the end */
	if (padlen >= 0)
	{
		ft_bchar(buf + len, 'X', padlen);
		len += padlen;
		*(uint64_t*)(buf + BUF_SIZE - LEN_SIZE) = g_opt.msglen * 8;
		*pad_done = 1;
		oneadded = 0;
	}
	else
	{
		ft_bchar(buf + len, 'Y', BUF_SIZE - len);	//
	}
}

int			get_block(int fd, uint8_t *buf, uint8_t *pad_done)
{
	int64_t	len;

	if (fd)
	{
		if ((len = read(fd, buf, BUF_SIZE)) == -1)
			ssl_perr(0, 0, bad_read);
		buf[len] = 0;
		g_opt.msglen += len;
	}
	else
	{
		len = (g_opt.lentmp > BUF_SIZE) ? BUF_SIZE : g_opt.lentmp;
		if (len)
		{
			ft_strncpy((char *)buf, g_opt.msg, BUF_SIZE);
			g_opt.msg += len;
			g_opt.lentmp -= len;
		}
	}
	if (len < BUF_SIZE)
	{
		// ft_printf("%s, len %i, %s\n", buf, len);	//
		ssl_padder(buf, len, pad_done);
		// ft_printf("%s\n", buf);	//
	}
	return (len);
}
