/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 22:50:28 by alouzizi          #+#    #+#             */
/*   Updated: 2023/01/10 23:04:42 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			if ((s[i - 1] == c || i == 0))
				count++;
			i++;
		}
	}
	return (count);
}

static char	**free_2d(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char		**tab;
	size_t		i;
	size_t		len;

	i = 0;
	if (!s)
		return (0);
	tab = (char **)malloc((ft_count(s, c) + 1) * sizeof(*tab));
	if (!tab)
		return (0);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		len = 0;
		while (s[len] && s[len] != c)
			len++;
		if (len != 0)
			tab[i++] = ft_substr((char *)s, 0, len);
		if (!tab[i - 1] && len != 0)
			return (free_2d(tab));
		s = len + s;
	}
	tab[i] = NULL;
	return (tab);
}
