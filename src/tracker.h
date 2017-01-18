/*
 * GNUitar
 * Tracker module - write samples to file
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
 * $Id: tracker.h,v 1.6 2004/08/10 15:21:16 fonin Exp $
 */

#ifndef _TRACKER_H_
#define _TRACKER_H_ 1

#include "pump.h"

extern void     tracker_out(const char *outfile);
// extern void tracker_in(const char *infile);
extern void     tracker_done();
// extern void track_read(int *s, int count);
extern void     track_write(DSP_SAMPLE *s, int count);

#endif
