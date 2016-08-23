/*
  This file is part of libmicrohttpd
  Copyright (C) 2014-2016 Karlson2k (Evgeny Grin)

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

*/

/**
 * @file microhttpd/mhd_compat.h
 * @brief  Header for platform missing functions.
 * @author Karlson2k (Evgeny Grin)
 *
 * Provides compatibility for platforms with some missing
 * functionality.
 * Any functions can be implemented as macro on some platforms
 * unless explicitly marked otherwise.
 * Any function argument can be skipped in macro, so avoid
 * variable modification in function parameters.
 */

#ifndef MHD_COMPAT_H
#define MHD_COMPAT_H 1

#include "mhd_options.h"

/* Platform-independent snprintf name */
#if defined(HAVE_SNPRINTF)
#define MHD_snprintf_ snprintf
#else  /* ! HAVE_SNPRINTF */
#if defined(_WIN32)
/* Emulate snprintf function on W32 */
int W32_snprintf(char *__restrict s, size_t n, const char *__restrict format, ...);
#define MHD_snprintf_ W32_snprintf
#else  /* ! _WIN32*/
#error Your platform does not support snprintf() and MHD does not know how to emulate it on your platform.
#endif /* ! _WIN32*/
#endif /* ! HAVE_SNPRINTF */

#if !defined(_WIN32) || defined(__CYGWIN__)
#define MHD_random_() random()
#else  /* _WIN32 && !__CYGWIN__ */
#define MHD_random_() MHD_W32_random_()

/**
 * Generate 31-bit pseudo random number.
 * Function initialize itself at first call to current time.
 * @return 31-bit pseudo random number.
 */
int MHD_W32_random_(void);
#endif /* _WIN32 && !__CYGWIN__ */



#endif /* MHD_COMPAT_H */