/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frankgar <frankgar@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 19:56:12 by frankgar          #+#    #+#             */
/*   Updated: 2024/06/29 20:16:34 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	get_current_time(void)
{
	struct timeval		tmp;
	unsigned int		current_time;

	gettimeofday(&tmp, NULL);
	current_time = (unsigned int)tmp.tv_sec * 1000 + tmp.tv_usec * 0.001;
	return (current_time);
}

unsigned int	get_sim_time(t_simulation *sim)
{
	return (get_current_time() - sim->t_start);
}

int	comprove_death(t_simulation *sim)
{
	int	is_n_death;

	is_n_death = 1;
	pthread_mutex_lock(&sim->check_flag);
	if (sim->flag_death == 1)
		is_n_death = 0;
	pthread_mutex_unlock(&sim->check_flag);
	return (is_n_death);
}
