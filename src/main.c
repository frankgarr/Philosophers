/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frankgar <frankgar@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 17:28:55 by frankgar          #+#    #+#             */
/*   Updated: 2024/06/29 20:21:10 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_simulation(t_simulation *sim)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&sim->action_flag);
	while (i < sim->n_philos && !sim->flag_death)
	{
		if (pthread_create \
			(&sim->philo[i].philo, NULL, &philo_routine, &sim->philo[i]))
		{
			sim->flag_death = 1;
			ft_exit(E_THREAD, NULL);
		}
		i++;
	}
	sim->t_start = get_current_time();
	pthread_mutex_unlock(&sim->action_flag);
	return (0);
}

int	prepare_simulation(t_simulation *sim)
{
	int	i;

	i = 0;
	sim->philo = malloc(sim->n_philos * sizeof(t_philo));
	if (!sim->philo)
		return (ft_exit(E_MALLOC, NULL));
	if (pthread_mutex_init(&sim->action_flag, NULL))
		return (ft_exit(E_MUTEX, sim->philo));
	while (i < sim->n_philos)
	{
		sim->philo[i].id = i;
		sim->philo[i].n_meals = 0;
		sim->philo[i].last_meal = 0;
		sim->philo[i].sim = sim;
		if (pthread_mutex_init(&sim->philo[i].fork1, NULL))
			return (ft_exit(E_MUTEX, sim->philo));
		if (pthread_mutex_init(&sim->philo[i].last_meal_flag, NULL))
			return (ft_exit(E_MUTEX, sim->philo));
		if (i > 0)
			sim->philo[i].fork2 = &sim->philo[i - 1].fork1;
		i++;
	}
	sim->philo[0].fork2 = &sim->philo[sim->n_philos - 1].fork1;
	return (0);
}

void	destroy_mutex(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->n_philos)
	{
		pthread_mutex_destroy(&sim->philo[i].fork1);
		pthread_mutex_destroy(&sim->philo[i].last_meal_flag);
		i++;
	}
	pthread_mutex_destroy(&sim->check_flag);
	pthread_mutex_destroy(&sim->action_flag);
}

void	check_philo_status(t_simulation *sim)
{
	int	i;
	int	flag_meals;

	flag_meals = 0;
	while (comprove_death(sim) && flag_meals != sim->n_philos)
	{
		i = 0;
		flag_meals = 0;
		while (i < sim->n_philos)
		{
			pthread_mutex_lock(&sim->philo[i].last_meal_flag);
			if (sim->philo[i].n_meals == sim->n_meals)
				flag_meals++;
			if (get_sim_time(sim) - sim->philo[i].last_meal >= sim->t_death \
				&& sim->philo[i].n_meals != sim->n_meals)
				print_action(&sim->philo[i], DIE, ACT_DIE);
			pthread_mutex_unlock(&sim->philo[i].last_meal_flag);
			i++;
		}
	}
	while (i >= 0)
		pthread_join(sim->philo[i--].philo, NULL);
	free(sim->philo);
	destroy_mutex(sim);
}

int	main(int argc, char **argv)
{
	t_simulation	sim;

	ft_bzero(&sim, sizeof(sim));
	if (parsing(argc, argv, &sim))
		return (0);
	if (prepare_simulation(&sim))
		return (0);
	init_simulation(&sim);
	check_philo_status(&sim);
	return (0);
}
