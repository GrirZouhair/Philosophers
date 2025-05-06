/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogrir <zogrir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 01:52:30 by zogrir            #+#    #+#             */
/*   Updated: 2025/05/06 05:58:21 by zogrir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_msg_caller(int msg)
{
	if (msg == 1)
		printf("\033[1;31m🛑ERROR: Argument number\033[0m\n");
	else if (msg == 2)
		printf("\033[1;31m🛑ERROR: enter a valid And positive numbers\033[0m\n");
	else if (msg == 3)
		printf("\033[1;31m🛑ERROR: Arguments must be > 0.\033[0m\n");
	else if (msg == 4)
		printf("\033[1;31m🛑ERROR: OverFlow number.\033[0m\n");
	else if (msg == 5)
		printf("\033[1;31m🛑ERROR: Failed to allocate memory.\033[0m\n");
	else if (msg == 6)
		printf("\033[1;31m🛑ERROR: Failed initialize mutexes for forks.\033[0m\n");
	else if (msg == 7)
		printf("\033[1;31m🛑ERROR: Failed to initialize print mutex.\033[0m\n");
	else if (msg == 8)
		printf("\033[1;31m🛑ERROR: Philosophers count must be <= 200\033[0m\n");
}
