#include "ft_ssl.h"

extern t_ssl_opt	g_opt;

void	ft_md5(int fd)
{
	char		buf[BUF_SIZE + 1];
	uint16_t	cur_hash[4];

	buf[BUF_SIZE] = 0;
	cur_hash[0] = 0x67452301;
	cur_hash[1] = 0xefcdab89;
	cur_hash[2] = 0x98badcfe;
	cur_hash[3] = 0x10325476;
	get_block(fd, buf);
}
