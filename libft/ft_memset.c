/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 22:51:45 by alouzizi          #+#    #+#             */
/*   Updated: 2023/01/10 23:03:25 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int c, size_t num)
{
	int				i;
	unsigned char	*s;

	i = 0;
	s = ptr;
	while (num)
	{
		s[i] = c;
		i++;
		num--;
	}
	return (ptr);
}
