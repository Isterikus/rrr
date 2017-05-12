/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adress_wch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 14:12:59 by dkovalen          #+#    #+#             */
/*   Updated: 2017/05/12 12:51:34 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*ft_encode(wchar_t c)
{
	unsigned char	*str;

	str = (unsigned char *)ft_strnew(4);
	//printf("(%d)\n", c);
	if (c <= 0x7F)
		str[0] = (unsigned char)c;
	else if (c <= 0x7FF)
	{
		str[0] = (unsigned char)(((c << 2) | 0xC000) >> 8);
		str[1] = (unsigned char)((c & 0xBF) | 0x80);
	}
	else if (c <= 0xFFFF)
	{
		str[0] = (unsigned char)(((c >> 12) | 0xE0) & 0xEF);
		str[1] = (unsigned char)(((c >> 6) | 0x80) & 0xBF);
		str[2] = (unsigned char)((c | 0x80) & 0xBF);
		//printf("!%d!!%d!!%d!\n", str[0], str[1], str[2]);
	}
	else if (c <= 0x1FFFFF)
	{
		str[0] = (unsigned char)(((c << 6) | 0xF0000000) >> 24);
		str[1] = (unsigned char)(((c << 4) >> 16) | 0x80);
		str[2] = (unsigned char)((((c << 2) & 0x3FBF) >> 8) | 0x80);
		str[3] = (unsigned char)((c & 0xBF) | 0x80);
	}
	//printf("{%s}\n", str);
	return ((char *)str);
}

int		print_wchar(t_printf *elem, va_list *ap)
{
	wchar_t	*str;
	int		ret;

	ret = 0;
	if (elem->type == 'C' || elem->type == 'c')
	{
		str = (wchar_t *)malloc(sizeof(wchar_t) * 2);
		str[0] = va_arg(*ap, wchar_t);
		if (str[0] == 0)
		{
			write(1, str, 1);
			return (1);
		}
		str[1] = '\0';
	}
	else
		str = va_arg(*ap, wchar_t *);
	if (!str)
		str = ft_wchar_tdup(NL);
	return (create_spaces_wch(str, elem));
}

int		adress_acc(char *str, t_printf *elem)
{
	int		i;

	i = 0;
	ft_putstr("0x");
	str += 2;
	while (i++ < elem->accuracy - (int)ft_strlen(str))
		ft_putchar('0');
	if (elem->accuracy != 0)
	{
		ft_putstr(str);
		return (i + ft_strlen(str) + 1);
	}
	return (i + 1);
}

int		print_adress(t_printf *elem, va_list *ap)
{
	long long int	adr;
	char			*str;
	int				ret;

	adr = va_arg(*ap, long long int);
	str = ft_strdup("0x");
	str = ft_strjoin3(str, ft_itoa_base_unsigned(adr, 16, 1));
	ret = ft_strlen(str);
	if (elem->accuracy >= elem->width)
		return (adress_acc(str, elem));
	else if (elem->width != 0)
	{
		if (ft_strchr(elem->flags, '-') != NULL)
			create_spaces(str, elem, ' ', 1);
		else if (ft_strchr(elem->flags, '0') != NULL)
			zero_addr(str, elem);
		else
			create_spaces(str, elem, ' ', 0);
		free(str);
		if (ret > elem->accuracy)
			return (find_biggest(ret, elem->width, 0));
		else
			return (find_biggest(0, elem->width, elem->accuracy));
	}
	else
		ft_putstr(str);
	free(str);
	return (ret);
}
