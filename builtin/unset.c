/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:19:12 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/06 20:53:04 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_id(char *str)
{
	int	idx;
	int	after_assign;

	idx = 0;
	after_assign = 0;
	while (str[idx])
	{
		if (idx == 0)
		{
			if (!(ft_isalpha(str[idx]) || str[idx] == '_'))
				return (0);
		}
		else
		{
			if (!(ft_isalpha(str[idx]) || \
				str[idx] == '_' || ft_isdigit(str[idx])))
				return (0);
		}
		idx++;
	}
	return (1);
}

static int	invalid_id_err(char	*str)
{
	const char	*err_str = ": not a valid identifier\n";

	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, "unset: ", 7);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, err_str, ft_strlen(err_str));
	return (1);
}

int	ft_unset(char **argv, t_dict **env_dict)
{
	int	argc;
	int	idx;
	int	result;

	argc = 0;
	while (argv && argv[argc])
		argc++;
	idx = 1;
	result = 0;
	while (idx < argc)
	{
		if (is_valid_id(argv[idx]))
			del_node_with_key(env_dict, argv[idx]);
		else
			result = invalid_id_err(argv[idx]);
		idx++;
	}
	return (0);
}
