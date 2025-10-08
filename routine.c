/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:54:12 by yalkhidi          #+#    #+#             */
/*   Updated: 2025/10/05 14:19:12 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	still_alive(t_input *input)
{
	pthread_mutex_lock(&input->dead_lock);
	if (input->dead == 1)
	{
		pthread_mutex_unlock(&input->dead_lock);
		return (false);
	}
	pthread_mutex_unlock(&input->dead_lock);
	return (true);
}

void	philo_sleep_think(t_philo *philo)
{
	if (philo->input->n_philo != 1)
	{
		log_status(philo, "is sleeping");
		smart_usleep(philo->input, philo->input->t_sleep);
		log_status(philo, "is thinking");
	}
}

// void	philo_eat(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->input->fork_locks[philo->r_fork]);
// 	philo->input->forks[philo->r_fork] = 1;
// 	log_status(philo, "has taken a fork");
// 	if (philo->input->n_philo == 1)
// 	{
// 		smart_usleep(philo->input, philo->input->t_die);
// 		pthread_mutex_unlock(&philo->input->fork_locks[philo->r_fork]);
// 		return ;
// 	}
// 	pthread_mutex_lock(&philo->input->fork_locks[philo->l_fork]);
// 	philo->input->forks[philo->l_fork] = 1;
// 	log_status(philo, "has taken a fork");
// 	pthread_mutex_lock(&philo->meal_lock);
// 	philo->eating = 1;
// 	philo->last_meal = get_time();
// 	log_status(philo, "is eating");
// 	smart_usleep(philo->input, philo->input->t_eat);
// 	philo->meals_ate++;
// 	philo->eating = 0;
// 	pthread_mutex_unlock(&philo->meal_lock);
	
// 	pthread_mutex_unlock(&philo->input->fork_locks[philo->l_fork]);
// 	philo->input->forks[philo->l_fork] = 0;
// 	pthread_mutex_unlock(&philo->input->fork_locks[philo->r_fork]);
// 	philo->input->forks[philo->r_fork] = 0;
// }

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->input->fork_locks[philo->r_fork]);
	philo->input->forks[philo->r_fork] = 1;
	log_status(philo, "has taken a fork");
	if (philo->input->n_philo == 1)
	{
		smart_usleep(philo->input, philo->input->t_die);
		pthread_mutex_unlock(&philo->input->fork_locks[philo->r_fork]);
		return ;
	}
	pthread_mutex_lock(&philo->input->fork_locks[philo->l_fork]);
	philo->input->forks[philo->l_fork] = 1;
	log_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->meal_lock);
	philo->eating = 1;
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_lock);

	log_status(philo, "is eating");
	smart_usleep(philo->input, philo->input->t_eat);
	
	pthread_mutex_lock(&philo->meal_lock);
	philo->meals_ate++;
	philo->eating = 0;
	pthread_mutex_unlock(&philo->meal_lock);
	
	pthread_mutex_unlock(&philo->input->fork_locks[philo->l_fork]);
	philo->input->forks[philo->l_fork] = 0;
	pthread_mutex_unlock(&philo->input->fork_locks[philo->r_fork]);
	philo->input->forks[philo->r_fork] = 0;
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (still_alive(philo->input))
	{
		philo_eat(philo);
		philo_sleep_think(philo);
	}
	return (arg);
}
