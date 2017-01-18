/*
 * GNUitar
 * Vibrato effect
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
 * $Id: vibrato.h,v 1.8 2004/08/10 15:21:16 fonin Exp $
 */

#ifndef _VIBRATO_H_
#define _VIBRATO_H_ 1

#include "pump.h"

#define MAX_VIBRATO_BUFSIZE MAX_SAMPLE_RATE*MAX_CHANNELS
#define VIBRATO_THRESHOLD 1500

extern void     vibrato_create(struct effect *);

struct vibrato_params {
    float           vibrato_amplitude;
    int             vibrato_speed,
                    vibrato_phase_buffer_size,
                    vibrato_phase;
    DSP_SAMPLE     *phase_buffer;
};

#endif
