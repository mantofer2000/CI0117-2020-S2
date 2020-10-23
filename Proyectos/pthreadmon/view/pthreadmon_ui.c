#include "../model/game_master.h"
#include "../model/mapper.h"
#include "../model/player.h"
#include "../model/pokemon.h"

#include <gtk/gtk.h>
#include <stdlib.h>

GtkWidget *window; // Ventana.
GtkWidget *grid;

GtkWidget *dialog;
GtkWidget *label;
GtkWidget *box;
GtkWidget *content_area;

GtkWidget *button_start;
GtkWidget *test_button;

GtkWidget *input_name_label;
GtkWidget *input_labels[3];

GtkWidget *pokemon_labels1[3];
GtkWidget *pokemon_labels2[3];

GtkWidget *attacks_info_label;

GtkWidget *poke_list_labels[5];

char* player1_name;
char* player2_name;

int player_id;
int id1, id2, id3;

player_t* player1;
player_t* player2;

pokemon_t** random_pokemon_list;


static void start_async(GTask *task, gpointer source_object,
                        gpointer task_data, GCancellable *cancellable);

static void show_poke_list(GtkWindow* parent);
static void poke_list(GtkWidget* widget, gpointer data);

void player_get_name(GtkWindow* parent, int id);

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

pokemon_t** generate_random_pokes()
{
    pokemon_t** random_pokemon_list = malloc( 5 * sizeof(pokemon_t*) );

    int poke = 0;
    int rand_id = 0;
    int is_repeated = 0;
    while (poke < 5)
    {
        rand_id = (rand() % 49);
        
        for ( int index = 0; index < poke; ++index )
        {
            if ( poke > 0 )
            {
                if ( random_pokemon_list[index]->pokemon_info->id == rand_id )
                {
                    is_repeated = 1;
                    break;
                }
                else
                {
                    is_repeated = 0;
                }
            }
            
        }
        if ( !(is_repeated) )
        {
            random_pokemon_list[poke] = pokemon_create(rand_id); 
            ++poke;
        }
    }
    return random_pokemon_list;
}

static void my_callback(GObject *source_object, GAsyncResult *res,
                        gpointer user_data)
{
   /* Do nothing */
}

static void player_team()
{
    if ( player_id == 1 )
    {
        player1->pokemon_team = choose_team(id1, id2, id3);
        player_id = 2;

        player_get_name(GTK_WINDOW(window), player_id);
    }
    else
    {
        player2->pokemon_team = choose_team(id1, id2, id3);
        GCancellable *cancellable = g_cancellable_new();
        GTask *task = g_task_new(g_object_new(G_TYPE_OBJECT, NULL), cancellable, my_callback, NULL);
        g_task_run_in_thread(task, start_async);
        g_object_unref(task);
    }    
}

int is_an_option(int id)
{
    for ( int index = 0; index < 5; ++index )
        if ( random_pokemon_list[index]->pokemon_info->id == id )
            return 1;

    return 0;
}

static void options_dialog(GtkWindow* parent)
{
    GtkDialogFlags flags;
    flags = GTK_DIALOG_DESTROY_WITH_PARENT;

    dialog = gtk_dialog_new();
    gtk_window_set_title(GTK_WINDOW(dialog), "X");

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    label = gtk_label_new("Wrong choice. Try again");

    gtk_container_add(GTK_CONTAINER(content_area), label);

    test_button = gtk_button_new_with_mnemonic("_OK");
    gtk_container_add(GTK_CONTAINER(content_area), test_button);

    g_signal_connect(test_button, "clicked", G_CALLBACK(poke_list), NULL);
    g_signal_connect_swapped(test_button, "clicked", G_CALLBACK(gtk_widget_destroy), dialog);

    g_signal_connect_swapped(dialog, "response", G_CALLBACK(gtk_widget_destroy), dialog);

    gtk_widget_show_all(dialog);
}

static void verify()
{
    if ( !(is_an_option(id1)) || !(is_an_option(id2)) || !(is_an_option(id3))
        || (id1 == id2) || (id1 == id3) || (id2 == id3) )
        options_dialog(GTK_WINDOW(window));
    else
        player_team();
}

static void assign_id1(GtkWidget* widget, gpointer data)
{
    char* temp = (char*) gtk_entry_get_text(GTK_ENTRY(data));
    id1 = strtoul(temp, NULL, 10);
}

static void assign_id2(GtkWidget* widget, gpointer data)
{
    char* temp = (char*) gtk_entry_get_text(GTK_ENTRY(data));
    id2 = strtoul(temp, NULL, 10);
}

static void assign_id3(GtkWidget* widget, gpointer data)
{
    char* temp = (char*) gtk_entry_get_text(GTK_ENTRY(data));
    id3 = strtoul(temp, NULL, 10);
    verify();
}

