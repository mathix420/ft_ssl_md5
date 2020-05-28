/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agissing <agissing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:49:50 by agissing          #+#    #+#             */
/*   Updated: 2019/05/14 19:00:51 by agissing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"
#include <fcntl.h>

uint32_t	g_s[64] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

uint32_t	g_k[64] = {
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

int		pad_chunk(char *chunk, int count)
{
	while (count < MD5_PAD_LIMIT)
		chunk[count++] = 0;
	return count;
}

static uint32_t	leftrotate(uint32_t x, uint32_t round)
{
	uint32_t	shift;

	shift = g_s[round];
	return ((x << shift) | (x >> (32 - shift)));
}

void		step(void *ptr, t_const *vars)
{
	uint32_t	i;
	uint32_t	f;
	uint32_t	g;
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	*chunks;

	chunks = ptr;
	a = vars->a;
	b = vars->b;
	c = vars->c;
	d = vars->d;

	for (i = 0; i < 64; ++i)
	{
		if (i <= 15)
		{
			f = (b & c) | ((~b) & d);
			g = i;
		}
		else if (16 <= i && 31 >= i)
		{
			f = (d & b) | ((~d) & c);
			g = (5 * i + 1) % 16;
		}
		else if (32 <= i && 47 >= i)
		{
			f = b ^ c ^ d;
			g = (3 * i + 5) % 16;
		}
		else if (i >= 48)
		{
			f = c ^ (b | (~d));
			g = (7 * i) % 16;
		}
		f += a + g_k[i] + chunks[g];
        a = d;
        d = c;
        c = b;
        b += leftrotate(f, i);
	}
	vars->a += a;
    vars->b += b;
    vars->c += c;
    vars->d += d;
}

uint32_t 	reverse(uint32_t x)
{
    return ((x>>24)&0xff) | // move byte 3 to byte 0
                    ((x<<8)&0xff0000) | // move byte 1 to byte 2
                    ((x>>8)&0xff00) | // move byte 2 to byte 1
                    ((x<<24)&0xff000000);
}

void		final(t_const	*vars)
{
	int		i;

	i = 1;
	if (*(char *)&i == 1)
		printf("%.8x%.8x%.8x%.8x\n", reverse(vars->a), reverse(vars->b), reverse(vars->c), reverse(vars->d));
	else
		printf("%.8x%.8x%.8x%.8x\n", vars->a, vars->b, vars->c, vars->d);
}

void		md5(t_env *env)
{
	int		fd;
	char	tmp[MD5_CHUNK_SIZE + 1];
	t_siz	count;
	t_siz	size;
	t_const	*vars;

	fd = 0;
	size = 0;
	vars = ft_memalloc(sizeof (t_const));

	vars->a = 0x67452301;
	vars->b = 0xefcdab89;
	vars->c = 0x98badcfe;
	vars->d = 0x10325476;

	if (env->argc >= 3)
		e_error((fd = open(env->opt, O_RDONLY)) < 0, 0);
	ft_bzero(tmp, MD5_CHUNK_SIZE + 1);
	while ((count = read(fd, tmp, MD5_CHUNK_SIZE)))
	{
		tmp[count] = 0;
		size += count;
		if (count < MD5_CHUNK_SIZE)
			break;
		step(tmp, vars);
		ft_bzero(tmp, MD5_CHUNK_SIZE + 1);
	}
	close(fd);
	pad_chunk(tmp, count);
	tmp[count] |= 1 << 7;
	if (count >= 56) {
		step(tmp, vars);
		ft_bzero(tmp, MD5_CHUNK_SIZE + 1);
	}
	*((uint64_t*)&tmp[64 - 8]) = size * 8;

	step(tmp, vars);
	final(vars);
}
