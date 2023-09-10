/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 17:29:34 by ofadahun          #+#    #+#             */
/*   Updated: 2023/09/10 15:33:36 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\v' || \
	*str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= 48 && *str <= 57)
	{
		res *= 10;
		res += *str - 48;
		str++;
	}
	return (res * sign);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while ((*(s1 + i) && *(s2 + i)))
	{
		if (*(s1 + i) > *(s2 + i) || *(s2 + i) > *(s1 + i))
			return ((unsigned char)*(s1 + i) - (unsigned char)*(s2 + i));
		i++;
	}
	if (!(*(s1 + i)) && !(*(s2 + i)))
		return (0);
	return ((unsigned char)*(s1 + i) - (unsigned char)*(s2 + i));
}
