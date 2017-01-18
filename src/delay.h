/*
 * GNUitar
 * Delay effect: definitions
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
 * $Id: delay.h,v 1.6 2004/08/10 15:07:31 fonin Exp $
 */

#ifndef _DELAY_H_
#define _DELAY_H_ 1

#include "pump.h"

#define MAX_STEP 65000
#define MAX_COUNT 10
#define MAX_SIZE (MAX_STEP*MAX_COUNT)

extern void     delay_create(struct effect *);

struct delay_params {
    DSP_SAMPLE     *history;	/* history of samples */

    int             index;	/* curr.index in the history array */
    int             delay_size,	/* length of history */
                    delay_decay,	/* volume of processed signal */
                    delay_start,
                    delay_step,
                   *idelay,
                    delay_count;	/* number of repeats */
};

#endif
