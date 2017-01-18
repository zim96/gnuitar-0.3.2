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
 * $Id: vibrato.c,v 1.13 2005/04/29 11:24:42 fonin Exp $
 *
 * $Log: vibrato.c,v $
 * Revision 1.13  2005/04/29 11:24:42  fonin
 * Better presets
 *
 * Revision 1.12  2004/08/10 15:21:16  fonin
 * Support processing in float/int - type DSP_SAMPLE
 *
 * Revision 1.10  2004/07/07 19:18:42  fonin
 * GTK2 port
 *
 * Revision 1.9  2003/03/09 20:53:16  fonin
 * Meaningful params "speed" and "amplitude". Structures were redesigned
 * for new feature of on-the-fly change of sampling params.
 *
 * Revision 1.8  2003/02/03 11:39:25  fonin
 * Copyright year changed.
 *
 * Revision 1.6  2003/02/01 19:13:44  fonin
 * Changed the units of slider bars from computer ones to ms and %
 *
 * Revision 1.5  2003/01/30 21:35:29  fonin
 * Got rid of rnd_window_pos().
 *
 * Revision 1.4  2003/01/29 19:34:00  fonin
 * Win32 port.
 *
 * Revision 1.3  2001/06/02 14:05:59  fonin
 * Added GNU disclaimer.
 *
 * Revision 1.2  2001/03/25 12:10:50  fonin
 * Effect window control ignores delete event.
 *
 * Revision 1.1.1.1  2001/01/11 13:22:31  fonin
 * Version 0.1.0 Release 1 beta
 *
 */

#include "vibrato.h"
#include <math.h>
#include <stdlib.h>
#ifndef _WIN32
#    include <unistd.h>
#else
#    include <io.h>
#    include "utils.h"
#endif
#include "gui.h"

void
                vibrato_filter(struct effect *p, struct data_block *db);

void
update_vibrato_speed(GtkAdjustment * adj, struct vibrato_params *params)
{
    params->vibrato_speed =
	(int) ((float) sample_rate * nchannels * adj->value / 1000.0);
}

void
update_vibrato_ampl(GtkAdjustment * adj, struct vibrato_params *params)
{
    params->vibrato_amplitude = adj->value * 50.0 / MAX_SAMPLE;
}

void
toggle_vibrato(void *bullshit, struct effect *p)
{
    if (p->toggle == 1) {
	p->proc_filter = passthru;
	p->toggle = 0;
    } else {
	p->proc_filter = vibrato_filter;
	p->toggle = 1;
    }
}

void
vibrato_init(struct effect *p)
{
    struct vibrato_params *pvibrato;

    GtkWidget      *speed;
    GtkWidget      *speed_label;
    GtkObject      *adj_speed;

    GtkWidget      *ampl;
    GtkWidget      *ampl_label;
    GtkObject      *adj_ampl;

    GtkWidget      *button;
    GtkWidget      *parmTable;

    pvibrato = (struct vibrato_params *) p->params;

    /*
     * GUI Init
     */
#ifdef HAVE_GTK
    p->control = gtk_window_new(GTK_WINDOW_DIALOG);
#elif defined HAVE_GTK2
    p->control = gtk_window_new(GTK_WINDOW_TOPLEVEL);
#endif

    gtk_signal_connect(GTK_OBJECT(p->control), "delete_event",
		       GTK_SIGNAL_FUNC(delete_event), NULL);

    parmTable = gtk_table_new(2, 8, FALSE);

    adj_speed =
	gtk_adjustment_new(pvibrato->vibrato_speed * 1000.0 /
			   (sample_rate * nchannels), 1.0,
			   (MAX_VIBRATO_BUFSIZE * 1000.0 /
			    (sample_rate * nchannels)), 1.0, 1.0, 1.0);
    speed_label = gtk_label_new("Speed\n1/ms");
    gtk_table_attach(GTK_TABLE(parmTable), speed_label, 0, 1, 0, 1,
		     __GTKATTACHOPTIONS(GTK_FILL | GTK_EXPAND |
					GTK_SHRINK),
		     __GTKATTACHOPTIONS(GTK_FILL | GTK_EXPAND |
					GTK_SHRINK), 0, 0);

    gtk_signal_connect(GTK_OBJECT(adj_speed), "value_changed",
		       GTK_SIGNAL_FUNC(update_vibrato_speed), pvibrato);

    speed = gtk_vscale_new(GTK_ADJUSTMENT(adj_speed));
#ifdef HAVE_GTK2
    gtk_widget_set_size_request(GTK_WIDGET(speed),0,100);
#endif

    gtk_table_attach(GTK_TABLE(parmTable), speed, 0, 1, 1, 2,
		     __GTKATTACHOPTIONS
		     (GTK_FILL | GTK_EXPAND | GTK_SHRINK),
		     __GTKATTACHOPTIONS
		     (GTK_FILL | GTK_EXPAND | GTK_SHRINK), 0, 0);

    adj_ampl =
	gtk_adjustment_new(pvibrato->vibrato_amplitude * MAX_SAMPLE / 50,
			   0.0, 100.0, 1.0, 1.0, 1.0);
    ampl_label = gtk_label_new("Amplitude\n%");
    gtk_table_attach(GTK_TABLE(parmTable), ampl_label, 3, 4, 0, 1,
		     __GTKATTACHOPTIONS(GTK_FILL | GTK_EXPAND |
					GTK_SHRINK),
		     __GTKATTACHOPTIONS(GTK_FILL | GTK_EXPAND |
					GTK_SHRINK), 0, 0);


    gtk_signal_connect(GTK_OBJECT(adj_ampl), "value_changed",
		       GTK_SIGNAL_FUNC(update_vibrato_ampl), pvibrato);

    ampl = gtk_vscale_new(GTK_ADJUSTMENT(adj_ampl));

    gtk_table_attach(GTK_TABLE(parmTable), ampl, 3, 4, 1, 2,
		     __GTKATTACHOPTIONS
		     (GTK_FILL | GTK_EXPAND | GTK_SHRINK),
		     __GTKATTACHOPTIONS
		     (GTK_FILL | GTK_EXPAND | GTK_SHRINK), 0, 0);

    button = gtk_check_button_new_with_label("On");
    gtk_signal_connect(GTK_OBJECT(button), "toggled",
		       GTK_SIGNAL_FUNC(toggle_vibrato), p);

    gtk_table_attach(GTK_TABLE(parmTable), button, 3, 4, 2, 3,
		     __GTKATTACHOPTIONS
		     (GTK_FILL | GTK_EXPAND | GTK_SHRINK),
		     __GTKATTACHOPTIONS
		     (GTK_FILL | GTK_EXPAND | GTK_SHRINK), 0, 0);
    if (p->toggle == 1) {
	p->toggle = 0;
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button), TRUE);
    }

    gtk_window_set_title(GTK_WINDOW(p->control), (gchar *) ("Vibrato"));
    gtk_container_add(GTK_CONTAINER(p->control), parmTable);

    gtk_widget_show_all(p->control);

}

