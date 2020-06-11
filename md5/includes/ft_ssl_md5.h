/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agissing <agissing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:43:29 by agissing          #+#    #+#             */
/*   Updated: 2019/05/14 17:03:58 by agissing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H

# ifndef FT_SSL_H
#  include "ft_ssl.h"
# endif

# include <fcntl.h>

# define MD5_CHUNK_SIZE		64
# define MD5_PAD_LIMIT		56

typedef struct s_env		t_env;
typedef unsigned int		t_siz;

typedef struct				s_md5
{
	uint32_t		a;
	uint32_t		b;
	uint32_t		c;
	uint32_t		d;
}							t_md5;

/*
** main
*/
void						md5(t_env *env);

#endif
