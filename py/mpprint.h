/*
 * This file is part of the Micro Python project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2013, 2014 Damien P. George
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef __MICROPY_INCLUDED_PY_MPPRINT_H__
#define __MICROPY_INCLUDED_PY_MPPRINT_H__

#include "py/mpconfig.h"

#define PF_FLAG_LEFT_ADJUST       (0x001)
#define PF_FLAG_SHOW_SIGN         (0x002)
#define PF_FLAG_SPACE_SIGN        (0x004)
#define PF_FLAG_NO_TRAILZ         (0x008)
#define PF_FLAG_SHOW_PREFIX       (0x010)
#define PF_FLAG_SHOW_COMMA        (0x020)
#define PF_FLAG_PAD_AFTER_SIGN    (0x040)
#define PF_FLAG_CENTER_ADJUST     (0x080)
#define PF_FLAG_ADD_PERCENT       (0x100)
#define PF_FLAG_PAD_NAN_INF       (0x200)
#define PF_FLAG_SHOW_OCTAL_LETTER (0x400)

typedef void (*mp_print_strn_t)(void *data, const char *str, mp_uint_t len);

typedef struct _mp_print_t {
    void *data;
    mp_print_strn_t print_strn;
} mp_print_t;

// Wrapper for platform print function, which wraps MP_PLAT_PRINT_STRN.
// All (non-debug) prints go through this interface (except some which
// go through mp_sys_stdout_obj if MICROPY_PY_IO is defined).
extern const mp_print_t mp_plat_print;

int mp_print_str(const mp_print_t *print, const char *str);
int mp_print_strn(const mp_print_t *print, const char *str, mp_uint_t len, int flags, char fill, int width);
int mp_print_int(const mp_print_t *print, mp_uint_t x, int sgn, int base, int base_char, int flags, char fill, int width);
#if MICROPY_PY_BUILTINS_FLOAT
int mp_print_float(const mp_print_t *print, mp_float_t f, char fmt, int flags, char fill, int width, int prec);
#endif

int mp_printf(const mp_print_t *print, const char *fmt, ...);
#ifdef va_start
int mp_vprintf(const mp_print_t *print, const char *fmt, va_list args);
#endif

#endif // __MICROPY_INCLUDED_PY_MPPRINT_H__