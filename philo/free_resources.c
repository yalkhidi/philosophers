/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:25:33 by yalkhidi          #+#    #+#             */
/*   Updated: 2025/10/09 15:25:55 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_input *input)
{
	unsigned int	i;

	if (input->fork_locks)
	{
		i = -1;
		while (++i < input->n_philo)
			pthread_mutex_destroy(&input->fork_locks[i]);
		free(input->fork_locks);
	}
	if (input->philos)
	{
		i = -1;
		while (++i < input->n_philo)
			pthread_mutex_destroy(&input->philos[i].meal_lock);
		free(input->philos);
	}
	if (input->forks)
		free(input->forks);
	if (input)
	{
		pthread_mutex_destroy(&input->write_lock);
		pthread_mutex_destroy(&input->dead_lock);
		free(input);
	}
}

void	free_resources(t_input *input, char *message)
{
	destroy_mutexes(input);
	if (message)
		print_message(message);
}
