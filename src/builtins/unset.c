/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:44:46 by tiaferna          #+#    #+#             */
/*   Updated: 2024/03/31 18:41:29 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_env_node(t_env *env_node, t_mshell *init)
{
	if (init)
		init->env_table = init->env_table->next;
	env_node->visibility = 0;
	free(env_node->var);
	free(env_node->content);
	free(env_node);
}

void	unset_if_present(t_mshell *init, t_env	*env_node, int *i)
{
	t_env	*temp;

	if (ft_strcmp(env_node->var, init->parser->cmd_exec[*i]) == 0)
		free_env_node(env_node, init);
	else
	{
		while (env_node->next)
		{
			if (ft_strcmp(env_node->next->var, init->parser->cmd_exec[*i]) == 0)
			{
				temp = env_node->next;
				env_node->next = env_node->next->next;
				free_env_node(temp, NULL);
				break ;
			}
			env_node = env_node->next;
		}
	}
	(*i)++;
}

void	unset(t_mshell *init, char ***envp_copy)
{
	t_env	*env_node;
	int		i;

	if (!init->parser->cmd_exec[1] || \
	(init->parser->cmd_exec[1] && init->parser->cmd_exec[1][0] == '-'))
		return ;
	i = 1;
	while (init->parser->cmd_exec[i])
	{
		env_node = init->env_table;
		unset_if_present(init, env_node, &i);
	}
	*envp_copy = update_envp_copy(init, envp_copy, 0, NULL);
}
