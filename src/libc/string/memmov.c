/*!The Treasure Box Library
 * 
 * TBox is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 * 
 * TBox is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with TBox; 
 * If not, see <a href="http://www.gnu.org/licenses/"> http://www.gnu.org/licenses/</a>
 * 
 * Copyright (C) 2009 - 2012, ruki All rights reserved.
 *
 * @author		ruki
 * @file		memmov.c
 * @ingroup 	libc
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

#ifndef TB_CONFIG_LIBC_HAVE_MEMMOV
# 	if defined(TB_CONFIG_ARCH_x86)
# 		include "opt/x86/memmov.c"
# 	elif defined(TB_CONFIG_ARCH_ARM)
# 		include "opt/arm/memmov.c"
# 	elif defined(TB_CONFIG_ARCH_SH4)
# 		include "opt/sh4/memmov.c"
# 	endif
#else
# 	include <string.h>
#endif

/* ///////////////////////////////////////////////////////////////////////
 * implementation 
 */

#if defined(TB_CONFIG_LIBC_HAVE_MEMMOV)
tb_pointer_t tb_memmov(tb_pointer_t s1, tb_cpointer_t s2, tb_size_t n)
{
	tb_assert_and_check_return_val(s1 && s2, TB_NULL);
	return memmove(s1, s2, n);
}
#elif !defined(TB_LIBC_STRING_OPT_MEMMOV)
tb_pointer_t tb_memmov(tb_pointer_t s1, tb_cpointer_t s2, tb_size_t n)
{
	tb_assert_and_check_return_val(s1 && s2, TB_NULL);

	__tb_register__ tb_byte_t* 			s = s1;
	__tb_register__ tb_byte_t const* 	p = s2;

	if (p >= s) 
	{
		while (n) 
		{
			*s++ = *p++;
			--n;
		}
	} 
	else 
	{
		while (n) 
		{
			--n;
			s[n] = p[n];
		}
	}

	return s1;
}
#endif
