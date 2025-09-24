#include <stdio.h>
#include <gtk/gtk.h>

#include "common.h"

static int count = 0;

void quitApp(GtkWidget* widget, gpointer ptr)
{
    UNUSED(widget);
    UNUSED(ptr);
	gtk_main_quit();
}

void doIncrement(GtkWidget* widget, gpointer ptr)
{
    UNUSED(widget);
	char buffer[32];
	count++;
	snprintf(buffer, sizeof(buffer), "Button pressed %d times", count);
	gtk_label_set_text(GTK_LABEL(ptr), buffer);
}

gboolean updateApp(gpointer ptr)
{
    UNUSED(ptr);
    exampleEventHandler();
    return true;
}

int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);
	GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_present(GTK_WINDOW(window)); // I think this should bring the window to the foreground, but it appears to be broken on mac.
	// gtk_container_set_border_width(GTK_CONTAINER(win), 10);

	GtkWidget* closeButton = gtk_button_new_with_label("Close Window");
	g_signal_connect(closeButton, "clicked", G_CALLBACK(quitApp), NULL);
	g_signal_connect(window, "delete_event", G_CALLBACK(quitApp), NULL);
	
	GtkWidget* incrementLabel = gtk_label_new("Click the 'Increment Counter' button");
	GtkWidget* incrementButton = gtk_button_new_with_label("Increment Counter");
	g_signal_connect(incrementButton, "clicked", G_CALLBACK(doIncrement), incrementLabel);

	// menu bar
	GtkWidget* menuBar = gtk_menu_bar_new();

    createExampleMenuBar(menuBar);

    GtkWidget* vbox = gtk_vbox_new(false, 0);
	gtk_box_pack_start(GTK_BOX(vbox), menuBar, false, false, 0);
	gtk_box_pack_start(GTK_BOX(vbox), incrementButton, true, false, 5);
	gtk_box_pack_start(GTK_BOX(vbox), incrementLabel, true, false, 5);
	gtk_box_pack_start(GTK_BOX(vbox), closeButton, true, false, 5);
	gtk_container_add(GTK_CONTAINER(window), vbox);

    g_timeout_add(16, updateApp, NULL);
	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
