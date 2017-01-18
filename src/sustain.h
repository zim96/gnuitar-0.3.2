/*
 * GNUitar
 * Sustain effect
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
 * $Id: sustain.h,v 1.4 2003/02/03 11:39:25 fonin Exp $
 */

#ifndef _SUSTAIN_H_
#define _SUSTAIN_H_ 1

#include "pump.h"

extern void     sustain_create(struct effect *);

struct sustain_params {
    int             sust,
                    noise,
                    threshold,
                    volaccum;
};

#endif
