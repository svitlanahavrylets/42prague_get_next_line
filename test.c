/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shavryle <shavryle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:25:36 by shavryle          #+#    #+#             */
/*   Updated: 2025/12/02 10:30:04 by shavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void counter() 
{
    static int i = 0;  // не скидається!
    i++;
    printf("i = %d\n", i);
}

void counter2() 
{
    int i = 0;  // скидається!
    i++;
    printf("i = %d\n", i);
}

int main()
{
    counter();  // i = 1
    counter();  // i = 2
    counter();  // i = 3
	counter2();  // i = 1
    counter2();  // i = 2
    counter2();  // i = 3
}
