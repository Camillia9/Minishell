/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:38:26 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 15:33:49 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//

// void	free_all(t_data *data, char *err, int ext)
//{
//	if (data->cmd)
//		free_cmd(&data->cmd);
//	if (data->token)
//		free_token(&data->token);
//	if (data->env)
//		free_list(&data->env);
//	if (data->pip[0] && data->pip[0] != -1)
//		close(data->pip[0]);
//	if (data->pip[1] && data->pip[1] != -1)
//		close(data->pip[1]);
//	if (err)
//		print_error(err);
//	rl_clear_history();
//	if (!access(".heredoc.tmp", F_OK))
//		unlink(".heredoc.tmp");
//	if (ext != -1)
//		exit(ext);
// }
