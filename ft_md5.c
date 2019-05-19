#include "ft_ssl.h"

extern t_ssl_opt	g_opt;

void	ft_md5(int fd)
{
	uint8_t	buf[BUF_SIZE + 1];
	int		len;
	uint8_t	pad_done;
	// uint16_t	cur_hash[4];

	buf[BUF_SIZE] = 0;
	// cur_hash[0] = 0x67452301;
	// cur_hash[1] = 0xefcdab89;
	// cur_hash[2] = 0x98badcfe;
	// cur_hash[3] = 0x10325476;
	pad_done = 0;
	while (!pad_done)
	{
		len = get_block(fd, buf, &pad_done);
		// ft_printf("%s", buf);
		if (!pad_done)
			write(1, buf, BUF_SIZE);
		else
		{
			write(1, buf, BUF_SIZE - LEN_SIZE);
			ft_printf("%llu", *(uint64_t*)(buf + BUF_SIZE - LEN_SIZE));
		}
		write(1, "\n", 1);//
	}
}
