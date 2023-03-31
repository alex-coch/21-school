#include <gtk/gtk.h>

#include "simple_grapher/grapher.h"

double *x, *y;
int count_of_dots = 500000;

int main(int argc, char *argv[]) {
  GtkBuilder *builder;
  GtkWindow *window;

  x = calloc(sizeof(double), count_of_dots);
  y = calloc(sizeof(double), count_of_dots);

  gtk_init(&argc, &argv);
  plotter_init();

  builder = gtk_builder_new_from_file("./UI/ui.glade");
  window = GTK_WINDOW(gtk_builder_get_object(builder, "gtk_window"));

  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_builder_connect_signals(builder, NULL);

  gtk_widget_show_all(GTK_WIDGET(window));
  gtk_main();

  free(x);
  free(y);
  return 0;
}
