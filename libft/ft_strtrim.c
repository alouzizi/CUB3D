/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 22:56:05 by alouzizi          #+#    #+#             */
/*   Updated: 2023/01/11 02:03:33 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_right(char const *s1, char const *set, int j)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s1[j])
		{
			j--;
			i = 0;
		}
		else
			i++;
	}
	return (j);
}

static int	ft_left(char const *s1, char const *set)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (set[j])
	{
		if (set[j] == s1[i])
		{
			i++;
			j = 0;
		}
		else
			j++;
	}
	return (i);
}

char	*ft_strtrim(char *s1, char *set)
{
	int		i;
	char	*s;
	int		j;
	int		l;

	l = 0;
	if (s1 == NULL)
		return ((char *)s1);
	j = ft_strlen(s1) - 1;
	i = ft_left(s1, set);
	j = ft_right(s1, set, j);
	l = j - i + 1;
	if (l <= 0)
		return (ft_strdup("\0"));
	j = l;
	s = malloc(sizeof(*s1) * (l + 1));
	if (!s)
		return (0);
	while (l--)
		*s++ = s1[i++];
	*s = '\0';
	return (s - j);
}
