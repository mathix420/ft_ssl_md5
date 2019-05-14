/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agissing <agissing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:49:50 by agissing          #+#    #+#             */
/*   Updated: 2019/04/16 17:29:15 by agissing         ###   ########.fr       */
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

/*
** start debug fcts
*/

void		print_data(t_data data)
{
	while (data.next)
	{
		write(1, (char *)data.data, data.size);
		data = *data.next;
	}
	write(1, (char *)data.data, data.size);
}

/*
** end debug fcts
*/

void		pre_process(t_data *data)
{
	t_siz		id_data;
	t_const		cst;
	t_siz		count;

	cst.a = 0x67452301;
	cst.b = 0xefcdab89;
	cst.c = 0x98badcfe;
	cst.d = 0x10325476;
	count = 0;
	while (data->next && ++count)
		data = data->next;
	count = count * MD5_TAB_SIZE;
	id_data = data->size / (MD5_TAB_SIZE + 1);
	data[id_data].data[data->size / sizeof(t_chunk)].msg[data->size % sizeof(t_chunk)].sub[0] = 0x80;
	data->size++;
	while ((count + data->size) % 64 != 56)
	{
		data[id_data].data[data->size / sizeof(t_chunk)].msg[data->size % sizeof(t_chunk)].sub[0] = 0;
		data[id_data].data[data->size / sizeof(t_chunk)].msg[data->size % sizeof(t_chunk)].sub[1] = 0;
		data[id_data].data[data->size / sizeof(t_chunk)].msg[data->size % sizeof(t_chunk)].sub[2] = 0;
		data[id_data].data[data->size / sizeof(t_chunk)].msg[data->size % sizeof(t_chunk)].sub[3] = 0;
		data->size++;
	}
//	write(1, (char*)data[id_data].data, data->size);
}

void		md5(t_env *env)
{
	char	tmp[MD5_TAB_SIZE];
	t_data	**data;
	t_siz	count;
	int		fd;

	fd = 0;
	e_error(!(data = ft_memalloc(sizeof(t_data *))), 0);
	if (env->argc >= 3)
		e_error((fd = open(env->opt, O_RDONLY)) < 0, 0);
	tmp[0] = 0;
	while ((count = read(fd, tmp, MD5_TAB_SIZE)))
		append_data(data, tmp, count);
	pre_process(*data);
//	print_data(**data);	
	close(fd);
}
