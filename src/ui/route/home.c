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
