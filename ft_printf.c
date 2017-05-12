/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 15:38:27 by dkovalen          #+#    #+#             */
/*   Updated: 2017/05/12 17:38:26 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		add_new(t_printf *elem, va_list *ap)
{
	if ((elem->type == 'S') || ((elem->type == 's' ||
	elem->type == 'c') && elem->modificator == 'l'))
		return (print_wchar(elem, ap));
	else if (elem->type == 's')
		return (print_string(elem, ap));
	else if (elem->type == 'p')
		return (print_adress(elem, ap));
	else if (elem->type == 'd' || elem->type == 'i' || elem->type == 'D')
		return (print_int(elem, ap));
	else if (elem->type == 'f' || elem->type == 'F')
		return (print_double(elem, ap));
	else if (elem->type == 'e' || elem->type == 'E')
		return (print_double_e(elem, ap));
	else if (elem->type == 'g' || elem->type == 'G')
		return (print_double_short(elem, ap));
	else if (elem->type == 'u' || elem->type == 'U')
		return (print_int_unsigned(elem, ap));
	else if (elem->type == 'o' || elem->type == 'O' || elem->type == 'x'
			|| elem->type == 'X' || elem->type == 'b')
		return (print_another_system(elem, ap));
	else if (elem->type == 'c' || elem->type == 'C')
		return (print_char(elem, ap, 0));
	else
		return (print_char(elem, ap, 1));
	return (0);
}

int		ft_find_per(va_list *ap, int *i, char *format)
{
	t_printf	*elem;
	int			ret;

	if (format[*i + 1] == '\0')
	{
		(*i)++;
		return (0);
	}
	elem = (t_printf *)malloc(sizeof(t_printf));
	create_type(format, i, ap, &elem);
	if (elem != NULL)
	{
		ret = add_new(elem, ap);
		if (elem->flags)
			free(elem->flags);
		free(elem);
		return (ret);
	}
	return (0);
}

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	int			i;
	int			ret;
	char		*test;

	i = 0;
	test = ft_strdup(format);
	va_start(ap, format);
	ret = 0;
	while (format[i])
	{
		if (format[i] == '%')
			ret += ft_find_per(&ap, &i, (char *)format);
		// else if (format[i] == '{')
		// 	i = ft_colors(test, i);
		else
		{
			ft_putchar(test[i++]);
			ret++;
		}
	}
	free(test);
	va_end(ap);
	return (ret);
}
