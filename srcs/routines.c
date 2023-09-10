/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 17:27:44 by ofadahun          #+#    #+#             */
/*   Updated: 2023/09/10 19:56:35 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_print_action(t_philo *philo, const char *action_str)
{
	int		philo_id;
	size_t	start_time;
	
	pthread_mutex_lock(philo->write_lock);
	philo_id = philo->id;
	start_time = philo->start_time;
	if (!(*philo->dead))
	{
		if (ft_strcmp(action_str, "has taken a fork") == 0)
			printf("%s%lu %d %s%s\n", YELLOW, get_time_in_ms() - start_time, philo_id, action_str, RESET);
		else if (ft_strcmp(action_str, "is eating") == 0)
			printf("%s%lu %d %s%s\n", GREEN, get_time_in_ms() - start_time, philo_id, action_str, RESET);
		else if (!ft_strcmp(action_str, "is sleeping"))
			printf("%lu %d %s\n", get_time_in_ms() - start_time, philo_id, action_str);
		else if (!ft_strcmp(action_str, "is thinking"))
			printf("%s%lu %d %s%s\n", CYAN, get_time_in_ms() - start_time, philo_id, action_str, RESET);
		else if (!ft_strcmp(action_str, "is dead"))
			printf("%s%lu %d %s%s\n", RED, get_time_in_ms() - start_time, philo_id, action_str, RESET);
	}
	pthread_mutex_unlock(philo->write_lock);
}

int ft_usleep(size_t ms)
{
	size_t	start;

	// usleep(ms * 1000);
	start = get_time_in_ms();
	while ((get_time_in_ms() - start) < ms)
		usleep(500);
	return (0);
}

int	pick_forks(t_philo *philo)
{
	if (philo->id == 1)
	{
		while((philo + philo->philo_no - 1)->my_fork_picked)
			continue ;
	}
	else
	{
		while((philo - 1)->my_fork_picked)
			continue ;
	}
	pthread_mutex_lock(philo->r_fork);
	ft_print_action(philo, "has taken a fork");
	pthread_mutex_lock(philo->l_fork);
	philo->my_fork_picked = 1;
	ft_print_action(philo, "has taken a fork");
	// if ((philo->id % 2))
	// {
	// 	// if (philo->id != philo->philo_no)
	// 	// {
	// 	// 	while((philo + 1)->my_fork_picked)
	// 	// 		continue ;
	// 	// }
	// 	// else
	// 	// {
	// 	// 	while((philo - (philo->philo_no - 1))->my_fork_picked)
	// 	// 		continue ;
	// 	// }
	// 	pthread_mutex_lock(philo->r_fork);
	// 	ft_print_action(philo, "has taken a fork");
	// 	pthread_mutex_lock(philo->l_fork);
	// 	philo->my_fork_picked = 1;
	// 	ft_print_action(philo, "has taken a fork");
	// }
	// else
	// {
	// 	pthread_mutex_lock(philo->l_fork);
	// 	ft_print_action(philo, "has taken a fork");
	// 	pthread_mutex_lock(philo->r_fork);
	// 	philo->my_fork_picked = 1;
	// 	ft_print_action(philo, "has taken a fork");
	// }
	return (1);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	philo->my_fork_picked = 0;
	pthread_mutex_unlock(philo->r_fork);
	// if ((philo->id % 2))
	// {
	// 	pthread_mutex_unlock(philo->l_fork);
	// 	pthread_mutex_unlock(philo->r_fork);
	// 	philo->my_fork_picked = 0;
	// }
	// else
	// {
	// 	pthread_mutex_unlock(philo->l_fork);
	// 	philo->my_fork_picked = 0;
	// 	pthread_mutex_unlock(philo->r_fork);
	// }
}

void	*thread_routine(void	*arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	// pthread_mutex_lock(philo->meal_lock);
	// pthread_mutex_unlock(philo->meal_lock);
	philo->start_time = get_time_in_ms();
	philo->last_meal = get_time_in_ms();
	while (!(*(philo->dead)))
	{
		ft_print_action(philo, "is thinking");
		pick_forks(philo);
		ft_print_action(philo, "is eating");
		philo->last_meal = get_time_in_ms();
		ft_usleep(philo->time_to_eat);
		drop_forks(philo);
		philo->meals_eaten += 1;
		if (philo->meals_eaten == philo->meals_to_eat)
			break ;
		ft_print_action(philo, "is sleeping");
		ft_usleep(philo->time_to_sleep);
		// usleep(1000);
	}
	*philo->philo_eaten += 1;
	return (NULL);
}

void	die_from_hunger(t_philo *philo, int philo_no, int *dead)
{
	int		i;

	i = 0;
	while(i < philo_no)
	{
		if ((philo + i)->start_time && ((get_time_in_ms() - (philo + i)->last_meal) > (philo + i)->time_to_die))
		{
			*dead = 1;
			// printf("current time in ms: %lu   &&   last meal in ms: %lu  && start time in ms: %lu\n", get_time_in_ms(), (philo + i)->last_meal, (philo + i)->start_time);
			printf("%s%lu %d has died%s\n", RED, get_time_in_ms() - (philo + i)->start_time, (philo + i)->id, RESET);
			return ;
		}
		i++;
	}
}


void    *thread_monitor(void *arg)
{
    t_program	*program;

	program = (t_program *)arg;
	// pthread_mutex_lock(&program->meal_lock);
	// while(!program->started)
	// {
	// 	printf("i am here\n");
	// 	continue ;
	// }
	// pthread_mutex_unlock(&program->meal_lock);
	while (1)
	{
		if (program->dead || program->philo_eaten == program->philo_no)
		{
			printf("Program ended\n");
			exit(EXIT_SUCCESS);
		}
		die_from_hunger(program->philo, program->philo_no, &program->dead);
	}
	return (NULL);
}