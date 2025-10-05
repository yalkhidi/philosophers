/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 17:14:23 by yalkhidi          #+#    #+#             */
/*   Updated: 2025/10/02 13:05:32 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

unsigned long	ft_atoi(const char *str)
{
	int				i;
	unsigned long	outcome;

	i = 0;
	outcome = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		return (0);
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		outcome = outcome * 10 + (str[i] - '0');
		if (outcome > UINT_MAX)
		{
			i = -1;
			return (i);
		}
		i++;
	}
	return (outcome);
}

bool	ft_isdigit(char d)
{
	if (d >= '0' && d <= '9')
		return (true);
	return (false);
}

bool	is_within_limits(unsigned long num)
{
	if (num > UINT_MAX || num <= 0)
		return (false);
	return (true);
}

void	print_message(char *message)
{
	int	i;

	i = 0;
	while (message[i])
		i++;
	write(2, message, i);
	exit(1);
}
