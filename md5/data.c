/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agissing <agissing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 15:18:17 by agissing          #+#    #+#             */
/*   Updated: 2019/04/16 15:18:29 by agissing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

t_data		*new_elem(t_data **data)
{
	t_data		*tmp;

	tmp = *data;
	if (!(*data))
	{
		e_error(!(*data = ft_memalloc(sizeof(t_data))), 0);
		return (*data);
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		e_error(!(tmp->next = ft_memalloc(sizeof(t_data))), 0);
		return (tmp->next);
	}
}

void		append_data(t_data **data, char *str, t_siz count)
{
	int			i;
	t_data		*tmp;
	t_chunk		*chunks;

	i = -1;
	tmp = new_elem(data);
	chunks = (t_chunk *)str;
	while (++i < MD5_CHUNK_NBR)
		tmp->data[i] = chunks[i];
	tmp->size = count;
}
