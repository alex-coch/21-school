#include <gtk/gtk.h>
#include <locale.h>

#include "calc.h"
#include "pars.h"
#include "simple_grapher/grapher.h"

/** @brief Recursively searches for the widget by name.
 *
 * From
 * https://stackoverflow.com/questions/5401327/finding-children-of-a-gtkwidget
 *
 *  @param parent a widget.
 *  @param name a desired name.
 *
 *  @return an outcome of evaluation.
 */
static inline GtkWidget* find_child(GtkWidget* parent, const gchar* name) {
  if (strcmp(gtk_widget_get_name(parent), name) == 0) return parent;

  GList* children = NULL;
  if (GTK_IS_CONTAINER(parent))
    children = gtk_container_get_children(GTK_CONTAINER(parent));

  while (children != NULL) {
    GtkWidget* widget = find_child(GTK_WIDGET(children->data), name);

    if (widget != NULL) return widget;

    children = children->next;
  }

  return NULL;
}

/** @brief Substites a delimiter regarding a current locale.
 *
 *  @param string a string where delimeters are swaped.
 *
 *  @return void.
 */
void to_locale_decimal_point(char* string) {
  char cur_delim = ',';
  char new_delim = '.';
  if (*localeconv()->decimal_point == ',') {
    cur_delim = '.';
    new_delim = ',';
  }
  for (size_t i = 0; i < strlen(string); ++i) {
    if (string[i] == cur_delim) {
      string[i] = new_delim;
    }
  }
}

/** @brief Calculates an expression.
 *
 *  @param button a pointer to a pressed button.
 *  @param gtk_window a pointer to a Gtk window.
 *
 *  @return void.
 */
void oncalculate(GtkButton* button, gpointer gtk_window) {
  GtkEntry* entry = GTK_ENTRY(find_child(gtk_window, "entry_exp"));
  gchar input[256];
  // g_print("%s\n", gtk_entry_get_text(entry));
  g_snprintf(input, sizeof(input), "%s", gtk_entry_get_text(entry));
  que* qu;
  GtkEntry* entry_x = GTK_ENTRY(find_child(gtk_window, "entry_x"));
  gchar input_x[101];
  g_snprintf(input_x, sizeof(input), "%s", gtk_entry_get_text(entry_x));
  double input_x_d = strtod(input_x, NULL);
  if (str_to_polish(input, &qu)) {
    double result = calculate(qu, input_x_d);
    gchar expression[256];
    g_snprintf(expression, sizeof(expression), "%.9f", result);
    gtk_entry_buffer_set_text(gtk_entry_get_buffer(entry), expression,
                              strlen(expression));
    // g_print("%.9f\n", result);
    gtk_editable_set_position(
        GTK_EDITABLE(entry),
        gtk_editable_get_position(GTK_EDITABLE(entry)) + 50);
  }
  UNUSED(button);
}

/** @brief Calls the plot widget.
 *
 *  @param widget a pointer to a Gtk widget.
 *  @param main_window a pointer to a Gtk window.
 *
 *  @return void.
 */
void on_plote_window_close(GtkWidget* widget, gpointer main_window) {
  UNUSED(widget);
  gtk_widget_set_sensitive(GTK_WIDGET(main_window), TRUE);
}

/** @brief Transfers a fucus to a main window.
 *
 *  @param windget a pointer to a widget.
 *  @param main_window a pointer to main Gtk window.
 *
 *  @return void.
 */
void on_plotter_window_close(GtkWidget* widget, gpointer main_window) {
  UNUSED(widget);
  gtk_widget_set_sensitive(GTK_WIDGET(main_window), TRUE);
  gtk_widget_show(main_window);
}

/** @brief Shows a window with a plot.
 *
 *  @param button a pointer to a pressed button.
 *  @param gtk_window a pointer to a Gtk window.
 *
 *  @return void.
 */
void onPlote(GtkButton* b, gpointer main_window) {
  UNUSED(b);
  /* builder init */
  GtkBuilder* builder;
  GtkWindow* window;

  builder = gtk_builder_new_from_file("./UI/plotter.glade");

  /* get window object from the builder */
  window = GTK_WINDOW(gtk_builder_get_object(builder, "id@gtk_window"));

  /* enable all signals from builder */
  gtk_builder_connect_signals(builder, NULL);

  /* disable main window */
  gtk_widget_set_sensitive(GTK_WIDGET(main_window), FALSE);
  g_signal_connect(G_OBJECT(window), "destroy",
                   G_CALLBACK(on_plote_window_close), main_window);

  /* show window */
  gtk_widget_show_all(GTK_WIDGET(window));
}

