/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 22:51:33 by alouzizi          #+#    #+#             */
/*   Updated: 2023/01/10 23:02:57 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_len(int nb)
{
	int	i;

	i = 0;
	if (nb < 0)
		i++;
	while (nb != 0)
	{
		nb = nb / 10;
		i ++;
	}
	return (i);
}

static char	*to_string(char *str, int n, int len)
{
	int	s;

	s = 0;
	if (n < 0)
	{
		str[0] = '-';
		s++;
		n = n * -1;
	}
	while (n != 0)
	{
		str[len - 1] = (n % 10) + 48;
		n = n / 10;
		s++;
		len--;
	}
	str[s] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	int		i;
	int		k;
	char	*s;

	k = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	i = ft_len(n);
	s = (char *)malloc(sizeof(char) * (i + 1));
	if (!s)
		return (0);
	return (to_string(s, n, i));
}
