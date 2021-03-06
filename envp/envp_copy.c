/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envp_copy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/01 17:34:00 by cpopa         #+#    #+#                 */
/*   Updated: 2022/05/01 17:34:08 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_arrays(char **array)
{
	int	count;

	count = 0;
	while (array[count] != NULL)
		count++;
	return (count);
}

/*
** Function will attempt to find the variable
** and return its position in the envp list
*/

int	find_variable_position(char **envp, char *variable)
{
	int		i;
	char	**split;

	i = 0;
	while (envp[i] != NULL)
	{
		split = ft_split_variable(envp[i]);
		if (ft_strcmp(variable, split[0]) == 0)
		{
			free_string_array(split);
			return (i);
		}
		free_string_array(split);
		i++;
	}
	return (-1);
}

/*
** Function splits the environment variable into key and value
** If it doesn't have a value, the key will be returned
*/

char	**ft_split_variable(char *variable)
{
	int		i;
	char	**split;

	split = malloc(sizeof (char *) * 3);
	if (split == NULL)
		exit_on_error("Error :", 1);
	i = 0;
	split[1] = NULL;
	while (variable[i] != '=' && variable[i] != '\0')
		i++;
	split[0] = ft_substr(variable, 0, i);
	if (split[0] == NULL)
		exit_on_error("Error :", 1);
	if (variable[i] == '=')
	{
		split[1] = ft_strdup(&variable[i + 1]);
		if (split[1] == NULL)
			exit_on_error("Error :", 1);
	}
	split[2] = NULL;
	return (split);
}

/*
** Function will create a copy of the envp variable
** which allows us to modify it
*/

char	**copy_envp(char **envp)
{
	int		count;
	char	**envp_copy;
	int		i;

	count = count_arrays(envp);
	envp_copy = malloc(sizeof (char *) * (count + 1));
	i = 0;
	while (i < count)
	{
		envp_copy[i] = ft_strdup(envp[i]);
		if (envp_copy[i] == NULL)
			exit_on_error("Error :", 1);
		i++;
	}
	envp_copy[count] = NULL;
	return (envp_copy);
}
