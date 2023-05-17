/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:57:27 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/05/17 13:57:56 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
# define SIG_H

# include "../minishell.h"

# define DEFAULT 0
# define SIG_HERE 1
# define PARENT 2
# define CHILD 3

void	set_signals(int state);

#endif
