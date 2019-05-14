/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agissing <agissing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 11:54:00 by agissing          #+#    #+#             */
/*   Updated: 2019/04/14 18:30:07 by agissing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void		init_env(t_env *env)
{
	t_algos		*new;

	e_error(!(new = malloc(sizeof(t_algos) * 5)), 0);
	new[0] = (t_algos){"md5", &is_param_md5, &md5};
	new[1] = (t_algos){"sha256", &is_param_sha, 0};
	new[2] = (t_algos){"sha512", &is_param_sha, 0};
	new[3] = (t_algos){"whirlpool", &is_param_whirlpool, 0};
	new[4] = (t_algos){0, 0, 0};
	env->algos = new;
}

int				main(int c, char **v)
{
	t_env	env;

	env.argc = c;
	put_help(c < 2, 0);
	init_env(&env);
	parse(c, v, &env);
	return (0);
}
