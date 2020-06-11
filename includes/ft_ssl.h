/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agissing <agissing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 11:55:39 by agissing          #+#    #+#             */
/*   Updated: 2019/04/14 18:26:12 by agissing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdint.h>

# ifndef FT_SSL_MD5_H
#  include "../md5/includes/ft_ssl_md5.h"
# endif

# ifndef FT_SSL_SHA256_H
#  include "../sha256/includes/ft_ssl_sha256.h"
# endif

struct s_env;
typedef int		t_param;

typedef struct	s_algos
{
	char	*name;
	int		(*is_param)(char);
	void	(*exec)(struct s_env *env);
}				t_algos;

typedef struct	s_env
{
	t_param		arg;
	char		*opt;
	t_algos		*algos;
	int			argc;
}				t_env;

/*
** Parsing
*/
void			parse(int c, char **v, t_env *env);

/*
** Param checker
*/
int				is_param_md5(char c);
int				is_param_sha(char c);
int				is_param_whirlpool(char c);

/*
** Error
*/
void			e_error(int cond, int error_code);
void			put_help(int cond, t_env *env);

/*
** Libft fct
*/
void			*ft_memcpy(void *restrict dst, const void *restrict src,
						size_t n);
int				ft_strcmp(const char *s1, const char *s2);
void			*ft_memalloc(size_t size);
void			ft_bzero(void *s, size_t n);

#endif
