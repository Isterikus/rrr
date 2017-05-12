/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 17:49:47 by dkovalen          #+#    #+#             */
/*   Updated: 2017/05/12 13:51:50 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int			abs(int d)
{
	if (d >= 0)
		return (d);
	else
		return (-d);
}

void		fill_type(t_printf *elem, int *i)
{
	(*i)++;
	elem->flags = NULL;
	elem->width = 0;
	elem->accuracy = -12345;
	elem->modificator = 0;
	elem->type = 0;
}

void	create_type(const char *type, int *i, va_list *ap, t_printf **el)
{
	t_printf	*elem;

	elem = (*el);
	fill_type(elem, i);
	*i = flags(type, *i, elem);
	*i = int_w(type, *i, elem, ap);
	if (type[*i] == '.')
	{
		*i = int_a(type, *i + 1, elem, ap);
		if (type[*i] == '.' || elem->accuracy == -12345)
		{
			while (type[*i] == '.')
				(*i)++;
			elem->accuracy = 0;
		}
	}
	*i = modificators(type, *i, elem);
	if (ft_strchr(FLAGS, type[*i]) != NULL)
		*i = flags(type, *i, elem);
	if (type[*i] == '\0')
	{
		(*el) = NULL;
		return ;
	}
	elem->type = type[(*i)++];
	if (elem->type == 'D' || elem->type == 'O')
		elem->modificator = 'l';
}
