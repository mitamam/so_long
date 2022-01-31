/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 22:30:20 by mmasuda           #+#    #+#             */
/*   Updated: 2021/04/19 10:04:17 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*re_lstlast(t_list *lst)
{
	if (lst->next == NULL)
		return (lst);
	return (re_lstlast(lst->next));
}

t_list	*ft_lstlast(t_list *lst)
{
	if (lst)
		return (re_lstlast(lst));
	return (NULL);
}
