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

void		step(t_sub *chunks, t_const *vars)
{
	int		i;
	int		f;
	int		g;
	int		a;
	int		b;
	int		c;
	int		d;

	a = vars->a;
	b = vars->b;
	c = vars->c;
	d = vars->d;

	for (i = 0; i < 64; ++i)
	{
		if (0 <= i && 15 >= i)
		{
			f = (b & c) | ((!b) & c);
			g = i;
		}
		else if (16 <= i && 31 >= i)
		{
			f = (d & b) | ((!d) & c);
			g = (5 * i + 1) % 16;
		}
		else if (32 <= i && 47 >= i)
		{
			f = b ^ c ^ d;
			g = (3 * i + 5) % 16;
		}
		else if (48 <= i && 63 >= i)
		{
			f = c ^ (b | (!d));
			g = (7 * i) % 16;
		}
		f = f + a + g_k[i] + chunks[g];
        a = d;
        d = c;
        c = b;
        b = b + ((f << g_s[i]) | (f >> (32 - g_s[i])));
	}
	vars->a = vars->a + a;
    vars->b = vars->b + b;
    vars->c = vars->c + c;
    vars->d = vars->d + d;
}

void		md5(t_env *env)
{
	char	tmp[MD5_CHUNK_SIZE + 1];
	t_sub	*subs;
	t_siz	count;
	t_const	*vars;
	int		fd;

	fd = 0;
	vars = ft_memalloc(sizeof (t_const));
	if (env->argc >= 3)
		e_error((fd = open(env->opt, O_RDONLY)) < 0, 0);
	ft_bzero(tmp, MD5_CHUNK_SIZE + 1);
	while ((count = read(fd, tmp, MD5_CHUNK_SIZE)))
	{
		tmp[count] = 0;
		subs = (t_sub *)tmp;
		step(subs, vars);
		if (count != MD5_CHUNK_SIZE)
			break;
		printf("%s", tmp);
	}
	tmp[count] = 1;
	count = pad_chunk(tmp, count);
	subs = (t_sub *)tmp;
	step(subs, vars);
	printf("%sEND - %li\n", tmp, count);
	printf("\n\n%x%x%x%x\n", vars->a, vars->b, vars->c, vars->d);
	// pre_process(*data);
	close(fd);
}
