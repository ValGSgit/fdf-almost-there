/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagarcia <vagarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 14:39:31 by vagarcia          #+#    #+#             */
/*   Updated: 2024/11/13 12:57:32 by vagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

size_t	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

size_t	uintputnbr(unsigned int n)
{
	size_t	len;

	len = 0;
	if (n >= 10)
	{
		len += uintputnbr(n / 10);
		len += ft_putchar(n % 10 + '0');
	}
	if (n < 10)
		len += ft_putchar(n % 10 + '0');
	return (len);
}

int	ft_printpercent(void)
{
	write(1, "%", 1);
	return (1);
}
