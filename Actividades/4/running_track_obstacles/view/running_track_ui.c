#include <gtk/gtk.h>
#include <stdlib.h>
#include "../model/running_track.h"
#include "../model/main.h"

GtkWidget *window; // Ventana.
GtkWidget *grid; // Contenedor.

// Estos van a servir para representar la linea de partida y llegada en la interfaz.
GtkWidget *labels_start_line[NUM_LANES];
GtkWidget *labels_finish_line[NUM_LANES];

// Matriz de imagenes.
GtkWidget* images[NUM_LANES][NUM_OBSTACLES];

GtkWidget *button_start;

// Para que es esta vara si no hace nada? xd (revisar)
static void my_callback(GObject *source_object, GAsyncResult *res,
                        gpointer user_data)
{
   /* Do nothing */
}

// Llama al metodo de main.c para iniciar la carrera.
static void start_async(GTask *task, gpointer source_object,
                        gpointer task_data, GCancellable *cancellable)
{
    start_race();
}

// Este metodo es llamado cuando se hace click en el boton START.
static void start_clicked()
{
    // Nota: Revisar que hace GCancellable
    GCancellable *cancellable = g_cancellable_new();
    GTask *task = g_task_new(g_object_new(G_TYPE_OBJECT, NULL), cancellable, my_callback, NULL);
    g_task_run_in_thread(task, start_async);
    g_object_unref(task);
}

// Dibuja la pista de carreras.
static gboolean draw_running_track(GtkWidget *widget,
                                GdkEventExpose *event,
                                gpointer data)
{
    pthread_mutex_lock(&mutex_running_track);
    // Si running_track no es nulo
    if (running_track)
    {
        // Recorrer las filas de la matriz
        for ( int row = 0; row < NUM_LANES; ++row )
        {
            // Si la linea de partida esta en 1 entonces avisar que el corredor esta listo.
            if ( running_track->lanes_start_line[row] )
                gtk_label_set_text(GTK_LABEL(labels_start_line[row]), "READY!");
            // De lo contrario, esperar (imprimir -).
            else
                gtk_label_set_text(GTK_LABEL(labels_start_line[row]), "-");

            // Si la linea de llegada esta en 1 entonces
            if ( running_track->lanes_finish_line[row] )
            {
                char position_string[10];
                // Ojo: sprintf guarda la impresion en la varaible que se ponga como primer parametro.
                sprintf(position_string, "Place: %d", running_track->lanes_finish_line[row]);
                // Y esto agarra la cadena que habiamos guardado y la asigna como texto de la posicion i
                // de la linea de llegada.
                gtk_label_set_text(GTK_LABEL(labels_finish_line[row]), position_string);
            }
            else // De lo contrario
            {
                // Esperar y asignar "-" por mientras.
                gtk_label_set_text(GTK_LABEL(labels_finish_line[row]), "-");
            }

            // Recorrer las columnas de la matriz.
            for ( int column = 0; column < NUM_OBSTACLES; ++column )
            {
                // Si la posicion actual de la matriz esta en 1 entonces
                if ( running_track->obstacles[row][column] )
                {
                    // Agarra la imagen del archivo especificado.
                    gtk_image_set_from_file(GTK_IMAGE(images[row][column]), "view/runner.png");
                    // Esto le da el tamano a la imagen que agarra del archivo.
                    gtk_image_set_from_pixbuf(GTK_IMAGE(images[row][column]),
                        gdk_pixbuf_scale_simple(gtk_image_get_pixbuf(GTK_IMAGE(images[row][column])),
                        50, 50, GDK_INTERP_NEAREST));
                }
                else // De lo contario
                {
                    // Quitar la imagen que este en la posicion actual de la matriz.
                    gtk_image_clear(GTK_IMAGE(images[row][column]));
                }
            }
        }
    }
    pthread_mutex_unlock(&mutex_running_track);

    return TRUE; // Valor gboolean
}

// Inserta todo en la ventana y al final la muestra.
static void
activate(GtkApplication *app,
         gpointer user_data)
{

    // Crear una nueva ventana, asignar su titulo y tamano.
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Running Track");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 600);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    // construct the container and sets the rows / columns to be of the same size (homogeneeous)
    grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);

    // Agrega el grid a la ventana.
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Crear el boton para comenzar la carrera.
    // Asigna el evento "clicked".
    button_start = gtk_button_new_with_label("START");
    g_signal_connect(button_start, "clicked", G_CALLBACK(start_clicked), NULL);

    // Coloca el boton en la celda (3, 9) del grid, con width = 3 y height = 1.
    gtk_grid_attach(GTK_GRID(grid), button_start, 3, 9, 3, 1);

    // Crear y ajustar las imagenes al grid.
    for ( int row = 0; row < NUM_LANES; ++row )
    {
        // Nota: Recordar que "y" = filas y "x" = columnas.
        int position_y = row + 1; // Esto se saca a puro calculo?

        for ( int column = 0; column < NUM_OBSTACLES; ++column )
        {
            int position_x = column + 2;
            // Inicializar cada posicion de la matriz con una imagen.
            images[row][column] = gtk_image_new();
            // Ajustar cada imagen en el grid.
            gtk_grid_attach(GTK_GRID(grid), images[row][column], position_x, position_y, 1, 1);
        }
    }

    // Crear y ajustar los labels al grid.
    for ( int index = 0; index < NUM_LANES; ++index )
    {
        // Inicializar todas las posiciones de la linea de partida con un label "-".
        labels_start_line[index] = gtk_label_new("-");
        // Ajustar cada label en el grid.
        gtk_grid_attach(GTK_GRID(grid), labels_start_line[index], 1, index + 1, 1, 1);

        // Inicializar todas las posiciones de la linea de llegada con un label "-".
        labels_finish_line[index] = gtk_label_new("-");
        // Ajustar cada label en el grid.
        gtk_grid_attach(GTK_GRID(grid), labels_finish_line[index], NUM_OBSTACLES + 2, index + 1, 1, 1);
    }

    // Nota: Investigar que hace esto.
    g_timeout_add(33, (GSourceFunc)draw_running_track, (gpointer)window);

    // Mostrar todos los widgets en la ventana.
    gtk_widget_show_all(window);
}

int main(int argc, char* argv[])
{
    pthread_mutex_init(&mutex_running_track, NULL);

    // Puntero a GtkApplication.
    GtkApplication *app;
    int status;

    // Inicializar el puntero.
    app = gtk_application_new("example.gtk.running_track", G_APPLICATION_FLAGS_NONE);
    // La senal de activacion se conecta a la funcion activate.
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    // Cuando se inicia la aplicacion, se envia la senal.
    // Al salir de la ventana, el ciclo principal retrona un numero que se guarda en status.
    status = g_application_run(G_APPLICATION(app), argc, argv);
    // Liberar la memoria del objeto.
    g_object_unref(app);

    pthread_mutex_destroy(&mutex_running_track);

    if ( !(status) )
        printf("Funciono crack\n");

    return status;

}