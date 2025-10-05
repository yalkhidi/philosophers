/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:04:36 by yalkhidi          #+#    #+#             */
/*   Updated: 2025/10/05 10:06:41 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	unsigned long	*array;
	t_input			*input;

	array = collect_input(ac, av);
	if (array)
	{
		input = assign_inputs(array);
		init(input);
		free_resources(input, NULL);
	}
}