void
vibrato_filter(struct effect *p, struct data_block *db)
{
    DSP_SAMPLE     *s,
                    ratio;
    int             count;
    struct vibrato_params *vp;

    s = db->data;
    count = db->len;

    vp = p->params;

    while (count) {
	ratio =
	    VIBRATO_THRESHOLD +
	    vp->phase_buffer[vp->vibrato_phase] * vp->vibrato_amplitude;
	*s = *s * ratio / VIBRATO_THRESHOLD;

	vp->vibrato_phase++;

	if (vp->vibrato_phase >= vp->vibrato_speed ||
	    vp->vibrato_phase > MAX_VIBRATO_BUFSIZE)
	    vp->vibrato_phase = 0;

	s++;
	count--;
    }
}

void
vibrato_done(struct effect *p)
{
    struct vibrato_params *vp;

    vp = p->params;

    free(vp->phase_buffer);
    free(vp);
    gtk_widget_destroy(p->control);
    free(p);
    p = NULL;

}

void
vibrato_save(struct effect *p, int fd)
{
    struct vibrato_params *vp;

    vp = (struct vibrato_params *) p->params;

    write(fd, &vp->vibrato_speed, sizeof(int));
    write(fd, &vp->vibrato_amplitude, sizeof(int));
}

void
vibrato_load(struct effect *p, int fd)
{
    int             i;
    struct vibrato_params *vp;

    vp = (struct vibrato_params *) p->params;

    read(fd, &vp->vibrato_speed, sizeof(int));
    read(fd, &vp->vibrato_amplitude, sizeof(int));
    for (i = 0; i < vp->vibrato_phase_buffer_size; i++) {
	vp->phase_buffer[i] = ((double) vp->vibrato_amplitude *
				     sin(2 * M_PI * ((double) i / (double)
						     vp->
						     vibrato_phase_buffer_size)));
    }

    if (p->toggle == 0) {
	p->proc_filter = passthru;
    } else {
	p->proc_filter = vibrato_filter;
    }
}

void
vibrato_create(struct effect *p)
{
    int             i;
    struct vibrato_params *pvibrato;

    p->params =
	(struct vibrato_params *) malloc(sizeof(struct vibrato_params));
    p->proc_init = vibrato_init;
    p->proc_filter = passthru;
    p->toggle = 0;
    p->proc_done = vibrato_done;
    p->id = VIBRATO;
    p->proc_load = vibrato_load;
    p->proc_save = vibrato_save;

    pvibrato = (struct vibrato_params *) p->params;

    pvibrato->vibrato_amplitude = 5000.0 / MAX_SAMPLE;
    pvibrato->vibrato_speed = MAX_VIBRATO_BUFSIZE * 0.2 / nchannels;
    pvibrato->vibrato_phase_buffer_size = MAX_VIBRATO_BUFSIZE;

    pvibrato->phase_buffer =
	(DSP_SAMPLE *) malloc(MAX_VIBRATO_BUFSIZE * sizeof(DSP_SAMPLE));
    pvibrato->vibrato_phase = 0;

    for (i = 0; i < pvibrato->vibrato_phase_buffer_size; i++) {
	pvibrato->phase_buffer[i] = (MAX_SAMPLE *
					   sin(2 * M_PI * ((double)
							   i / (double)
							   pvibrato->
							   vibrato_phase_buffer_size)));
    }
}
