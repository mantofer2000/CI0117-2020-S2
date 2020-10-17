#include <gtk/gtk.h>
#include <stdlib.h>

GtkWidget *window; // Ventana.
GtkWidget *grid;

static void activate(GtkApplication* app, gpointer user_data)
{
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Pthreadmon");
    gtk_window_set_default_size(GTK_WINDOW(window), 350, 500);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

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