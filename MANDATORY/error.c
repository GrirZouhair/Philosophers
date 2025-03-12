/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogrir <zogrir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 01:52:30 by zogrir            #+#    #+#             */
/*   Updated: 2025/03/12 03:22:18 by zogrir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_msg_caller(int msg)
{
	if (msg == 1)
		printf("\033[1;31m🛑ERROR: Argument number\033[0m\n");
	else if (msg == 2)
		printf("\033[1;31m🛑ERROR: expecting only positive numbers\033[0m\n");
}