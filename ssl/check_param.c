/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agissing <agissing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:10:42 by agissing          #+#    #+#             */
/*   Updated: 2019/04/11 14:34:12 by agissing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		is_param_md5(char c)
{
	return ((c == 'p') | (c == 'q') << 1 | (c == 'r') << 2 | (c == 's') << 3);
}

int		is_param_sha(char c)
{
	return ((c == 'p') | (c == 'q') << 1 | (c == 'r') << 2 | (c == 's') << 3);
}

int		is_param_whirlpool(char c)
{
	return ((c == 'p') | (c == 'q') << 1 | (c == 'r') << 2 | (c == 's') << 3);
}
