/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 17:25:41 by ofadahun          #+#    #+#             */
/*   Updated: 2023/09/16 15:41:34 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_args(t_program *program, char *argv[])
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (i == 1)
			program->philo_no = ft_atoi(argv[i]);
		if (i == 2)
			program->time_to_die = ft_atoi(argv[i]);
		if (i == 3)
			program->time_to_eat = ft_atoi(argv[i]);
		if (i == 4)
			program->time_to_sleep = ft_atoi(argv[i]);
		if (i == 5)
			program->meals_to_eat = ft_atoi(argv[i]);
		i++;
	}
}

int	init_philo(t_program *program, int i)
{
	t_philo	*philo;

	philo = program->philo + i;
	philo->id = i + 1;
	philo->left_fork_acquired = 0;
	philo->right_fork_acquired = 0;
	philo->philo_no = program->philo_no;
	philo->time_to_die = program->time_to_die;
	philo->time_to_eat = program->time_to_eat;
	philo->time_to_sleep = program->time_to_sleep;
	philo->meals_to_eat = program->meals_to_eat;
	philo->meals_eaten = 0;
	philo->start_time = &(program->start_time);
	philo->philo_eaten = &(program->philo_eaten);
	philo->dead = &program->dead;
	philo->write_lock = &program->write_lock;
	philo->dead_lock = &program->dead_lock;
	philo->last_meal_lock = &program->last_meal_lock;
	philo->philo_eaten_lock = &program->philo_eaten_lock;
	philo->l_fork = program->forks + i;
	if (program->philo_no != 1)
		philo->r_fork = program->forks + ((i + 1) % program->philo_no);
	if (pthread_create(&philo->tid, NULL, thread_routine, philo) != 0)
		return (0);
	return (1);
}

pthread_mutex_t	*init_forks(int philo_no)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * philo_no);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < philo_no)
	{
		if (pthread_mutex_init(forks + i, NULL) == -1)
			return (NULL);
		i++;
	}
	return (forks);
}

int	init_program(t_program *program)
{
	int				i;

	i = 0;
	program->dead = 0;
	program->philo_no = program->philo_no;
	program->philo_eaten = 0;
	program->start_time = 0;
	if (pthread_mutex_init(&program->write_lock, NULL) == -1 || \
	pthread_mutex_init(&program->dead_lock, NULL) == -1 || \
	pthread_mutex_init(&program->last_meal_lock, NULL) == -1 || \
	pthread_mutex_init(&program->philo_eaten_lock, NULL) == -1)
		return (0);
	program->forks = init_forks(program->philo_no);
	program->philo = (t_philo *)malloc(sizeof(t_philo) * (program->philo_no));
	if (!program->philo || !program->forks)
		return (0);
	while (i < program->philo_no)
	{
		if (!init_philo(program, i))
			return (0);
		i++;
	}
	if (pthread_create(&program->monitor_tid, \
	NULL, thread_monitor, program) != 0)
		return (0);
	return (1);
}
