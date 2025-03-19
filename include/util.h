/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 05:32:33 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/19 14:36:38 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

typedef unsigned char		t_u8;
typedef unsigned short		t_u16;
typedef unsigned int		t_u32;
typedef unsigned long long	t_u64;

typedef char				t_i8;
typedef short				t_i16;
typedef int					t_i32;
typedef long long			t_i64;

typedef float				t_f32;
typedef double				t_f64;

typedef enum e_result
{
	SUCCESS,
	FAIL
}	t_result;
# define RESULT t_result __attribute__((warn_unused_result))

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;
# define BOOL t_bool //__attribute__((warn_unused_result))

t_i32		print_f(const char *s, ...);

void		print_error(const char *cstring);
t_result	fail(const char *cstring);

RESULT		i32_from_cstring(t_i32 *value, const char *cstring);

t_u64		uabs(t_i64 value);

#endif
