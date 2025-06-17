/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogrir <zogrir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 01:46:04 by zogrir            #+#    #+#             */
/*   Updated: 2025/06/08 08:36:44 by zogrir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{	
	t_data		data;
	t_philo		*philos;
	int			num_philos;

	if (argc != 5 && argc != 6)
		return (error_msg_caller(1), 1);
	num_philos = ft_atoi(argv[1]);
	if (num_philos <= 0 || num_philos > 200)
		return (error_msg_caller(4), 1);
	philos = malloc(sizeof(t_philo) * num_philos);
	if (!philos)
		return (error_msg_caller(5), 1);
	if (!init_all(argc, argv, &data, philos))
		return (free(philos), 1);
	free(data.forks);
	return (free(philos), 0);
}
