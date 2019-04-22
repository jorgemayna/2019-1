#include<gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

static void enter_callback( GtkWidget *widget,
                            GtkWidget *entry )
{
  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
  printf ("Entry contents: %s\n", entry_text);
}

int main(int argc,char* argv[]){

    gtk_init(&argc,&argv);
    GtkWidget* window;
    GtkWidget* vbox;
    GtkWidget* entry;
    gint tmp_pos;

    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request (GTK_WIDGET (window), 700, 480);
    gtk_window_set_title (GTK_WINDOW (window), "jorge bash");
    g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit),NULL);

    vbox = gtk_box_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (window), vbox);
    gtk_widget_show (vbox);

    entry = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry), 0);
    g_signal_connect (entry, "activate",G_CALLBACK (enter_callback),entry);
    gtk_entry_set_text (GTK_ENTRY (entry), "hola :) ");
    tmp_pos = gtk_entry_get_text_length(GTK_ENTRY(entry));
    gtk_editable_insert_text (GTK_EDITABLE (entry), " mundo", -1, &tmp_pos);
    gtk_editable_select_region (GTK_EDITABLE (entry),0, gtk_entry_get_text_length(GTK_ENTRY(entry)));
    gtk_box_pack_start (GTK_BOX (vbox), entry, TRUE, TRUE, 0);
    gtk_widget_show (entry);

    gtk_widget_show(window);
    gtk_main();
    return 0;

}
