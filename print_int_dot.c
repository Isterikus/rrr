/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int_dot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 13:44:41 by dkovalen          #+#    #+#             */
/*   Updated: 2017/05/12 17:28:06 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

long double	ft_round_up(long double t)
{
	long double d;

	d = (uintmax_t)t;
	if (t <= d)
		return (d);
	return (d + 1);
}

long double	ft_round_down(long double t)
{
	long double d;

	d = (uintmax_t)t;
	if (t >= d)
		return (d);
	return (d - 1);
}

long double	ft_round_fraction(long double t)
{
	long double up;
	long double down;

	up = ft_round_up(t);
	down = ft_round_down(t);
	if (t - down == 0.5 && !((uintmax_t)down ^ 1))
		return (down);
	else if (up - t == 0.5)
		return (up);
	if (t - down >= 0.5)
		return (up);
	else
		return (down);
}

int			check_srav(long double d, int acc)
{
	int		i;

	i = 0;
	d = d * ft_10pow(acc);
	d = d - (uintmax_t)d;
	// printf("{%Lf}\n", d);
	if (d > 0.5)
		return (1);
	return (0);
}

long double	srav_na_9(long double d, int acc)
{
	if (check_srav(d, acc))
	{
		//d = ((double)(int)(d * ft_10pow(acc)) / (double)(ft_10pow(acc)));
		// printf("SRAAAVVV  -  ");
		// printf("%Lf\n", ((long double)((10 - ((uintmax_t)(d * ft_10pow(acc)) % 10))) / ft_10pow(acc)));
		//d++;
		if (acc != 0)
			d += ((long double)1 / (long double)ft_10pow(acc));
		else
			d++;
	}
	// printf("ost = %Lf\n", d);
	return (d);
}

char		*int_part(long double *d, t_printf *elem)
{
	char		*str;
	int			i;
	long double	copy;
	int			min;
	int			len;

	i = 0;
	min = 0;
	if ((*d) < 0)
	{
		(*d) = -(*d);
		min = 1;
	}
	elem->type = 'f';
	(*d) = srav_na_9(*d, elem->accuracy);
	// printf("ACC = %d\n", elem->accuracy);
	// printf("D = %Lf\n", *d);
	copy = *d;
	while (copy > 10)
	{
		copy = copy / 10;
		i++;
	}
	// printf("copy = %Lf\n", copy);
	// printf("%d\n", i + min + 2);
	str = (char *)malloc(sizeof(char) * (i + min + 2));
	// str[i + min] = (uintmax_t)copy % 10 + 48;
	str[i + 1 + min] = '\0';
	copy = *d;
	len = min;
	i += min;
	// printf("```%Lf```\n", copy);
	while (i >= min)
	{
		str[i--] = (uintmax_t)copy % 10 + 48;
		copy = copy / 10;
		// printf("[%Lf][%Lf]\n", copy, *d);
	}
	(min == 1) ? str[0] = '-' : 0;
	return (str);
}

char	*ft_get_double(long double d, t_printf *elem)
{
	uintmax_t		i;
	char			*str;
	char			*dot;
	int				j;

	str = int_part(&d, elem);
	if (d < 0)
		d = -d;
	if (elem->accuracy == 0)
		return (str);
	// if ((elem->type == 'g' || elem->type == 'G') && ft_strlen(str) == 6)
	// 	return (str);
	str = ft_strjoin2(str, ".");
	d = d - (uintmax_t)d;
	i = (uintmax_t)((double)d * ft_10pow(elem->accuracy));
	j = ft_intlen((uintmax_t)i, 1);
	if (j == 0)
		j++;
	while (j++ < elem->accuracy)
		str = ft_strjoin(str, "0");
	dot = ft_itoa_base(i, 10, 0);
	str = ft_strjoin(str, dot);
	return (str);
}

char	*ft_get_double_e(long double d, t_printf *elem)
{
	char		*str;
	long int	i;
	int			j;
	char		*dot;

	d = d / ft_intlen(d, 0);
	str = ft_itoa_base((int)d, 10, 0);
	if (d < 0)
		d = -d;
	i = (long int)d;
	d = d - i;
	i = d * (ft_10pow(elem->accuracy) * 10);
	if (i % 10 >= 5)
		i += 10;
	i = i / 10;
	str = ft_strjoin(str, ".");
	j = ft_intlen((int)i, 1);
	if (j == 0 || elem->type == 'g' || elem->type == 'G')
		j++;
	while (j++ < 6)
		str = ft_strjoin(str, "0");
	dot = ft_itoa_base(i, 10, 0);
	str = ft_strjoin(str, dot);
	return (str);
}

int		print_e(t_printf *elem, long double d, char *str, int ten)
{
	if (elem->type == 'e' || elem->type == 'g')
	{
		if (ten > 9)
			str = ft_strjoin(str, "e+");
		else
			str = ft_strjoin(str, "e+0");
	}
	else
	{
		if (ten > 9)
			str = ft_strjoin(str, "E+");
		else
			str = ft_strjoin(str, "E+0");
	}
	str = ft_strjoin(str, ft_itoa_base(ten - 1, 10, 0));
	if (elem->width != 0)
		return (int_width(elem, str, d));
	else
	{
		print_plus(d, elem);
		ft_putstr(str);
	}
	return (ft_strlen(str) + count_plus(d, elem));
}

int		print_double_e(t_printf *elem, va_list *ap)
{
	long double	d;
	int			ten;
	char		*str;

	if (elem->modificator == 'Z')
		d = va_arg(*ap, long double);
	else
		d = va_arg(*ap, double);
	if (elem->accuracy == -12345)
		elem->accuracy = 6;
	str = ft_get_double_e(d, elem);
	ten = ft_intlen(d, 1);
	return (print_e(elem, d, str, ten));
}

int		print_double_short(t_printf *elem, va_list *ap)
{
	long double	d;
	int			ten;
	char		*str1;
	char		*str2;

	if (elem->modificator == 'Z')
		d = va_arg(*ap, long double);
	else
		d = va_arg(*ap, double);
	if (elem->accuracy == -12345)
		elem->accuracy = 5;
	str1 = ft_get_double(d, elem);
	str2 = ft_get_double_e(d, elem);
	ten = ft_intlen(d, 1);
	if (count_dig(str1) < 7)
	{
		str1[7] = '\0';
		return (print_dob(str1, elem, d));
	}
	else
		return (print_e(elem, d, str2, ten));
}
