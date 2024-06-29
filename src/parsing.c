/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frankgar <frankgar@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 18:17:51 by frankgar          #+#    #+#             */
/*   Updated: 2024/06/29 20:04:31 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_exit(char *error_str, void *target1)
{
	if (target1)
		free(target1);
	if (error_str)
		printf(RED"%s%s", error_str, RESET);
	return (1);
}

int	limits_error(int argc, char **argv)
{
	int		i;
	int		j;
	int		k;
	char	simpl_nmb[13];

	i = 0;
	while (++i < argc)
	{
		j = -1;
		k = 0;
		ft_bzero(simpl_nmb, 13);
		if (argv[i][0] == '+' || argv[i][0] == '-')
			if (argv[i][0] == '-')
				simpl_nmb[k++] = argv[i][++j];
		while (argv[i][++j] == '0')
			;
		while (argv[i][j] != '\0' && k < 13)
			simpl_nmb[k++] = argv[i][j++];
		if ((simpl_nmb[0] == '-' && ((k == 11 && ft_strncmp \
			(simpl_nmb, "-2147483648", 12) > 0) || k > 11)) \
			|| (simpl_nmb[0] != '-' && ((k == 10 && ft_strncmp \
					(simpl_nmb, "2147483647", 11) > 0) || k > 10)))
			return (0);
	}
	return (1);
}

int	syntax_error(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = -1;
		if (argv[i][0] == '+' || argv[i][0] == '-')
			j++;
		while (argv[i][++j] != '\0')
			if ((argv[i][j] < '0' || argv[i][j] > '9') \
			&& (argv[i][j] != '+' || argv[i][j] != '-'))
				return (0);
		if ((j == 1 && (argv[i][0] == '+' || argv[i][0] == '-')) || !*argv[i])
			return (0);
	}
	return (1);
}

int	limits_parameters(int *numbers, int argc)
{
	int	i;

	i = 0;
	while (i < argc - 1)
	{
		if (i == 0 && numbers[i] > 200)
			return (ft_exit(E_NPHILOS, NULL) * 0);
		if ((i == 4 && numbers[i] < 0) || (i != 4 && numbers[i] <= 0))
			return (ft_exit(E_LOWER_ARG, NULL) * 0);
		i++;
	}
	return (1);
}

int	parsing(int argc, char **argv, t_simulation *philos)
{
	int	*numbers;
	int	i;

	i = 0;
	if (argc != 5 && argc != 6)
		return (ft_exit(E_ARGS, NULL));
	if (!(syntax_error(argc, argv) && limits_error(argc, argv)))
		return (ft_exit(E_SYNTAX_LIMITS, NULL));
	numbers = malloc(argc * sizeof(int));
	if (!numbers)
		return (ft_exit(E_MALLOC, NULL));
	while (++i < argc)
		numbers[i - 1] = ft_atoi(argv[i]);
	if (!limits_parameters(numbers, argc))
		return (ft_exit(NULL, numbers));
	philos->n_philos = numbers[0];
	philos->t_death = numbers[1];
	philos->t_eat = numbers[2];
	philos->t_sleep = numbers[3];
	philos->n_meals = -1;
	if (argc == 6)
		philos->n_meals = numbers[4];
	free(numbers);
	return (0);
}
