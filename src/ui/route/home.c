#include "resource-paths.h"
#include "ui/route/home.h"
#include "ui/router.h"

static void on_navigate_clicked(gpointer route_id) {
    gtkpoc_router_navigate(GPOINTER_TO_INT(route_id));
}

GtkWidget *gtkpoc_route_home_new() {
    GtkBuilder *builder = gtk_builder_new_from_resource(RES_ROUTE_HOME_UI);
    
    GtkWidget *nav_db_test = GTK_WIDGET(gtk_builder_get_object(builder, "nav-db-test"));
    if (nav_db_test == NULL) {
        g_error("Could not get object \"nav-db-test\" from resource: %s", RES_ROUTE_HOME_UI);
    }

    g_signal_connect_swapped(GTK_BUTTON(nav_db_test), "clicked", G_CALLBACK(on_navigate_clicked), GINT_TO_POINTER(ROUTE_DB_TEST));

    g_object_ref(nav_db_test);
    g_object_unref(builder);

    return nav_db_test;
}
