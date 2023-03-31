#ifndef SRC_SIMPLE_GRAPHER_GRAPHER_H_
#define SRC_SIMPLE_GRAPHER_GRAPHER_H_

/************
 * INCLUDES *
 ************/
#include <gtk/gtk.h>

/***********
 * DEFINES *
 ***********/
#ifndef PI
#define PI 3.141592653589793238
#endif /* PI */

#ifndef NAN
#define NAN 0.0 / 0.0
#endif /* NAN */

#ifndef INF
#define INF 1.0 / 0.0
#endif /* INF */

/************************
 * FUNCTION DECLARATION *
 ************************/
void linspace(double *, double, double, unsigned);
void plotter_init();
void plotter_set_function(double *, double *, unsigned);
void plotter_set_range(double, double);
void plotter_set_domain(double, double);
void plotter_signal_connect_on_close(void (*on_close)(GtkWidget *, gpointer),
                                     gpointer);
void plotter_draw();
gboolean on_draw_call(GtkWidget *, cairo_t *, gpointer);

#endif /* SRC_SIMPLE_GRAPHER_GRAPHER_H_ */
