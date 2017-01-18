/*
 * GNUitar
 * Phasor effect
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
 * $Id: phasor.h,v 1.6 2003/03/13 20:24:30 fonin Exp $
 */

#ifndef _PHASOR_H_
#define _PHASOR_H_ 1

#include "pump.h"
#include "rcfilter.h"

extern void     phasor_create(struct effect *);

struct phasor_params {
    float           freq_low;
    float           freq_high;
    float           f,
                    df;
    short           bandpass;
    struct filter_data fd;
};

#endif