static void show_poke_list(GtkWindow* parent)
{
    GtkDialogFlags flags;
    flags = GTK_DIALOG_DESTROY_WITH_PARENT;

    dialog = gtk_dialog_new();
    gtk_window_set_title(GTK_WINDOW(dialog), "Pokemon list");

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    label = gtk_label_new("Options");

    gtk_container_add(GTK_CONTAINER(content_area), label);

    for ( int index = 0; index < 5; ++index )
    {
        char temp[50];
        sprintf(temp, "%d: %s", random_pokemon_list[index]->pokemon_info->id,
                random_pokemon_list[index]->pokemon_info->speciesName);

        poke_list_labels[index] = gtk_label_new(temp);

        gtk_container_add(GTK_CONTAINER(content_area), poke_list_labels[index]);
    }

    for ( int index = 0; index < 3; ++index )
    {
        input_labels[index] = gtk_entry_new();

        gtk_container_add(GTK_CONTAINER(content_area), input_labels[index]);
    }

    test_button = gtk_button_new_with_mnemonic("_Go!");
    gtk_container_add(GTK_CONTAINER(content_area), test_button);

    g_signal_connect(test_button, "clicked", G_CALLBACK(assign_id1), input_labels[0]);
    g_signal_connect(test_button, "clicked", G_CALLBACK(assign_id2), input_labels[1]);
    g_signal_connect(test_button, "clicked", G_CALLBACK(assign_id3), input_labels[2]);
    g_signal_connect_swapped(test_button, "clicked", G_CALLBACK(gtk_widget_destroy), dialog);

    g_signal_connect_swapped(dialog, "response", G_CALLBACK(gtk_widget_destroy), dialog);

    gtk_widget_show_all(dialog);
}

static void poke_list(GtkWidget* widget, gpointer data)
{
    show_poke_list(GTK_WINDOW(window));
}

static void name_1(GtkWidget* widget, gpointer data)
{
    player1_name = (char*) gtk_entry_get_text(GTK_ENTRY(data));
    set_name(player1, player1_name);
}

static void name_2(GtkWidget* widget, gpointer data)
{
    player2_name = (char*) gtk_entry_get_text(GTK_ENTRY(data));
    set_name(player2, player2_name);
}

void player_get_name(GtkWindow* parent, int id)
{
    GtkDialogFlags flags;
    flags = GTK_DIALOG_DESTROY_WITH_PARENT;
    dialog = gtk_dialog_new();
    
    gtk_window_set_title(GTK_WINDOW(dialog), "Name");

    random_pokemon_list = generate_random_pokes();

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    char label_text[30];
    sprintf(label_text, "Player #%d. Type your name", id);
    label = gtk_label_new(label_text);
    gtk_container_add(GTK_CONTAINER(content_area), label);

    input_name_label = gtk_entry_new();
    gtk_container_add(GTK_CONTAINER(content_area), input_name_label);

    test_button = gtk_button_new_with_mnemonic("_Done!");

    if ( id == 1 )
    {
        g_signal_connect(test_button, "clicked", G_CALLBACK(name_1), input_name_label);
        g_signal_connect(input_name_label, "activate", G_CALLBACK(name_1), input_name_label);
        g_signal_connect(test_button, "clicked", G_CALLBACK(poke_list), NULL);
        g_signal_connect_swapped(test_button, "clicked", G_CALLBACK(gtk_widget_destroy), dialog);
    }
    else if ( id == 2 )
    {
        g_signal_connect(test_button, "clicked", G_CALLBACK(name_2), input_name_label);
        g_signal_connect(input_name_label, "activate", G_CALLBACK(name_2), input_name_label);
        g_signal_connect(test_button, "clicked", G_CALLBACK(poke_list), NULL);
        g_signal_connect_swapped(test_button, "clicked", G_CALLBACK(gtk_widget_destroy), dialog);
    }

    gtk_container_add(GTK_CONTAINER(content_area), test_button);

    g_signal_connect_swapped(dialog, "response", G_CALLBACK(gtk_widget_destroy), dialog);

    gtk_widget_show_all(dialog);


}

// Llama al metodo de main.c para iniciar la carrera.
static void start_async(GTask *task, gpointer source_object,
                        gpointer task_data, GCancellable *cancellable)
{  
    // Una vez creados los jugadores, INICIAR BATALLA
    initialize_fight(player1, player2);
}

static void create_players()
{
    player_id = 1;
    player_get_name(GTK_WINDOW(window), player_id);
}

// Este metodo es llamado cuando se hace click en el boton START.
static void start_clicked()
{
    create_players();
}

