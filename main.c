/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 18:15:15 by dkovalen          #+#    #+#             */
/*   Updated: 2017/05/12 17:27:50 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <locale.h>

int main(void)
{
	setlocale(LC_ALL, "");
	int			i;
	// double		x = -8000;
	// double			x = 2147483648;
	// double		x = 2.9988;
	// double		x = 503.0;
	// double			x = 1333.45678;
	double			x = 1454.87654;

	i = 0;
	//printf("  %d\n", ft_printf("{%10S}", NULL));
	while (i < 5)
	{
		printf("----------------------------------\n");
		printf("  %d\n", ft_printf("%.*f", i, x));
		printf("  %d\n", printf("%.*f", i, x));
		printf("----------------------------------\n");
		i++;
	}
 	return (0);
}
