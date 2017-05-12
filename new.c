/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 09:47:39 by dkovalen          #+#    #+#             */
/*   Updated: 2017/05/12 11:59:47 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

wchar_t	*ft_wchar_tdup(char *str)
{
	wchar_t	*new;
	int		i;
	int		len;

	len = ft_strlen(str);
	new = (wchar_t *)malloc(sizeof(wchar_t) * len);
	i = 0;
	while (i < len)
	{
		new[i] = str[i];
		i++;
	}
	return (new);
}

int		ft_wchar_tlen(wchar_t *str)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] <= 0x7F)
			len += 1;
		else if (str[i] <= 0x7FF)
			len += 2;
		else if (str[i] <= 0xFFFF)
			len += 3;
		else if (str[i] <= 0x1FFFFF)
			len += 4;
		i++;
	}
	return (len);
}

void	zero_addr(char *str, t_printf *elem)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(str);
	str += 2;
	write(1, "0x", 2);
	while (i++ < elem->width - len)
		ft_putchar('0');
	if (len > 0)
		write(1, str, len - 2);
	else
		write(1, str, 1);
	str -= 2;
}

int		ft_wchar_tclen(wchar_t c)
{
	int		len;

	len = 0;
	if (c <= 0x7F)
		len = 1;
	else if (c <= 0x7FF)
		len = 2;
	else if (c <= 0xFFFF)
		len = 3;
	else if (c <= 0x1FFFFF)
		len = 4;
	return (len);
}

int		count_acc_wch(wchar_t *str, t_printf *elem)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (str[i] && ret + ft_wchar_tclen(str[i]) <= elem->accuracy)
	{
		ret += ft_wchar_tclen(str[i]);
		i++;
	}
	return (ret);
}

