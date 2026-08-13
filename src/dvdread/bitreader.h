/*
 * Copyright (C) 2000, 2001, 2002 Håkan Hjort <d95hjort@dtek.chalmers.se>.
 *
 * This file is part of libdvdread.
 *
 * libdvdread is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * libdvdread is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with libdvdread; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef LIBDVDREAD_BITREADER_H
#define LIBDVDREAD_BITREADER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <dvdread/attributes.h>

typedef struct {
  const uint8_t *start;
  uint32_t byte_position;
  uint32_t bit_position;
} getbits_state_t;

DVDREAD_API int dvdread_getbits_init(getbits_state_t *state, const uint8_t *start);
DVDREAD_API uint32_t dvdread_getbits(getbits_state_t *state, uint32_t number_of_bits);

#if defined(__GNUC__) && !defined(__COVERITY__)

__attribute__((error("dvdread_getbits requesting too many bits")))
uint32_t dvdread_getbits_toomany( getbits_state_t *, size_t );

// check the constant values are not bigger than 32 bits
# define dvdread_getbits(s,b) \
  ((__builtin_constant_p(b) && b <= 32 && b > 0) ? (dvdread_getbits)(s,b) : dvdread_getbits_toomany(s, b))

#endif

#ifdef __cplusplus
};
#endif
#endif /* LIBDVDREAD_BITREADER_H */
