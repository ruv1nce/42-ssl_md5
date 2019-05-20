#include "ft_ssl.h"

extern t_ssl_opt	g_opt;

static uint32_t		g_s[64] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

static uint32_t		g_k[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

static void			do_hash(uint32_t *new_hash, uint32_t i, uint32_t *g,\
uint32_t *f)
{
	if (i <= 15)
	{
		*f = (B & C) | ((~B) & D);
		*g = i;
	}
	else if (i <= 31)
	{
		*f = (D & B) | ((~D) & C);
		*g = (5 * i + 1) % 16;
	}
	else if (i <= 47)
	{
		*f = B ^ C ^ D;
		*g = (3 * i + 5) % 16;
	}
	else
	{
		*f = C ^ (B | (~D));
		*g = (7 * i) % 16;
	}
}

static uint32_t		*get_hash(uint8_t *block, uint32_t cur_hash[4])
{
	static uint32_t	new_hash[4];
	uint32_t		m[16];
	uint32_t		i;
	uint32_t		g;
	uint32_t		f;

	ft_memcpy(m, block, sizeof(int) * 16);
	ft_memcpy(new_hash, cur_hash, sizeof(int) * 4);
	i = -1;
	while (++i < 64)
	{
		do_hash(new_hash, i, &g, &f);
		f = f + A + g_k[i] + m[g];
		A = D;
		D = C;
		C = B;
		B = B + LROT(f, g_s[i]);
	}
	return (new_hash);
}

static void			init_hash(uint32_t *cur_hash)
{
	cur_hash[0] = 0x67452301;
	cur_hash[1] = 0xefcdab89;
	cur_hash[2] = 0x98badcfe;
	cur_hash[3] = 0x10325476;
}

void				ft_md5(int fd)
{
	uint8_t		buf[BUF_SIZE + 1];
	int			i;
	uint8_t		pad_done;
	uint32_t	cur_hash[4];
	uint32_t	*new_hash;

	buf[BUF_SIZE] = 0;
	init_hash(cur_hash);
	pad_done = 0;
	while (!pad_done)
	{
		get_block(fd, buf, &pad_done, ltl_end);
		new_hash = get_hash(buf, cur_hash);
		i = -1;
		while (++i < 4)
		{
			cur_hash[i] += new_hash[i];
			// ft_printf("%u ", cur_hash[i]);	//
		}
	}
	g_opt.hash = stos((uint8_t*)cur_hash, 16);
}