/** @brief Shows a loans window.
 *
 *  @param button a pointer to a pressed button.
 *  @param gtk_window a pointer to a Gtk window.
 *
 *  @return void.
 */
void onLoan(GtkButton* b, gpointer main_window) {
  UNUSED(b);
  /* builder init */
  GtkBuilder* builder;
  GtkWindow* window;

  builder = gtk_builder_new_from_file("./UI/loans.glade");

  /* get window object from the builder */
  window = GTK_WINDOW(gtk_builder_get_object(builder, "id@gtk_window"));

  /* enable all signals from builder */
  gtk_builder_connect_signals(builder, NULL);

  /* disable main window */
  gtk_widget_set_sensitive(GTK_WIDGET(main_window), FALSE);
  g_signal_connect(G_OBJECT(window), "destroy",
                   G_CALLBACK(on_plote_window_close), main_window);

  /* show window */
  gtk_widget_show_all(GTK_WIDGET(window));
}

/** @brief Proccesses pressing on a sqrt button.
 *
 *  @param b a pointer to a pressed button.
 *  @param io_field a pointer to an input string window's element.
 *
 *  @return void.
 */
void onsqrt(GtkButton* b, gpointer io_field) {
  UNUSED(b);
  gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
  gtk_editable_insert_text(GTK_EDITABLE(io_field), "sqrt()", 6,
                           &cursor_position);
  gtk_editable_set_position(
      GTK_EDITABLE(io_field),
      gtk_editable_get_position(GTK_EDITABLE(io_field)) + 5);
}

/** @brief Proccesses pressing on a mod button.
 *
 *  @param b a pointer to a pressed button.
 *  @param io_field a pointer to an input string window's element.
 *
 *  @return void.
 */
void onmod(GtkButton* b, gpointer io_field) {
  UNUSED(b);
  gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
  gtk_editable_insert_text(GTK_EDITABLE(io_field), "mod", 3, &cursor_position);
  gtk_editable_set_position(
      GTK_EDITABLE(io_field),
      gtk_editable_get_position(GTK_EDITABLE(io_field)) + 3);
}

/** @brief Proccesses pressing on a log button.
 *
 *  @param b a pointer to a pressed button.
 *  @param io_field a pointer to an input string window's element.
 *
 *  @return void.
 */
void onlog(GtkButton* b, gpointer io_field) {
  UNUSED(b);
  gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
  gtk_editable_insert_text(GTK_EDITABLE(io_field), "log()", 5,
                           &cursor_position);
  gtk_editable_set_position(
      GTK_EDITABLE(io_field),
      gtk_editable_get_position(GTK_EDITABLE(io_field)) + 4);
}

/** @brief Proccesses pressing on a ln button.
 *
 *  @param b a pointer to a pressed button.
 *  @param io_field a pointer to an input string window's element.
 *
 *  @return void.
 */
void onln(GtkButton* b, gpointer io_field) {
  UNUSED(b);
  gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
  gtk_editable_insert_text(GTK_EDITABLE(io_field), "ln()", 4, &cursor_position);
  gtk_editable_set_position(
      GTK_EDITABLE(io_field),
      gtk_editable_get_position(GTK_EDITABLE(io_field)) + 3);
}

/** @brief Proccesses pressing on a pow button.
 *
 *  @param b a pointer to a pressed button.
 *  @param io_field a pointer to an input string window's element.
 *
 *  @return void.
 */
