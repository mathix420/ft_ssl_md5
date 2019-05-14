/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agissing <agissing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:43:29 by agissing          #+#    #+#             */
/*   Updated: 2019/04/16 17:23:04 by agissing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H

# ifndef FT_SSL_H
#  include "ft_ssl.h"
# endif

# define MD5_CHUNK_SIZE		16
# define MD5_CHUNK_NBR		100
# define MD5_TAB_SIZE		(MD5_CHUNK_SIZE * MD5_CHUNK_NBR * 4)

struct s_list;
typedef struct s_env	t_env;
typedef uint64_t		t_siz;

typedef struct			s_sub
{
	char		sub[4];
}						t_sub;

typedef struct			s_chunk
{
	t_sub		msg[MD5_CHUNK_SIZE];
}						t_chunk;

typedef struct			s_data
{
	t_chunk			data[MD5_CHUNK_NBR];
	t_siz			size;
	struct s_data	*next;
}						t_data;

typedef struct			s_const
{
	uint32_t		a;
	uint32_t		b;
	uint32_t		c;
	uint32_t		d;
}						t_const;

/*
** main
*/
void					md5(t_env *env);

/*
** libfct
*/
void					*ft_memalloc(size_t size);
void					ft_bzero(void *s, size_t n);

/*
** data
*/
t_data					*new_elem(t_data **data);
void					append_data(t_data **data, char *str, t_siz count);

#endif
