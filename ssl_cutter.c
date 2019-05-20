#include "ft_ssl.h"

extern t_ssl_opt	g_opt;

void		reverse_bytes(void *s, size_t n)
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

/*
** add '1' bit (which equals to byte = 128)
** if there's not enough space to store msglen, we will pad two blocks
** inside last 8 bytes of padding we store msglen (in bits)
*/

static void	ssl_padder(uint8_t *buf, int64_t len, uint8_t *pad_done, t_end end)
{
	int				padlen;
	static int8_t	oneadded;

	padlen = BUF_SIZE - len - LEN_SIZE - 1;
	if (!oneadded)
	{
		buf[len++] = 128;
		oneadded = 1;
	}
	else
		buf[len++] = 0;
	if (padlen >= 0)
	{
		ft_bzero(buf + len, padlen);
		len += padlen;
		*(uint64_t*)(buf + BUF_SIZE - LEN_SIZE) = g_opt.msglen * 8;
		if (end == big_end)
			reverse_bytes(buf + BUF_SIZE - LEN_SIZE, LEN_SIZE);
		*pad_done = 1;
		oneadded = 0;
	}
	else
		ft_bzero(buf + len, BUF_SIZE - len);
}

/*
** if there's a file source, read from file
** if the source is a string, cut it into appropriate-sized blocks
** append padding for the last 1 or 2 blocks
*/

void		get_block(int fd, uint8_t *buf, uint8_t *pad_done, t_end end)
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
		ssl_padder(buf, len, pad_done, end);
}
