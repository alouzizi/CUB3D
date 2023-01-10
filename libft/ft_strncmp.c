/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 22:55:00 by alouzizi          #+#    #+#             */
/*   Updated: 2023/01/10 22:55:02 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((str1[i] || str2[j]) && n)
	{
		if (str1[i] != str2[j])
			return ((unsigned char )str1[i] - (unsigned char )str2[j]);
		n--;
		i++;
		j++;
	}
	return (0);
}
