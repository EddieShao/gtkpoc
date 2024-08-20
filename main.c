/**
 * This file is part of gtkpoc.
 * 
 * gtkpoc is free software: you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation, either version 3
 * of the License, or (at your option) any later version.
 * 
 * gtkpoc is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with gtkpoc.
 * If not, see <https://www.gnu.org/licenses/>.
 */

#include <gtk/gtk.h>

#include "resources.h"
#include "resource-paths.h"
#include "ui/router.h"
#include "db/version.h"

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

    GtkNotebook *router = GTK_NOTEBOOK(gtk_builder_get_object(builder, "router"));
    if (router == NULL) {
        g_error("Could not get object \"router\" from resource: %s", RES_MAIN_UI);
    }

    gtkpoc_router_init(router);
    gtkpoc_router_navigate(ROUTE_HOME); // might redundant nav to current page

    gtk_window_set_child(window, GTK_WIDGET(router));
    g_object_unref(builder);
}

static void activate(GtkApplication *app) {
    g_resources_register(sgsm_get_resource());
    GtkWindow *window = init_window(app);
    init_css();
    init_ui(window);
    gtk_window_present(window);
}

int main(int argc, char *argv[]) {
    g_print("SQLite3 version: %s\n", gtkpoc_sqlite_version());

    GtkApplication *app = gtk_application_new("com.eddieshao.gtkpoc", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
