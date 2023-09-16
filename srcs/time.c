/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 14:00:38 by ofadahun          #+#    #+#             */
/*   Updated: 2023/09/16 14:00:39 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

size_t	get_time_in_ms(void)
{
	struct timeval	current_time;
	size_t			ms;

	gettimeofday(&current_time, NULL);
	ms = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (ms);
}

int	ft_usleep(size_t ms)
{
	size_t	start;

	start = get_time_in_ms();
	while ((get_time_in_ms() - start) < ms)
		usleep(500);
	return (0);
}

void	ft_srand(int min_delay_ms, int max_delay_ms)
{
	struct timeval	cur_time;
	unsigned int	rand_seed;
	unsigned int	range;
	unsigned int	random_ms;

	gettimeofday(&cur_time, NULL);
	rand_seed = (unsigned int) \
	(cur_time.tv_sec * 1000000 + cur_time.tv_usec + 42);
	rand_seed = rand_seed * 1103515245 + 12345;
	rand_seed = (rand_seed / 65536) % 32768;
	range = max_delay_ms - min_delay_ms + 1;
	random_ms = min_delay_ms + (rand_seed % range);
	usleep(random_ms);
}