static gboolean draw_battle_arena(GtkWidget *widget, GdkEventExpose *event, gpointer data)
{
    pthread_mutex_lock(&battle_arena_mutex);

    if ( !(is_battle_over(player1, player2)) )
    {
        
        if ( battle_arena )
        {
            pokemon_t* poke_one = active_poke_one;

            char hp_1[50];
            if (poke_one->hp <= 0)
            {
                sprintf(hp_1, "Name: %s\nLost", poke_one->pokemon_info->speciesName);
                gtk_label_set_text(GTK_LABEL(pokemon_labels1[0]), hp_1);
            }
            else
            {
                sprintf(hp_1, "Name: %s\nHP: %d", poke_one->pokemon_info->speciesName, poke_one->hp);
                gtk_label_set_text(GTK_LABEL(pokemon_labels1[0]), hp_1);
            }

            gchar image_1[50];
            sprintf(image_1, "sprites/%s.png", poke_one->pokemon_info->speciesName);
            gtk_image_set_from_file(GTK_IMAGE(pokemon_labels1[1]), image_1);
            gtk_image_set_from_pixbuf(GTK_IMAGE(pokemon_labels1[1]),
                gdk_pixbuf_scale_simple(gtk_image_get_pixbuf(GTK_IMAGE(pokemon_labels1[1])),
                75, 75, GDK_INTERP_NEAREST));

            char energy_1[50];
            sprintf(energy_1, "Energy: %d\n", poke_one->energy);
            gtk_label_set_text(GTK_LABEL(pokemon_labels1[2]), energy_1);

            if ( poke_one->is_attacking )
            {
                if ( poke_one->attacking_charged )
                {
                    char charged[50];
                    sprintf(charged, "%s is using a CHARGED %s!!",
                        poke_one->pokemon_info->speciesName, poke_one->charged_move_info->moveName);
                    gtk_label_set_text(GTK_LABEL(attacks_info_label), charged);
                }
                else if ( poke_one->attacking_fast )
                {
                    char fast[50];
                    sprintf(fast, "%s is using %s!",
                        poke_one->pokemon_info->speciesName, poke_one->fast_move_info->moveName);
                    gtk_label_set_text(GTK_LABEL(attacks_info_label), fast);
                }
            }

            pokemon_t* poke_two = active_poke_two;

            char hp_2[50];
            if (poke_two->hp <= 0)
            {
                sprintf(hp_2, "Name: %s\nLost", poke_two->pokemon_info->speciesName);
                gtk_label_set_text(GTK_LABEL(pokemon_labels2[0]), hp_2);
            }
            else
            {
                sprintf(hp_2, "Name: %s\nHP: %d", poke_two->pokemon_info->speciesName, poke_two->hp);
                gtk_label_set_text(GTK_LABEL(pokemon_labels2[0]), hp_2);
            }
            
            gchar image_2[50];
            sprintf(image_2, "sprites/%s.png", poke_two->pokemon_info->speciesName);
            gtk_image_set_from_file(GTK_IMAGE(pokemon_labels2[1]), image_2);
            gtk_image_set_from_pixbuf(GTK_IMAGE(pokemon_labels2[1]),
                gdk_pixbuf_scale_simple(gtk_image_get_pixbuf(GTK_IMAGE(pokemon_labels2[1])),
                75, 75, GDK_INTERP_NEAREST));

            char energy_2[50];
            sprintf(energy_2, "Energy: %d\n", poke_two->energy);
            gtk_label_set_text(GTK_LABEL(pokemon_labels2[2]), energy_2);

            if ( poke_two->is_attacking )
            {
                if ( poke_two->attacking_charged )
                {
                    char charged[50];
                    sprintf(charged, "%s is using a CHARGED %s!!",
                        poke_two->pokemon_info->speciesName, poke_two->charged_move_info->moveName);
                    gtk_label_set_text(GTK_LABEL(attacks_info_label), charged);
                }
                else if ( poke_two->attacking_fast )
                {
                    char fast[50];
                    sprintf(fast, "%s is using %s!",
                        poke_two->pokemon_info->speciesName, poke_two->fast_move_info->moveName);
                    gtk_label_set_text(GTK_LABEL(attacks_info_label), fast);
                }
            }
        }
    }
    else
    {
        if ( battle_arena )
        {
            pokemon_t* poke_one = active_poke_one;

            char hp_1[10];

            if (poke_one->hp <= 0)
            {
                sprintf(hp_1, "Name: %s\nLost", poke_one->pokemon_info->speciesName);
                gtk_label_set_text(GTK_LABEL(pokemon_labels1[0]), hp_1);
            }
            else
            {
                sprintf(hp_1, "Name: %s\nHP: %d", poke_one->pokemon_info->speciesName, poke_one->hp);
                gtk_label_set_text(GTK_LABEL(pokemon_labels1[0]), hp_1);
            }
            
            gchar image_1[50];
            sprintf(image_1, "sprites/%s.png", poke_one->pokemon_info->speciesName);
            gtk_image_set_from_file(GTK_IMAGE(pokemon_labels1[1]), image_1);
            gtk_image_set_from_pixbuf(GTK_IMAGE(pokemon_labels1[1]),
                gdk_pixbuf_scale_simple(gtk_image_get_pixbuf(GTK_IMAGE(pokemon_labels1[1])),
                75, 75, GDK_INTERP_NEAREST));

            char move_info_1[50];
            sprintf(move_info_1, "Energy: %d\n", poke_one->energy);
            gtk_label_set_text(GTK_LABEL(pokemon_labels1[2]), move_info_1);

            pokemon_t* poke_two = active_poke_two;

            char hp_2[10];

            if (poke_two->hp <= 0)
            {
                sprintf(hp_2, "Name: %s\nLost", poke_two->pokemon_info->speciesName);
                gtk_label_set_text(GTK_LABEL(pokemon_labels2[0]), hp_2);
            }
            else
            {
                sprintf(hp_2, "Name: %s\nHP: %d", poke_two->pokemon_info->speciesName, poke_two->hp);
                gtk_label_set_text(GTK_LABEL(pokemon_labels2[0]), hp_2);
            }

            gchar image_2[50];
            sprintf(image_2, "sprites/%s.png", poke_two->pokemon_info->speciesName);
            gtk_image_set_from_file(GTK_IMAGE(pokemon_labels2[1]), image_2);
            gtk_image_set_from_pixbuf(GTK_IMAGE(pokemon_labels2[1]),
                gdk_pixbuf_scale_simple(gtk_image_get_pixbuf(GTK_IMAGE(pokemon_labels2[1])),
                75, 75, GDK_INTERP_NEAREST));

            char move_info_2[50];
            sprintf(move_info_2, "Energy: %d\n", poke_two->energy);
            gtk_label_set_text(GTK_LABEL(pokemon_labels2[2]), move_info_2);

            char announce[20];

            if ( poke_one->hp <= 0 )
                sprintf(announce, "The winner is %s!!", poke_two->pokemon_info->speciesName);
            else
                sprintf(announce, "The winner is %s!!", poke_one->pokemon_info->speciesName);

            gtk_label_set_text(GTK_LABEL(attacks_info_label), announce);
        }
        
    }

    pthread_mutex_unlock(&battle_arena_mutex);

    return TRUE;
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

    // A esto hay que hacerle un draw y eso pero por ahora los hago aqui para probar

    pokemon_labels1[0] = gtk_label_new("HP: ");
    gtk_widget_set_name(pokemon_labels1[0], "hp_label");
    pokemon_labels1[1] = gtk_image_new();
    
    pokemon_labels1[2] = gtk_label_new("Info: ");
    gtk_widget_set_name(pokemon_labels1[2], "energy_label");

    for ( int label = 0; label < 3; ++label )
        gtk_grid_attach(GTK_GRID(grid), pokemon_labels1[label], 3, label + 1, 1, 1);

    pokemon_labels2[0] = gtk_label_new("HP: ");
    gtk_widget_set_name(pokemon_labels2[0], "hp_label");
    pokemon_labels2[1] = gtk_image_new();
    
    pokemon_labels2[2] = gtk_label_new("Info: ");
    gtk_widget_set_name(pokemon_labels2[2], "energy_label");

    for ( int label = 0; label < 3; ++label )
        gtk_grid_attach(GTK_GRID(grid), pokemon_labels2[label], 0, label + 4, 1, 1);

    attacks_info_label = gtk_label_new("-");
    gtk_widget_set_name(attacks_info_label, "attacks_info");
    gtk_grid_attach(GTK_GRID(grid), attacks_info_label, 1, 2, 2, 4);

    button_start = gtk_button_new_with_label("Start");
    g_signal_connect(button_start, "clicked", G_CALLBACK(start_clicked), NULL);

    gtk_grid_attach(GTK_GRID(grid), button_start, 2, 8, 1, 1);

    /*attacks_info_label = gtk_label_new("-");
    gtk_widget_set_name(attacks_info_label, "attacks_info");
    gtk_grid_attach(GTK_GRID(grid), attacks_info_label, 0, 8, 3, 2);*/

    g_timeout_add(33, (GSourceFunc)draw_battle_arena, (gpointer)window);

    gtk_widget_show_all(window);
}

int main(int argc, char* argv[])
{
    srand( time(NULL) );
    initialize_data();

    // Evitar seg fault
    player1 = player_create("Trainer1");
    player1->pokemon_team = choose_team(0, 0, 0);

    player2 = player_create("Trainer2");
    player2->pokemon_team = choose_team(0, 0, 0);

    pthread_mutex_init(&battle_arena_mutex, NULL);

    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.pthreadmon", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    pthread_mutex_destroy(&battle_arena_mutex);

    return status;
}
