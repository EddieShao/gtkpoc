#include <gtk/gtk.h>

#include "resources.h"
#include "resource-paths.h"

static GtkWindow *init_window(GtkApplication *app) {
    GtkWindow *window = GTK_WINDOW(gtk_application_window_new(app));

    gtk_window_set_title(window, "GTK Proof of Concept");
    gtk_window_set_default_size(window, 1600, 900);
    
    return window;
}

static void init_css() {
    GtkCssProvider *css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_resource(css_provider, RES_STYLE_CSS);
    gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(css_provider);
}

static void init_ui(GtkWindow *window) {
    GtkBuilder *builder = gtk_builder_new_from_resource(RES_MAIN_UI);

    GtkWidget *root = GTK_WIDGET(gtk_builder_get_object(builder, "root"));
    if (root == NULL) {
        g_error("Could not get object \"root\" from resource: %s", RES_MAIN_UI);
    }

    // TODO: do UI initialization here

    gtk_window_set_child(window, root);
    g_object_unref(builder);
}

static void activate(GtkApplication *app, gpointer user_data) {
    (void)user_data; // unused

    GtkWindow *window;

    g_resources_register(sgsm_get_resource());
    window = init_window(app);
    init_css();
    init_ui(window);

    gtk_window_present(window);
}

int main(int argc, char *argv[]) {
    GtkApplication *app = gtk_application_new("com.eddieshao.gtkpoc", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
