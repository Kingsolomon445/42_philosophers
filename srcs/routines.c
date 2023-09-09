/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 17:27:44 by ofadahun          #+#    #+#             */
/*   Updated: 2023/09/09 17:50:54 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*thread_routine(void	*arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	printf("My thread is running\n");
	return (NULL);
}

// void    *thread_monitor()
// {
    
// }