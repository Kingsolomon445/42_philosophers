/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 20:43:50 by ofadahun          #+#    #+#             */
/*   Updated: 2023/09/13 20:44:27 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	pick_forks(t_philo *philo)
{
	if (philo->philo_no == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		philo->left_fork_acquired = 1;
		ft_print_action(philo, "has taken a fork");
		return (ft_usleep(philo->time_to_die + 5), 0);
	}
	else if (philo->id % 2)
	{
		pthread_mutex_lock(philo->r_fork);
		philo->right_fork_acquired = 1;
		ft_print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		philo->left_fork_acquired = 1;
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		philo->left_fork_acquired = 1;
		ft_print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		philo->right_fork_acquired = 1;
	}
	return (ft_print_action(philo, "has taken a fork"), 1);
}

void	drop_forks(t_philo *philo)
{
	if ((philo->id % 2))
	{
		if (philo->left_fork_acquired)
			pthread_mutex_unlock(philo->l_fork);
		philo->left_fork_acquired = 0;
		if (philo->right_fork_acquired)
			pthread_mutex_unlock(philo->r_fork);
		philo->right_fork_acquired = 0;
	}
	else
	{
		if (philo->right_fork_acquired)
			pthread_mutex_unlock(philo->r_fork);
		philo->right_fork_acquired = 0;
		if (philo->left_fork_acquired)
			pthread_mutex_unlock(philo->l_fork);
		philo->left_fork_acquired = 0;
	}
}