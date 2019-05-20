#include "ft_ssl.h"

extern t_ssl_opt	g_opt;

void	reverse_bytes(void *s, size_t n)
{
	uint32_t	i;
	uint8_t		tmp;

	i = 0;
	n--;
	while (i < n)
	{
		tmp = ((uint8_t*)s)[i];
		((uint8_t*)s)[i] = ((uint8_t*)s)[n];
		((uint8_t*)s)[n] = tmp;
		i++;
		n--;
	}
}

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
		buf[len++] = 0;
	/* if we can fit 8B of msglen in the end */
	if (padlen >= 0)
	{
		ft_bzero(buf + len, padlen);
		len += padlen;
		*(uint64_t*)(buf + BUF_SIZE - LEN_SIZE) = g_opt.msglen * 8;
		*pad_done = 1;
		oneadded = 0;
	}
	else
		ft_bzero(buf + len, BUF_SIZE - len);
}

void		get_block(int fd, uint8_t *buf, uint8_t *pad_done)
{
	int64_t	len;

	// write(1, "\n", 1);
	// int i = -1;///
	// while (++i < (int)g_opt.msglen)///
	// 	ft_printf("%hhi ", g_opt.msg[i]);///
	// write(1, "\n", 1);///
	// ft_printf("msglen %i\n", g_opt.msglen);///


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
		ssl_padder(buf, len, pad_done);
}
