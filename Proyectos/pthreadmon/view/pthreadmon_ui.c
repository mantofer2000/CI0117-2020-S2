#include <gtk/gtk.h>
#include <stdlib.h>

GtkWidget *window; // Ventana.
GtkWidget *grid;

GtkWidget *button_start;

GtkWidget *input_labels[3];

GtkWidget *pokemon_labels[3];

GtkWidget *attacks_info_label;

void myCSS(void)
{
    GtkCssProvider* provider;
    GdkDisplay* display;
    GdkScreen* screen;

    provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    const gchar* my_css_file = "view/color_test.css";
    GError* error = 0;

    gtk_css_provider_load_from_file(provider, g_file_new_for_path(my_css_file), &error);
    g_object_unref(provider);
}

static void start_clicked()
{
    g_print("Start button pressed\n");
}

static void activate(GtkApplication* app, gpointer user_data)
{
    myCSS();

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Pthreadmon");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 600);
    //gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_container_set_border_width(GTK_CONTAINER(window), 5);

    grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);

    gtk_container_add(GTK_CONTAINER(window), grid);

    for ( int index = 0; index < 3; ++index )
    {
        input_labels[index] = gtk_entry_new();

        char num[7] = "Input ";
        num[6] = index + '1';

        gtk_entry_set_text(GTK_ENTRY(input_labels[index]), num);

        gtk_grid_attach(GTK_GRID(grid), input_labels[index], index, 0, 1, 1);
    }

    // A esto hay que hacerle un draw y eso pero por ahora los hago aqui para probar

    pokemon_labels[0] = gtk_label_new("HP: ");
    gtk_widget_set_name(pokemon_labels[0], "hp_label");
    pokemon_labels[1] = gtk_image_new();
    gtk_image_set_from_file(GTK_IMAGE(pokemon_labels[1]), "sprites/mew.png");
    gtk_image_set_from_pixbuf(GTK_IMAGE(pokemon_labels[1]),
        gdk_pixbuf_scale_simple(gtk_image_get_pixbuf(GTK_IMAGE(pokemon_labels[1])),
        75, 75, GDK_INTERP_NEAREST));
    pokemon_labels[2] = gtk_label_new("Energy: ");
    gtk_widget_set_name(pokemon_labels[2], "energy_label");

    for ( int label = 0; label < 3; ++label )
        gtk_grid_attach(GTK_GRID(grid), pokemon_labels[label], 2, label + 1, 1, 1);

    pokemon_labels[0] = gtk_label_new("HP: ");
    gtk_widget_set_name(pokemon_labels[0], "hp_label");
    pokemon_labels[1] = gtk_image_new();
    gtk_image_set_from_file(GTK_IMAGE(pokemon_labels[1]), "sprites/magnezone.png");
    gtk_image_set_from_pixbuf(GTK_IMAGE(pokemon_labels[1]),
        gdk_pixbuf_scale_simple(gtk_image_get_pixbuf(GTK_IMAGE(pokemon_labels[1])),
        75, 75, GDK_INTERP_NEAREST));
    pokemon_labels[2] = gtk_label_new("Energy: ");
    gtk_widget_set_name(pokemon_labels[2], "energy_label");

    for ( int label = 0; label < 3; ++label )
        gtk_grid_attach(GTK_GRID(grid), pokemon_labels[label], 0, label + 4, 1, 1);

    attacks_info_label = gtk_label_new("-");
    gtk_widget_set_name(attacks_info_label, "attacks_info");
    gtk_grid_attach(GTK_GRID(grid), attacks_info_label, 1, 2, 1, 4);

    for ( int index = 0; index < 3; ++index )
    {
        input_labels[index] = gtk_entry_new();

        char num[7] = "Input ";
        num[6] = index + '1';

        gtk_entry_set_text(GTK_ENTRY(input_labels[index]), num);

        gtk_grid_attach(GTK_GRID(grid), input_labels[index], index, 7, 1, 1);
    }

    button_start = gtk_button_new_with_label("Start");
    g_signal_connect(button_start, "clicked", G_CALLBACK(start_clicked), NULL);

    gtk_grid_attach(GTK_GRID(grid), button_start, 2, 8, 1, 1);

    attacks_info_label = gtk_label_new("-");
    gtk_widget_set_name(attacks_info_label, "attacks_info");
    gtk_grid_attach(GTK_GRID(grid), attacks_info_label, 0, 8, 3, 2);

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