void onpow(GtkButton* b, gpointer io_field) {
  UNUSED(b);
  gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
  gtk_editable_insert_text(GTK_EDITABLE(io_field), "^", 1, &cursor_position);
  gtk_editable_set_position(
      GTK_EDITABLE(io_field),
      gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

/** @brief Proccesses pressing on a tan button.
 *
 *  @param b a pointer to a pressed button.
 *  @param io_field a pointer to an input string window's element.
 *
 *  @return void.
 */
void ontan(GtkButton* b, gpointer io_field) {
  UNUSED(b);
  gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
  gtk_editable_insert_text(GTK_EDITABLE(io_field), "tan()", 5,
                           &cursor_position);
  gtk_editable_set_position(
      GTK_EDITABLE(io_field),
      gtk_editable_get_position(GTK_EDITABLE(io_field)) + 4);
}

/** @brief Proccesses pressing on an atan button.
 *
 *  @param b a pointer to a pressed button.
 *  @param io_field a pointer to an input string window's element.
 *
 *  @return void.
 */
void onatan(GtkButton* b, gpointer io_field) {
  UNUSED(b);
  gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
  gtk_editable_insert_text(GTK_EDITABLE(io_field), "atan()", 6,
                           &cursor_position);
  gtk_editable_set_position(
      GTK_EDITABLE(io_field),
      gtk_editable_get_position(GTK_EDITABLE(io_field)) + 5);
}

/** @brief Proccesses pressing on a sin button.
 *
 *  @param b a pointer to a pressed button.
 *  @param io_field a pointer to an input string window's element.
 *
 *  @return void.
 */
void onsin(GtkButton* b, gpointer io_field) {
  UNUSED(b);
  gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
  gtk_editable_insert_text(GTK_EDITABLE(io_field), "sin()", 5,
                           &cursor_position);
  gtk_editable_set_position(
      GTK_EDITABLE(io_field),
      gtk_editable_get_position(GTK_EDITABLE(io_field)) + 4);
}

/** @brief Proccesses pressing on an asin button.
 *
 *  @param b a pointer to a pressed button.
 *  @param io_field a pointer to an input string window's element.
 *
 *  @return void.
 */
void onasin(GtkButton* b, gpointer io_field) {
  UNUSED(b);
  gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
  gtk_editable_insert_text(GTK_EDITABLE(io_field), "asin()", 6,
                           &cursor_position);
  gtk_editable_set_position(
      GTK_EDITABLE(io_field),
      gtk_editable_get_position(GTK_EDITABLE(io_field)) + 5);
}

/** @brief Proccesses pressing on an cos button.
 *
 *  @param b a pointer to a pressed button.
 *  @param io_field a pointer to an input string window's element.
 *
 *  @return void.
 */
void oncos(GtkButton* b, gpointer io_field) {
  UNUSED(b);
  gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
  gtk_editable_insert_text(GTK_EDITABLE(io_field), "cos()", 5,
                           &cursor_position);
  gtk_editable_set_position(
      GTK_EDITABLE(io_field),
      gtk_editable_get_position(GTK_EDITABLE(io_field)) + 4);
}

/** @brief Proccesses pressing on an acos button.
 *
 *  @param b a pointer to a pressed button.
 *  @param io_field a pointer to an input string window's element.
 *
 *  @return void.
 */
void onacos(GtkButton* b, gpointer io_field) {
  UNUSED(b);
  gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
  gtk_editable_insert_text(GTK_EDITABLE(io_field), "acos()", 6,
                           &cursor_position);
  gtk_editable_set_position(
      GTK_EDITABLE(io_field),
      gtk_editable_get_position(GTK_EDITABLE(io_field)) + 5);
}

/** @brief Proccesses pressing on an '(' button.
 *
 *  @param b a pointer to a pressed button.
 *  @param io_field a pointer to an input string window's element.
 *
 *  @return void.
 */
void onopenbr(GtkButton* b, gpointer io_field) {
  UNUSED(b);
  gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
  gtk_editable_insert_text(GTK_EDITABLE(io_field), "(", 1, &cursor_position);
  gtk_editable_set_position(
      GTK_EDITABLE(io_field),
      gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

/** @brief Proccesses pressing on an ')' button.
 *
 *  @param b a pointer to a pressed button.
 *  @param io_field a pointer to an input string window's element.
 *
 *  @return void.
 */
void onclosebr(GtkButton* b, gpointer io_field) {
  UNUSED(b);
  gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
  gtk_editable_insert_text(GTK_EDITABLE(io_field), ")", 1, &cursor_position);
  gtk_editable_set_position(
      GTK_EDITABLE(io_field),
      gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

/** @brief Proccesses pressing on an '1' button.
 *
 *  @param b a pointer to a pressed button.
 *  @param io_field a pointer to an input string window's element.
 *
 *  @return void.
 */
void on1(GtkButton* b, gpointer io_field) {
  UNUSED(b);
  gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
  gtk_editable_insert_text(GTK_EDITABLE(io_field), "1", 1, &cursor_position);
  gtk_editable_set_position(
      GTK_EDITABLE(io_field),
      gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

/** @brief Proccesses pressing on an '2' button.
 *
 *  @param b a pointer to a pressed button.
 *  @param io_field a pointer to an input string window's element.
 *
 *  @return void.
 */
void on2(GtkButton* b, gpointer io_field) {
  UNUSED(b);
  gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
  gtk_editable_insert_text(GTK_EDITABLE(io_field), "2", 1, &cursor_position);
  gtk_editable_set_position(
      GTK_EDITABLE(io_field),
      gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

/** @brief Proccesses pressing on an '3' button.
 *
 *  @param b a pointer to a pressed button.
 *  @param io_field a pointer to an input string window's element.
 *
 *  @return void.
 */
void on3(GtkButton* b, gpointer io_field) {
  UNUSED(b);
  gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
  gtk_editable_insert_text(GTK_EDITABLE(io_field), "3", 1, &cursor_position);
  gtk_editable_set_position(
      GTK_EDITABLE(io_field),
      gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

/** @brief Proccesses pressing on an '4' button.
 *
 *  @param b a pointer to a pressed button.
 *  @param io_field a pointer to an input string window's element.
 *
 *  @return void.
 */
void on4(GtkButton* b, gpointer io_field) {
  UNUSED(b);
  gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
  gtk_editable_insert_text(GTK_EDITABLE(io_field), "4", 1, &cursor_position);
  gtk_editable_set_position(
      GTK_EDITABLE(io_field),
      gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

/** @brief Proccesses pressing on an '5' button.
 *
 *  @param b a pointer to a pressed button.
 *  @param io_field a pointer to an input string window's element.
 *
 *  @return void.
 */
void on5(GtkButton* b, gpointer io_field) {
  UNUSED(b);
  gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
  gtk_editable_insert_text(GTK_EDITABLE(io_field), "5", 1, &cursor_position);
  gtk_editable_set_position(
      GTK_EDITABLE(io_field),
      gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

/** @brief Proccesses pressing on an '6' button.
 *
 *  @param b a pointer to a pressed button.
 *  @param io_field a pointer to an input string window's element.
 *
 *  @return void.
 */
void on6(GtkButton* b, gpointer io_field) {
  UNUSED(b);
  gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
  gtk_editable_insert_text(GTK_EDITABLE(io_field), "6", 1, &cursor_position);
  gtk_editable_set_position(
      GTK_EDITABLE(io_field),
      gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

/** @brief Proccesses pressing on an '7' button.
 *
 *  @param b a pointer to a pressed button.
 *  @param io_field a pointer to an input string window's element.
 *
 *  @return void.
 */
void onseven(GtkButton* b, gpointer io_field) {
  UNUSED(b);
  gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
  gtk_editable_insert_text(GTK_EDITABLE(io_field), "7", 1, &cursor_position);
  gtk_editable_set_position(
      GTK_EDITABLE(io_field),
      gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

/** @brief Proccesses pressing on an '8' button.
 *
 *  @param b a pointer to a pressed button.
 *  @param io_field a pointer to an input string window's element.
 *
 *  @return void.
 */
void oneight(GtkButton* b, gpointer io_field) {
  UNUSED(b);
  gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
  gtk_editable_insert_text(GTK_EDITABLE(io_field), "8", 1, &cursor_position);
  gtk_editable_set_position(
      GTK_EDITABLE(io_field),
      gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

/** @brief Proccesses pressing on an '9' button.
 *
 *  @param b a pointer to a pressed button.
 *  @param io_field a pointer to an input string window's element.
 *
 *  @return void.
 */
void on9(GtkButton* b, gpointer io_field) {
  UNUSED(b);
  gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
  gtk_editable_insert_text(GTK_EDITABLE(io_field), "9", 1, &cursor_position);
  gtk_editable_set_position(
      GTK_EDITABLE(io_field),
      gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

/** @brief Proccesses pressing on an '0' button.
 *
 *  @param b a pointer to a pressed button.
 *  @param io_field a pointer to an input string window's element.
 *
 *  @return void.
 */
void on0(GtkButton* b, gpointer io_field) {
  UNUSED(b);
  gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
  gtk_editable_insert_text(GTK_EDITABLE(io_field), "0", 1, &cursor_position);
  gtk_editable_set_position(
      GTK_EDITABLE(io_field),
      gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

/** @brief Proccesses pressing on an '.' button.
 *
 *  @param b a pointer to a pressed button.
 *  @param io_field a pointer to an input string window's element.
 *
 *  @return void.
 */
void ondot(GtkButton* b, gpointer io_field) {
  UNUSED(b);
  gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
  gtk_editable_insert_text(GTK_EDITABLE(io_field), ".", 1, &cursor_position);
  gtk_editable_set_position(
      GTK_EDITABLE(io_field),
      gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

/** @brief Proccesses pressing on an '+' button.
 *
 *  @param b a pointer to a pressed button.
 *  @param io_field a pointer to an input string window's element.
 *
 *  @return void.
 */
void onplus(GtkButton* b, gpointer io_field) {
  UNUSED(b);
  gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
  gtk_editable_insert_text(GTK_EDITABLE(io_field), "+", 1, &cursor_position);
  gtk_editable_set_position(
      GTK_EDITABLE(io_field),
      gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

/** @brief Proccesses pressing on an '-' button.
 *
 *  @param b a pointer to a pressed button.
 *  @param io_field a pointer to an input string window's element.
 *
 *  @return void.
 */
void onminus(GtkButton* b, gpointer io_field) {
  UNUSED(b);
  gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
  gtk_editable_insert_text(GTK_EDITABLE(io_field), "-", 1, &cursor_position);
  gtk_editable_set_position(
      GTK_EDITABLE(io_field),
      gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

/** @brief Proccesses pressing on an '/' button.
 *
 *  @param b a pointer to a pressed button.
 *  @param io_field a pointer to an input string window's element.
 *
 *  @return void.
 */
void ondef(GtkButton* b, gpointer io_field) {
  UNUSED(b);
  gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
  gtk_editable_insert_text(GTK_EDITABLE(io_field), "/", 1, &cursor_position);
  gtk_editable_set_position(
      GTK_EDITABLE(io_field),
      gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

/** @brief Proccesses pressing on an '*' button.
 *
 *  @param b a pointer to a pressed button.
 *  @param io_field a pointer to an input string window's element.
 *
 *  @return void.
 */
void onmul(GtkButton* b, gpointer io_field) {
  UNUSED(b);
  gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
  gtk_editable_insert_text(GTK_EDITABLE(io_field), "*", 1, &cursor_position);
  gtk_editable_set_position(
      GTK_EDITABLE(io_field),
      gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

/** @brief Clears an input string.
 *
 *  @param b a pointer to a pressed button.
 *  @param io_field a pointer to an input string window's element.
 *
 *  @return void.
 */
void oncls(GtkButton* b, gpointer io_field) {
  UNUSED(b);
  gtk_editable_delete_text(GTK_EDITABLE(io_field), 0,
                           gtk_entry_get_max_length(GTK_ENTRY(io_field)));
}

/** @brief Deletes an element in an input string.
 *
 *  @param b a pointer to a pressed button.
 *  @param io_field a pointer to an input string window's element.
 *
 *  @return void.
 */
void ondel(GtkButton* b, gpointer io_field) {
  UNUSED(b);
  gtk_editable_delete_text(
      GTK_EDITABLE(io_field),
      gtk_editable_get_position(GTK_EDITABLE(io_field)) - 1,
      gtk_editable_get_position(GTK_EDITABLE(io_field)));
}

extern double* x;
extern double* y;
extern int count_of_dots;

/** @brief Posiotions a graph on a window.
 *
 *  @param b a pointer to a pressed button.
 *  @param plotter_window a pointer to GtkGrid window.
 *
 *  @return void.
 */
void on_plote_graph(GtkButton* b, GtkGrid* plotter_window) {
  UNUSED(b);
  double x_max;
  double x_min;
  double y_max;
  double y_min;
  char* endptr;
  GtkWidget* widget;
  char str[256];

  // initialize x_min, x_max, y_min, y_max on a graph
  widget = find_child(GTK_WIDGET(plotter_window), "id@gtk_xmin");
  g_snprintf(str, sizeof(str), "%s", gtk_entry_get_text(GTK_ENTRY(widget)));
  to_locale_decimal_point(str);
  x_min = strtod(str, &endptr);
  if (endptr == str || *endptr != '\0') {
    gtk_entry_set_text(GTK_ENTRY(widget), "error");
    return;
  }

  widget = find_child(GTK_WIDGET(plotter_window), "id@gtk_xmax");
  g_snprintf(str, sizeof(str), "%s", gtk_entry_get_text(GTK_ENTRY(widget)));
  to_locale_decimal_point(str);
  x_max = strtod(str, &endptr);
  if (endptr == str || *endptr != '\0') {
    gtk_entry_set_text(GTK_ENTRY(widget), "error");
    return;
  }

  widget = find_child(GTK_WIDGET(plotter_window), "id@gtk_ymin");
  g_snprintf(str, sizeof(str), "%s", gtk_entry_get_text(GTK_ENTRY(widget)));
  to_locale_decimal_point(str);
  y_min = strtod(str, &endptr);
  if (endptr == str || *endptr != '\0') {
    gtk_entry_set_text(GTK_ENTRY(widget), "error");
    return;
  }

  widget = find_child(GTK_WIDGET(plotter_window), "id@gtk_ymax");
  g_snprintf(str, sizeof(str), "%s", gtk_entry_get_text(GTK_ENTRY(widget)));
  to_locale_decimal_point(str);
  y_max = strtod(str, &endptr);
  if (endptr == str || *endptr != '\0') {
    gtk_entry_set_text(GTK_ENTRY(widget), "error");
    return;
  }

  widget = find_child(GTK_WIDGET(plotter_window), "id@gtk_entry");
  g_snprintf(str, sizeof(str), "%s", gtk_entry_get_text(GTK_ENTRY(widget)));

  que* qu;

  linspace(x, x_min, x_max, count_of_dots);

  if (str_to_polish(str, &qu) == true) {
    for (int i = 0; i < count_of_dots; ++i) {
      y[i] = calculate(qu, x[i]);
    }
    plotter_set_domain(y_min, y_max);
    plotter_set_range(x_min, x_max);
    plotter_set_function(x, y, count_of_dots);
    gtk_widget_set_sensitive(GTK_WIDGET(plotter_window), FALSE);
    gtk_widget_hide(GTK_WIDGET(plotter_window));
    plotter_draw();
    plotter_signal_connect_on_close(on_plotter_window_close,
                                    (gpointer)plotter_window);
  } else {
    gtk_entry_buffer_set_text(gtk_entry_get_buffer(GTK_ENTRY(widget)), "ERROR",
                              6);
  }
  queue_free(qu);
}

/** @brief Calculates a loan.
 *
 *  @param b a pointer to a pressed button.
 *  @param plotter_window a pointer to GtkGrid window.
 *
 *  @return void.
 */
void on_get_loan(GtkButton* b, GtkGrid* plotter_window) {
  UNUSED(b);
  double sum, rate, term, month_pay, over_pay, all_pay, month_pay_first,
      month_pay_last;
  int annu = 0, res;
  char* endptr;
  GtkWidget* widget;
  char str[256];

  widget = find_child(GTK_WIDGET(plotter_window), "id@gtk_sum");
  g_snprintf(str, sizeof(str), "%s", gtk_entry_get_text(GTK_ENTRY(widget)));
  to_locale_decimal_point(str);
  sum = strtof(str, &endptr);
  if (endptr == str || *endptr != '\0') {
    gtk_entry_set_text(GTK_ENTRY(widget), "error");
    return;
  }
  // printf("%f\n", sum);

  widget = find_child(GTK_WIDGET(plotter_window), "id@gtk_rate");
  g_snprintf(str, sizeof(str), "%s", gtk_entry_get_text(GTK_ENTRY(widget)));
  to_locale_decimal_point(str);
  rate = strtof(str, &endptr);
  if (endptr == str || *endptr != '\0') {
    gtk_entry_set_text(GTK_ENTRY(widget), "error");
    return;
  }
  // printf("%f\n", rate);

  widget = find_child(GTK_WIDGET(plotter_window), "id@gtk_annu");
  g_snprintf(str, sizeof(str), "%s", gtk_entry_get_text(GTK_ENTRY(widget)));
  if (strstr(str, "y")) annu = 1;
  // printf("%d\n", annu);
  if (endptr == str || *endptr != '\0') {
    gtk_entry_set_text(GTK_ENTRY(widget), "error");
    return;
  }

  widget = find_child(GTK_WIDGET(plotter_window), "id@gtk_term");
  g_snprintf(str, sizeof(str), "%s", gtk_entry_get_text(GTK_ENTRY(widget)));
  to_locale_decimal_point(str);
  term = strtof(str, &endptr);
  if (endptr == str || *endptr != '\0') {
    gtk_entry_set_text(GTK_ENTRY(widget), "error");
    return;
  }
  // printf("%f\n", term);

  widget = find_child(GTK_WIDGET(plotter_window), "id@gtk_entry");
  // g_snprintf(str, sizeof(str), "%s", gtk_entry_get_text(GTK_ENTRY(widget)));

  if (annu) {
    res = credit_annuity(sum, term, rate, &month_pay, &over_pay, &all_pay);
    // printf("%f %f %f\n", month_pay, over_pay, all_pay);
    if (!res)
      g_snprintf(
          str, sizeof(str),
          "Monthly payment: %.2f, overpayment: %.2f, total payment: %.2f",
          month_pay, over_pay, all_pay);
  } else {
    res = credit_dif(sum, term, rate, &month_pay_first, &month_pay_last,
                     &over_pay, &all_pay);
    if (!res)
      g_snprintf(str, sizeof(str),
                 "1st payment: %.2f, last payment: %.2f overpayment: %.2f, "
                 "total payment: %.2f",
                 month_pay_first, month_pay_last, over_pay, all_pay);
  }
  if (!res) {
    gtk_entry_buffer_set_text(gtk_entry_get_buffer(GTK_ENTRY(widget)), str,
                              strlen(str));
  } else {
    gtk_entry_set_text(GTK_ENTRY(widget), "error");
  }
}

/** @brief Calculates a deposit.
 *
 *  @param b a pointer to a pressed button.
 *  @param plotter_window a pointer to GtkGrid window.
 *
 *  @return void.
 */
void on_deposit_loan(GtkButton* b, GtkGrid* plotter_window) {
  UNUSED(b);
  double all_sum, interest, tax, tern;
  char* endptr;
  // int cap = 0;
  GtkWidget* widget;
  char str[256];

  double re1[10];  // refill months
  double re2[10];  // sum
  int countR = 0;  // amount of refills

  double wi1[10];  // withdrawals
  double wi2[10];
  int countW = 0;
  double all_interest, all_tax, all_sum_after;

  int globalPeriod = 0;
  int globalKap = 0;

  widget = find_child(GTK_WIDGET(plotter_window), "id@gtk_summa");
  g_snprintf(str, sizeof(str), "%s", gtk_entry_get_text(GTK_ENTRY(widget)));
  to_locale_decimal_point(str);
  all_sum = strtof(str, &endptr);
  if (endptr == str || *endptr != '\0') {
    gtk_entry_set_text(GTK_ENTRY(widget), "error");
    return;
  }

  widget = find_child(GTK_WIDGET(plotter_window), "id@gtk_irate");
  g_snprintf(str, sizeof(str), "%s", gtk_entry_get_text(GTK_ENTRY(widget)));
  to_locale_decimal_point(str);
  interest = strtof(str, &endptr);
  if (endptr == str || *endptr != '\0') {
    gtk_entry_set_text(GTK_ENTRY(widget), "error");
    return;
  }

  widget = find_child(GTK_WIDGET(plotter_window), "id@gtk_tax");
  g_snprintf(str, sizeof(str), "%s", gtk_entry_get_text(GTK_ENTRY(widget)));
  to_locale_decimal_point(str);
  tax = strtof(str, &endptr);
  if (endptr == str || *endptr != '\0') {
    gtk_entry_set_text(GTK_ENTRY(widget), "error");
    return;
  }

  widget = find_child(GTK_WIDGET(plotter_window), "id@gtk_cap");
  g_snprintf(str, sizeof(str), "%s", gtk_entry_get_text(GTK_ENTRY(widget)));
  if (strstr(str, "y")) globalKap = 1;
  if (endptr == str || *endptr != '\0') {
    gtk_entry_set_text(GTK_ENTRY(widget), "error");
    return;
  }

  widget = find_child(GTK_WIDGET(plotter_window), "id@gtk_months");
  g_snprintf(str, sizeof(str), "%s", gtk_entry_get_text(GTK_ENTRY(widget)));
  to_locale_decimal_point(str);
  tern = strtod(str, &endptr);
  if (endptr == str || *endptr != '\0') {
    gtk_entry_set_text(GTK_ENTRY(widget), "error");
    return;
  }

  widget = find_child(GTK_WIDGET(plotter_window), "id@gtk_per");
  g_snprintf(str, sizeof(str), "%s", gtk_entry_get_text(GTK_ENTRY(widget)));
  if (strstr(str, "m"))
    globalPeriod = 1;
  else if (strstr(str, "q"))
    globalPeriod = 3;
  else if (strstr(str, "y"))
    globalPeriod = 12;
  else
    gtk_entry_set_text(GTK_ENTRY(widget), "error");
  if (endptr == str || *endptr != '\0') {
    gtk_entry_set_text(GTK_ENTRY(widget), "error");
    return;
  }

  // refill
  widget = find_child(GTK_WIDGET(plotter_window), "id@gtk_refill");
  g_snprintf(str, sizeof(str), "%s", gtk_entry_get_text(GTK_ENTRY(widget)));
  to_locale_decimal_point(str);
  char* token = strtok(str, ";");
  while (token != NULL) {
    char* lpoint = strstr(token, ",");
    if (lpoint) {
      int buff_len = lpoint - token;
      char subbuff[buff_len + 1];
      memcpy(subbuff, token, buff_len);
      subbuff[buff_len] = '\0';

      re1[countR] = strtof(subbuff, &endptr);
      if (endptr == subbuff || *endptr != '\0') {
        gtk_entry_set_text(GTK_ENTRY(widget), "error");
        return;
      }
      re2[countR] = strtof(lpoint + 1, &endptr);
      if (endptr == (lpoint + 1) || *endptr != '\0') {
        gtk_entry_set_text(GTK_ENTRY(widget), "error");
        return;
      }
      countR++;
    }
    token = strtok(NULL, ";");
  }

  // withdraw
  widget = find_child(GTK_WIDGET(plotter_window), "id@gtk_wi");
  g_snprintf(str, sizeof(str), "%s", gtk_entry_get_text(GTK_ENTRY(widget)));
  to_locale_decimal_point(str);
  token = strtok(str, ";");
  while (token != NULL) {
    char* lpoint = strstr(token, ",");
    if (lpoint) {
      int buff_len = lpoint - token;
      char subbuff[buff_len + 1];
      memcpy(subbuff, token, buff_len);
      subbuff[buff_len] = '\0';

      wi1[countW] = strtof(subbuff, &endptr);
      if (endptr == subbuff || *endptr != '\0') {
        gtk_entry_set_text(GTK_ENTRY(widget), "error");
        return;
      }
      wi2[countW] = strtof(lpoint + 1, &endptr);
      if (endptr == (lpoint + 1) || *endptr != '\0') {
        gtk_entry_set_text(GTK_ENTRY(widget), "error");
        return;
      }
      countW++;
    }
    token = strtok(NULL, ";");
  }

  widget = find_child(GTK_WIDGET(plotter_window), "id@gtk_dep");
  if (deposit_calculator(re1, re2, countR, wi1, wi2, countW, all_sum, tern,
                         interest, tax, globalPeriod, globalKap, &all_interest,
                         &all_tax, &all_sum_after)) {
    gtk_entry_set_text(GTK_ENTRY(widget), "error");
  } else {
    g_snprintf(str, sizeof(str), "Interest: %.2f, Taxes: %.2f Sum: %.2f",
               all_interest, all_tax, all_sum_after);
    gtk_entry_buffer_set_text(gtk_entry_get_buffer(GTK_ENTRY(widget)), str,
                              strlen(str));
  }
}
