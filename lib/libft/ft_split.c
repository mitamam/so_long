/* ************************************************************************** */
/*                                                                        */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 22:30:20 by mmasuda           #+#    #+#             */
/*   Updated: 2021/04/15 00:01:37 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*free_memory(char **newstr, int word_count)
{
	int	i;

	i = 0;
	while (i < word_count)
	{
		free(newstr[i]);
		i++;
	}
	free(newstr);
	return (NULL);
}

static char	*ft_strndup(const char *s1, size_t n, size_t i)
{
	char		*s2;
	size_t		j;

	j = 0;
	if (!s1)
		return (NULL);
	s2 = (char *)malloc(sizeof(char) * (n + 1));
	if (!s2)
		return (NULL);
	while (j < n)
	{
		s2[j] = s1[i + j];
		j++;
	}
	s2[j] = '\0';
	return (s2);
}

static char	**split_words(char **newstr, char const *s, char c, int qty)
{
	size_t	i;
	size_t	word_count;
	size_t	split;

	word_count = 0;
	i = 0;
	while (ft_strlen(s) > i)
	{
		split = 0;
		if (s[i] != c)
		{
			while (s[i + split] && s[i + split] != c)
				split++;
			newstr[word_count] = ft_strndup(s, split, i);
			if (!newstr[word_count])
				return (free_memory(newstr, word_count));
			word_count++;
		}
		i += split + 1;
	}
	if (word_count == 0)
		newstr[word_count] = ft_strndup(NULL, 0, 0);
	newstr[qty] = NULL;
	return (newstr);
}

char	**ft_split(char const *s, char c)
{
	char	**newstr;
	int		qty;
	int		i;

	qty = 0;
	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i])
				i++;
			qty++;
		}
		else
			i++;
	}
	if (qty == 0)
		qty = 1;
	newstr = (char **)malloc(sizeof(char *) * (qty + 1));
	if (!newstr)
		return (NULL);
	return (split_words(newstr, s, c, qty));
}
