/*
 * GNUitar
 * Echo effect
 * Copyright (C) 2000,2001,2003 Max Rudensky         <fonin@ziet.zhitomir.ua>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * $Id: echo.h,v 1.6 2004/08/10 15:07:31 fonin Exp $
 */

#ifndef _ECHO_H_
#define _ECHO_H_ 1

#include "pump.h"

#define MAX_ECHO_COUNT 20
#define MAX_ECHO_SIZE 1000

extern void     echo_create(struct effect *);

struct echo_params {
    int             echo_size,
                    echo_decay,
                    buffer_count;	/* number of buffers */
    DSP_SAMPLE    **history;	/* array[MAX_ECHO_COUNT] of history */
    int            *size,	/* size of one buffer */
                   *factor,
                   *index;	/* array[MAX_ECHO_COUNT] of history index */
};

#endif
