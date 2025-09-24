#include <stdio.h>
#include <gtk/gtk.h>

#include "common.inl"

int count = 0;

void end_program(GtkWidget* widget, gpointer ptr)
{
	gtk_main_quit();
}

void count_button(GtkWidget* widget, gpointer ptr)
{
	char buffer[32];
	count++;
	snprintf(buffer, sizeof(buffer), "Button pressed %d times", count);
	gtk_label_set_text(GTK_LABEL(ptr), buffer);
}

gboolean app_update(gpointer ptr)
{
    UNUSED(ptr);
    handleEvents();
    return true;
}

int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);
	GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_present(GTK_WINDOW(win)); // I think this should bring the window to the foreground, but it's broken on mac?
	// gtk_container_set_border_width(GTK_CONTAINER(win), 10);

	GtkWidget* btn = gtk_button_new_with_label("Close window");
	g_signal_connect(btn, "clicked", G_CALLBACK(end_program), NULL);
	g_signal_connect(win, "delete_event", G_CALLBACK(end_program), NULL);
	
	GtkWidget* label = gtk_label_new("My Label");

	GtkWidget* btn2 = gtk_button_new_with_label("Increment Counter");
	g_signal_connect(btn2, "clicked", G_CALLBACK(count_button), label);

	// menu bar
//	GtkWidget* menu_bar = gtk_menu_bar_new();

	GtkWidget* vbox = gtk_vbox_new(false, 0);

    createMenuBar(vbox);

//	gtk_box_pack_start(GTK_BOX(vbox), menu_bar, false, false, 0);
	gtk_box_pack_start(GTK_BOX(vbox), btn2, true, false, 5);
	gtk_box_pack_start(GTK_BOX(vbox), label, true, false, 5);
	gtk_box_pack_start(GTK_BOX(vbox), btn, true, false, 5);
	gtk_container_add(GTK_CONTAINER(win), vbox);

	// menu content
//	GtkWidget* file_mi = gtk_menu_item_new_with_label("File");
//	gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), file_mi);
//
//	GtkWidget* file_menu = gtk_menu_new();
//	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_mi), file_menu);
//
//	GtkWidget* quit_mi = gtk_menu_item_new_with_label("Quit");
//	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), quit_mi);
//	g_signal_connect(quit_mi, "activate", G_CALLBACK(end_program), NULL);

    g_timeout_add(16, app_update, NULL);
	gtk_widget_show_all(win);
	gtk_main();
	return 0;
}
