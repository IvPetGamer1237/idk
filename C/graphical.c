#include <gtk/gtk.h>
void on_destroy(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}
int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Window");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_size_request(window, 200, 50);
    GtkWidget *label = gtk_label_new("sus");
    gtk_container_add(GTK_CONTAINER(window), label);
    g_signal_connect(window, "destroy", G_CALLBACK(on_destroy), NULL);
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
