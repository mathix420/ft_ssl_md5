/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agissing <agissing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 11:53:39 by agissing          #+#    #+#             */
/*   Updated: 2019/04/14 16:37:38 by agissing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static inline t_param	parse_param(int c, char **v, t_algos algo, t_env *env)
{
	int		i;
	int		j;
	t_param	out;

	i = 2;
	out = 0;
	while (++i < c)
	{
		if (v[i][0] == '-' && v[i][1])
		{
			j = 0;
			while (v[i][++j])
			{
				if (algo.is_param(v[i][j]))
					out |= algo.is_param(v[i][j]);
				else
					put_help(1, env);
			}
		}
		else
			put_help(1, env);
	}
	return (out);
}

void					parse(int c, char **v, t_env *env)
{
	int	i;

	i = -1;
	while (env->algos[++i].name)
		if (!ft_strcmp(env->algos[i].name, v[1]))
		{
			env->arg = parse_param(c, v, env->algos[i], env);
			env->opt = v[2];
			env->algos[i].exec(env);
			return ;
		}
	put_help(1, env);
}
