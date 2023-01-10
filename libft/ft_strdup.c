/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 22:53:08 by alouzizi          #+#    #+#             */
/*   Updated: 2023/01/10 22:53:29 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup( char *s)
{
	int		len;
	int		i;
	char	*p;

	i = 0;
	len = ft_strlen(s) + 1;
	p = malloc(len * sizeof(char));
	if (!p)
		return (0);
	while (s[i])
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
