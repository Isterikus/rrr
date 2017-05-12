/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 19:11:19 by dkovalen          #+#    #+#             */
/*   Updated: 2017/05/11 19:53:09 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = -1;
	if (s == NULL)
		return (NULL);
	while (s[++i])
		if (s[i] == c)
			return ((char *)(s + i));
	if (c == '\0')
		return ((char *)(s + i));
	return (NULL);
}
