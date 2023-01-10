/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 22:52:36 by alouzizi          #+#    #+#             */
/*   Updated: 2023/01/10 23:04:19 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_realoc(char **tab, int size)
{
	int		i;
	char	**t;

	i = 0;
	t = (char **)malloc(sizeof(char *) * size);
	if (!t)
		return (NULL);
	while (i < size - 1)
	{
		t[i] = tab[i];
		i++;
	}
	free(tab);
	return (t);
}
