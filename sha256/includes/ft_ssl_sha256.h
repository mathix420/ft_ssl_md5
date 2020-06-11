/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha256.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agissing <agissing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:43:29 by agissing          #+#    #+#             */
/*   Updated: 2019/05/14 17:03:58 by agissing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_SHA256_H
# define FT_SSL_SHA256_H

# ifndef FT_SSL_H
#  include "ft_ssl.h"
# endif

# include <fcntl.h>

# define SHA256_CHUNK_SIZE		64
# define SHA256_PAD_LIMIT		56

typedef struct s_env			t_env;
typedef unsigned int			t_siz;

typedef struct					s_sha256
{
	uint32_t		a;
	uint32_t		b;
	uint32_t		c;
	uint32_t		d;
	uint32_t		e;
	uint32_t		f;
	uint32_t		g;
	uint32_t		h;
}								t_sha256;

/*
** main
*/
void							sha256(t_env *env);

#endif
