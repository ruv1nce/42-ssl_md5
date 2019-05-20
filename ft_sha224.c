/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha224.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfonarev <dfonarev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 00:37:17 by dfonarev          #+#    #+#             */
/*   Updated: 2019/05/20 00:37:19 by dfonarev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

extern t_ssl_opt	g_opt;

static uint32_t	g_k[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
	0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
	0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
	0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
	0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
	0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

static void			make_warray(uint8_t *block, uint32_t *w)
{
	uint32_t	i;
	uint32_t	s[2];

	ft_memcpy(w, block, sizeof(int) * 16);
	i = -1;
	while (++i < 16)
		reverse_bytes(w + i, sizeof(int));
	i--;
	while (++i < 64)
	{
		s[0] = RROT(w[i - 15], 7) ^ RROT(w[i - 15], 18) ^ (w[i - 15] >> 3);
		s[1] = RROT(w[i - 2], 17) ^ RROT(w[i - 2], 19) ^ (w[i - 2] >> 10);
		w[i] = w[i - 16] + s[0] + w[i - 7] + s[1];
	}
}

static void			do_hash(uint32_t *new_hash, uint32_t *w,
							uint32_t i)
{
	uint32_t		s[2];
	uint32_t		tmp[2];
	uint32_t		ch;
	uint32_t		maj;

	s[1] = RROT(E, 6) ^ RROT(E, 11) ^ RROT(E, 25);
	ch = (E & F) ^ ((~E) & G);
	tmp[0] = H + s[1] + ch + g_k[i] + w[i];
	s[0] = RROT(A, 2) ^ RROT(A, 13) ^ RROT(A, 22);
	maj = (A & B) ^ (A & C) ^ (B & C);
	tmp[1] = s[0] + maj;
	H = G;
	G = F;
	F = E;
	E = D + tmp[0];
	D = C;
	C = B;
	B = A;
	A = tmp[0] + tmp[1];
}

static uint32_t		*get_hash(uint8_t *block, uint32_t cur_hash[8])
{
	static uint32_t	new_hash[8];
	uint32_t		w[64];
	uint32_t		i;

	make_warray(block, w);
	ft_memcpy(new_hash, cur_hash, sizeof(int) * 8);
	i = -1;
	while (++i < 64)
		do_hash(new_hash, w, i);
	return (new_hash);
}

static void			init_hash(uint32_t *cur_hash)
{
	cur_hash[0] = 0xc1059ed8;
	cur_hash[1] = 0x367cd507;
	cur_hash[2] = 0x3070dd17;
	cur_hash[3] = 0xf70e5939;
	cur_hash[4] = 0xffc00b31;
	cur_hash[5] = 0x68581511;
	cur_hash[6] = 0x64f98fa7;
	cur_hash[7] = 0xbefa4fa4;
}

void				ft_sha224(int fd)
{
	uint8_t		buf[BUF_SIZE + 1];
	int			i;
	uint8_t		pad_done;
	uint32_t	cur_hash[8];
	uint32_t	*new_hash;

	buf[BUF_SIZE] = 0;
	init_hash(cur_hash);
	pad_done = 0;
	while (!pad_done)
	{
		get_block(fd, buf, &pad_done, big_end);
		new_hash = get_hash(buf, cur_hash);
		i = -1;
		while (++i < 8)
			cur_hash[i] += new_hash[i];
	}
	i = -1;
	while (++i < 8)
		reverse_bytes(cur_hash + i, sizeof(int));
	g_opt.hash = stos((uint8_t*)cur_hash, 28);
}
