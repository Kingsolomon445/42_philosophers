/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:55:15 by ofadahun          #+#    #+#             */
/*   Updated: 2023/09/16 14:01:24 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_print_action(t_philo *philo, const char *action_str)
{
	int		philo_id;
	size_t	start_time;

	if (is_dead(philo))
		return (0);
	philo_id = philo->id;
	start_time = philo->start_time;
	pthread_mutex_lock(philo->write_lock);
	if (ft_strcmp(action_str, "has taken a fork") == 0)
		printf("%s%lu %d %s%s\n", YELLOW, get_time_in_ms() - \
		start_time, philo_id, action_str, RESET);
	else if (ft_strcmp(action_str, "is eating") == 0)
		printf("%s%lu %d %s%s\n", GREEN, get_time_in_ms() - \
		start_time, philo_id, action_str, RESET);
	else if (!ft_strcmp(action_str, "is sleeping"))
		printf("%lu %d %s\n", get_time_in_ms() - \
		start_time, philo_id, action_str);
	else if (!ft_strcmp(action_str, "is thinking"))
		printf("%s%lu %d %s%s\n", CYAN, get_time_in_ms() - \
		start_time, philo_id, action_str, RESET);
	pthread_mutex_unlock(philo->write_lock);
	return (1);
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	close_program(t_program *program)
{
	destroy_all_mutex(program, program->philo_no);
	if (program->forks)
		free(program->forks);
	if (program->philo)
		free(program->philo);
	free(program);
}

void	wait_for_all_threads(t_program *program)
{
	t_philo		*philo;
	int			i;
	pthread_t	tid;

	i = 0;
	philo = program->philo;
	if (pthread_join(program->monitor_tid, NULL) == -1)
	{
		close_program(program);
		exit(EXIT_FAILURE);
	}
	while (i < program->philo_no)
	{
		tid = (philo + i)->tid;
		if (pthread_join(tid, NULL) == -1)
		{
			close_program(program);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	destroy_all_mutex(t_program *program, int philo_no)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&(program->write_lock));
	pthread_mutex_destroy(&(program->last_meal_lock));
	pthread_mutex_destroy(&(program->philo_eaten_lock));
	while (i < philo_no)
	{
		pthread_mutex_destroy(program->forks + i);
		i++;
	}
}
