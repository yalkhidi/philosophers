/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:54:12 by yalkhidi          #+#    #+#             */
/*   Updated: 2025/10/05 10:56:47 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	still_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->input->dead_lock);
	if (philo->input->dead == 1)
	{
		pthread_mutex_unlock(&philo->input->dead_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->input->dead_lock);
	return (1);
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

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->input->forks[philo->r_fork]);
	log_status(philo, "has taken a fork");
	if (philo->input->n_philo == 1)
	{
		smart_usleep(philo->input, philo->input->t_die);
		pthread_mutex_unlock(&philo->input->forks[philo->r_fork]);
		return ;
	}
	pthread_mutex_lock(&philo->input->forks[philo->l_fork]);
	log_status(philo, "has taken a fork");
	philo->eating = 1;
	log_status(philo, "is eating");
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time();
	philo->meals_ate++;
	pthread_mutex_unlock(&philo->meal_lock);
	smart_usleep(philo->input, philo->input->t_eat);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->input->forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->input->forks[philo->r_fork]);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (still_alive(philo))
	{
		philo_eat(philo);
		philo_sleep_think(philo);
	}
	return (arg);
}
