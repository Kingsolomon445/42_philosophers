/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:22:40 by ofadahun          #+#    #+#             */
/*   Updated: 2023/09/13 18:10:16 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


int main(int argc, char *argv[])
{
	t_philo     *philo;
	t_program   *program;
	
	if (argc < 5 || argc > 6)
		return (printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat\
		 time_to_sleep [number_of_times_each_philosopher_must_eat]\n"), 1);
	if (!check_if_all_digits(argv))
		return (printf("All arguments must be digits\n"), 1);
	if (!check_if_all_positive(argv))
		return (printf("All arguments must be positive integer\n"), 1);
	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (1);
	program = malloc(sizeof(t_program));
	if (!program)
		return (free(philo), 1);
	program->philo = NULL;
	program->forks = NULL;
	init_args(program, argv);
	if (init_program(program))
		wait_for_all_threads(program);
	close_program(program);
	return (0);
}
