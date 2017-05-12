/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_chars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 14:09:28 by dkovalen          #+#    #+#             */
/*   Updated: 2017/05/12 12:51:26 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		ft_putwchar(wchar_t c)
{
	char	*str;
	int		ret;

	str = ft_encode(c);
	ret = ft_strlen(str);
	write(1, str, ret);
	free(str);
	return (ret);
}

int		ft_putwchars(wchar_t *str)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (str[i])
		ret += ft_putwchar(str[i++]);
	return (ret);
}

int		first_str_wch(wchar_t *str, t_printf *elem, char c)
{
	int		ret;
	int		i;
	int		acc;

	ret = 0;
	if (elem->accuracy != -12345)
		acc = count_acc_wch(str, elem);
	else
		acc = ft_wchar_tlen(str);
	if (ft_strchr(SINGLE, elem->type) != NULL && str[0] == '\0')
		ret += ft_putwchar(str[0]);
	if (elem->accuracy != -12345)
	{
		i = 0;
		while (i < elem->accuracy && str[i])
			ret += ft_putwchar(str[i++]);
	}
	else
		ret += ft_putwchars(str);
	i = 0;
	while (i < elem->width - acc)
	{
		i++;
		ft_putchar(c);
	}
	if (elem->accuracy > elem->width)
		return (elem->accuracy);
	else
		return (elem->width);
}

int		first_c_wch(wchar_t *str, t_printf *elem, char c)
{
	int		ret;
	int		i;
	int		acc;

	ret = 0;
	i = 0;
	if (elem->accuracy != -12345)
		acc = count_acc_wch(str, elem);
	else
		acc = ft_wchar_tlen(str);
	while (i < elem->width - acc)
	{
		i++;
		ft_putchar(c);
	}
	if (ft_strchr(SINGLE, elem->type) != NULL)
		ret += ft_putwchar(str[0]);
	else if (elem->accuracy != -12345 && elem->type != 'p')
	{
		i = 0;
		while (str[i] && ret + ft_wchar_tclen(str[i]) <= elem->accuracy)
			ret += ft_putwchar(str[i++]);
	}
	else
		ret += ft_putwchars(str);
	if (elem->accuracy > elem->width)
		return (elem->accuracy);
	else
		return (elem->width);
}

int		create_spaces_wch(wchar_t *str, t_printf *elem)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	if (elem->width != 0)
	{
		if (ft_strchr(elem->flags, '-') != NULL)
			return (first_str_wch(str, elem, ' '));
		else if (ft_strchr(elem->flags, '0') != NULL)
			return (first_c_wch(str, elem, '0'));
		else
			return (first_c_wch(str, elem, ' '));
	}
	else if (elem->accuracy != -12345)
	{
		while (str[i] && ret + ft_wchar_tclen(str[i]) <= elem->accuracy)
			ret += ft_putwchar(str[i++]);
	}
	else
		ret += ft_putwchars(str);
	if (elem->type == 'C')
		free(str);
	return (ret);
}
