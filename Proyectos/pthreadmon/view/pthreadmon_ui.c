#include <gtk/gtk.h>
#include <stdlib.h>

GtkWidget *window; // Ventana.
GtkWidget *grid;

GtkWidget *button_start;

static void start_clicked()
{
    g_print("Start button pressed\n");
}

static void activate(GtkApplication* app, gpointer user_data)
{
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Pthreadmon");
    gtk_window_set_default_size(GTK_WINDOW(window), 350, 500);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    grid = gtk_grid_new();

    gtk_container_add(GTK_CONTAINER(window), grid);

    button_start = gtk_button_new_with_label("Start");
    g_signal_connect(button_start, "clicked", G_CALLBACK(start_clicked), NULL);

    gtk_grid_attach(GTK_GRID(grid), button_start, 3, 9, 4, 2);

    gtk_widget_show_all(window);
}

int main(int argc, char* argv[])
{
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.pthreadmon", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    if ( !(status) )
        printf("Funciono crack\n");

    return status;
}