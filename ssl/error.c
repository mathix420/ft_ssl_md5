/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agissing <agissing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:49:21 by agissing          #+#    #+#             */
/*   Updated: 2019/04/14 14:56:55 by agissing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <errno.h>

void		e_error(int cond, int error_code)
{
	if (!cond || (!error_code && !errno))
		return ;
	(error_code) ? errno = error_code : 0;
	perror("ft_ssl");
	exit(1);
}

void		put_help(int cond, t_env *env)
{
	if (!cond)
		return ;
	write(1, "usage: ft_ssl command [command opts] [command args]\n", 53);
	if (env)
		free(env->algos);
	exit(1);
}
