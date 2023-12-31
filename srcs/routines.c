/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 17:27:44 by ofadahun          #+#    #+#             */
/*   Updated: 2023/09/16 18:57:28 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	has_died(t_program *program)
{
	int		i;
	size_t	start_time;

	i = 0;
	while (i < program->philo_no)
	{
		pthread_mutex_lock(&program->last_meal_lock);
		start_time = program->start_time;
		if (start_time && (program->philo + i)->last_meal && ((get_time_in_ms() - \
		(program->philo + i)->last_meal) > program->time_to_die))
		{
			pthread_mutex_unlock(&program->last_meal_lock);
			pthread_mutex_lock(&program->dead_lock);
			program->dead = 1;
			pthread_mutex_unlock(&program->dead_lock);
			pthread_mutex_lock(&program->write_lock);
			printf("%s%lu %d died%s\n", RED, get_time_in_ms() - \
			start_time, (program->philo + i)->id, RESET);
			pthread_mutex_unlock(&program->write_lock);
			return (1);
		}
		pthread_mutex_unlock(&program->last_meal_lock);
		i++;
	}
	return (0);
}

static int	ft_eat(t_philo *philo)
{
	if (!pick_forks(philo) || !ft_print_action(philo, "is eating"))
		return (0);
	pthread_mutex_lock(philo->last_meal_lock);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(philo->last_meal_lock);
	ft_usleep(philo->time_to_eat);
	drop_forks(philo);
	philo->meals_eaten += 1;
	if (philo->meals_eaten == philo->meals_to_eat)
		return (0);
	return (1);
}

void	*thread_routine(void	*arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->last_meal_lock);
	philo->last_meal = get_time_in_ms();
	if (*philo->start_time == 0)
		*philo->start_time = get_time_in_ms();
	pthread_mutex_unlock(philo->last_meal_lock);
	while (1)
	{
		if (is_dead(philo) || !ft_eat(philo))
			break ;
		if (!ft_print_action(philo, "is sleeping"))
			break ;
		ft_usleep(philo->time_to_sleep);
		if (!ft_print_action(philo, "is thinking"))
			break ;
		ft_srand(500, 2000);
	}
	pthread_mutex_lock(philo->philo_eaten_lock);
	*philo->philo_eaten += 1;
	pthread_mutex_unlock(philo->philo_eaten_lock);
	drop_forks(philo);
	return (NULL);
}

void	*thread_monitor(void *arg)
{
	t_program	*program;

	program = (t_program *)arg;
	while (1)
	{
		pthread_mutex_lock(&program->philo_eaten_lock);
		if (program->philo_eaten == program->philo_no)
		{
			pthread_mutex_unlock(&program->philo_eaten_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&program->philo_eaten_lock);
		if (has_died(program))
			return (NULL);
	}
	return (NULL);
}
