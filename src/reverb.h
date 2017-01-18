/*
 * GNUitar
 * Reverberation effect
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
 * $Id: reverb.h,v 1.5 2004/08/10 15:07:31 fonin Exp $
 */

#ifndef _REVERB_H_
#define _REVERB_H_ 1

#include "pump.h"

extern void     reverb_create(struct effect *);

struct reverbBuffer {
    DSP_SAMPLE     *data;
    int             nChunks;
    int             nCursor;
};

struct reverb_params {
    struct reverbBuffer *history;
    int             dry,
                    wet,
                    regen,
                    delay;
};

#endif
