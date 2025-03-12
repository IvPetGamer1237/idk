#include <gtk/gtk.h>

// Callback function for the button click event
static void on_button_clicked(GtkWidget *widget, gpointer data) {
    // Quit the GTK main loop when the button is clicked
    gtk_main_quit();
}

// Callback function for the window destroy event
void on_destroy(GtkWidget *widget, gpointer data) {
    // Quit the GTK main loop when the window is destroyed
    gtk_main_quit();
}

int main(int argc, char *argv[]) {
    // Initialize the GTK library
    gtk_init(&argc, &argv);

    // Create a new top-level window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *button;

    // Set the title of the window
    gtk_window_set_title(GTK_WINDOW(window), "Window");

    // Set the border width of the window
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    // Set the minimum size of the window
    gtk_widget_set_size_request(window, 200, 100);

    // Create a vertical box container to hold multiple widgets
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5); // 5 is the spacing between widgets
    gtk_container_add(GTK_CONTAINER(window), vbox); // Add the box to the window

    // Create a new label with the text "sus"
    GtkWidget *label = gtk_label_new("sus");

    // Add the label to the box
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);

    // Create a new button with the label "ok"
    button = gtk_button_new_with_label("ok");

    // Connect the "clicked" signal of the button to the on_button_clicked callback
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);

    // Add the button to the box
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

    // Connect the "destroy" signal of the window to the on_destroy callback
    g_signal_connect(window, "destroy", G_CALLBACK(on_destroy), NULL);

    // Show all widgets in the window
    gtk_widget_show_all(window);

    // Start the GTK main loop
    gtk_main();

    return 0;
}