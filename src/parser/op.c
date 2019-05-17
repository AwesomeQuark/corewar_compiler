/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2019/05/17 11:42:12 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_op    g_op_tab[17] =
{
	{LIVE, 1, {T_DIR}, 1},
	{LD, 2, {T_DIR | T_IND, T_REG}, 2},
	{ST, 2, {T_REG, T_IND | T_REG}, 3},
	{ADD, 3, {T_REG, T_REG, T_REG}, 4},
	{SUB, 3, {T_REG, T_REG, T_REG}, 5},
	{AND, 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6},
	{OR, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7},
	{XOR, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8},
	{ZJMP, 1, {T_DIR}, 9},
	{LDI, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10},
	{STI, 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11},
	{FORK, 1, {T_DIR}, 12},
	{LLD, 2, {T_DIR | T_IND, T_REG}, 13},
	{LLDI, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14},
	{LFORK, 1, {T_DIR}, 15},
	{AFF, 1, {T_REG}, 16},
	{0, 0, {0}, 0}
};
