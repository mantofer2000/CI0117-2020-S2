#include <gtk/gtk.h>
#include <stdlib.h>

GtkWidget *window; // Ventana.
GtkWidget *grid;

GtkWidget *button_start;

GtkWidget *input_labels[3];

GtkWidget *pokemon_labels[3];

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

    for ( int index = 0; index < 3; ++index )
    {
        input_labels[index] = gtk_entry_new();

        char num[7] = "Input ";
        num[6] = index + '1';

        gtk_entry_set_text(GTK_ENTRY(input_labels[index]), num);

        gtk_grid_attach(GTK_GRID(grid), input_labels[index], index + 1, 3, 1, 1);
    }

    // A esto hay que hacerle un draw y eso pero por ahora los hago aqui para probar

    pokemon_labels[0] = gtk_label_new("HP: ");
    pokemon_labels[1] = gtk_image_new();
    gtk_image_set_from_file(GTK_IMAGE(pokemon_labels[1]), "sprites/mew.png");
    gtk_image_set_from_pixbuf(GTK_IMAGE(pokemon_labels[1]),
        gdk_pixbuf_scale_simple(gtk_image_get_pixbuf(GTK_IMAGE(pokemon_labels[1])),
        50, 50, GDK_INTERP_NEAREST));
    pokemon_labels[2] = gtk_label_new("Energy: ");

    for ( int label = 0; label < 3; ++label )
        gtk_grid_attach(GTK_GRID(grid), pokemon_labels[label], 3, label + 4, 1, 1);

    pokemon_labels[0] = gtk_label_new("HP: ");
    pokemon_labels[1] = gtk_image_new();
    gtk_image_set_from_file(GTK_IMAGE(pokemon_labels[1]), "sprites/magnezone.png");
    gtk_image_set_from_pixbuf(GTK_IMAGE(pokemon_labels[1]),
        gdk_pixbuf_scale_simple(gtk_image_get_pixbuf(GTK_IMAGE(pokemon_labels[1])),
        50, 50, GDK_INTERP_NEAREST));
    pokemon_labels[2] = gtk_label_new("Energy: ");

    for ( int label = 0; label < 3; ++label )
        gtk_grid_attach(GTK_GRID(grid), pokemon_labels[label], 1, label + 8, 1, 1);

    for ( int index = 0; index < 3; ++index )
    {
        input_labels[index] = gtk_entry_new();

        char num[7] = "Input ";
        num[6] = index + '1';

        gtk_entry_set_text(GTK_ENTRY(input_labels[index]), num);

        gtk_grid_attach(GTK_GRID(grid), input_labels[index], index + 1, 12, 1, 1);
    }

    button_start = gtk_button_new_with_label("Start");
    g_signal_connect(button_start, "clicked", G_CALLBACK(start_clicked), NULL);

    gtk_grid_attach(GTK_GRID(grid), button_start, 3, 13, 4, 2);

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

    return status;
}