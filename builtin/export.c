/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:03:04 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/06 20:52:57 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export(char **envp)
{
	int			i;
	int			j;
	int			has_assign;

	i = -1;
	while (envp[++i])
	{
		has_assign = 0;
		j = 0;
		while (envp[i][j])
		{
			if (envp[i][j] == '\"')
				write(STDOUT_FILENO, "\\", 1);
			write(STDOUT_FILENO, &envp[i][j], 1);
			if (envp[i][j] == '=')
			{
				has_assign = 1;
				write(STDOUT_FILENO, "\"", 1);
			}
			j++;
		}
		if (has_assign)
			write(STDOUT_FILENO, "\"", 1);
		write(STDOUT_FILENO, "\n", 1);
	}
}

static void	sort_print_env(t_dict *env_dict)
{
	char	**envp;
	char	*tmp;
	int		i;
	int		j;

	envp = generate_envp(env_dict);
	i = 0;
	while (envp[i])
	{
		j = i + 1;
		while (envp[j])
		{
			if (ft_strcmp(envp[i], envp[j]) > 0)
			{
				tmp = envp[i];
				envp[i] = envp[j];
				envp[j] = tmp;
			}
			j++;
		}
		i++;
	}
	print_export(envp);
	free_double_ptr(envp);
}

static int	is_valid_id(char *s)
{
	int	i;
	int	after_assign;

	i = 0;
	after_assign = 0;
	while (s[i])
	{
		if (i == 0)
		{
			if (!(ft_isalpha(s[i]) || s[i] == '_'))
				return (0);
		}
		else
		{
			if (s[i] == '=')
				after_assign = 1;
			if (!after_assign)
			{
				if (!(ft_isalpha(s[i]) || s[i] == '_' || ft_isdigit(s[i])))
					return (0);
			}
		}
		i++;
	}
	return (1);
}

static int	invalid_id_err(char	*str)
{
	const char	*err_str = ": not a valid identifier\n";

	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, "export: ", 8);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, err_str, ft_strlen(err_str));
	return (1);
}

int	ft_export(char **argv, t_dict **env_dict)
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
			add_node_back(env_dict, argv[idx]);
		else
			result = invalid_id_err(argv[idx]);
		idx++;
	}
	if (argc == 1)
		sort_print_env(*env_dict);
	return (result);
}
