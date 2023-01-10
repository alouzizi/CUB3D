/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 22:54:36 by alouzizi          #+#    #+#             */
/*   Updated: 2023/01/10 22:54:38 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s;
	int		i;

	if (s1 != NULL && s2 != NULL )
		i = (ft_strlen(s1)) + (ft_strlen(s2));
	else
		return (0);
	s = (char *)malloc(i + 1);
	if (!s)
		return (0);
	while (*s1)
		*s++ = *s1++;
	while (*s2)
		*s++ = *s2++;
	*s = '\0';
	return (s - i);
}
