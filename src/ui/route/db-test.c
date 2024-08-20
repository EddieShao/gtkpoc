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
#include "ui/route/db-test.h"
#include "ui/router.h"

static void on_navigate_clicked(gpointer route_id) {
    gtkpoc_router_navigate(GPOINTER_TO_INT(route_id));
}

static void on_insert_clicked() {
    g_print("Making query to DB...\n");
}

GtkWidget *gtkpoc_route_db_test_new() {
    GtkBuilder *builder = gtk_builder_new_from_resource(RES_ROUTE_DB_TEST_UI);

    GtkWidget *root = GTK_WIDGET(gtk_builder_get_object(builder, "root"));
    if (root == NULL) {
        g_error("Could not get object \"root\" from resource: %s", RES_ROUTE_DB_TEST_UI);
    }

    GtkButton *nav_home = GTK_BUTTON(gtk_builder_get_object(builder, "nav-home"));
    if (nav_home == NULL) {
        g_error("Could not get object \"nav-home\" from resource: %s", RES_ROUTE_DB_TEST_UI);
    }

    GtkButton *insert = GTK_BUTTON(gtk_builder_get_object(builder, "insert"));
    if (insert == NULL) {
        g_error("Could not get object \"insert\" from resource: %s", RES_ROUTE_DB_TEST_UI);
    }

    g_signal_connect_swapped(nav_home, "clicked", G_CALLBACK(on_navigate_clicked), GINT_TO_POINTER(ROUTE_HOME));
    g_signal_connect_swapped(insert, "clicked", G_CALLBACK(on_insert_clicked), NULL);

    g_object_ref(root);
    g_object_unref(builder);

    return root;
}
