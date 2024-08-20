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

#include "ui/router.h"
#include "ui/route/db-test.h"
#include "ui/route/home.h"

// order of elements MUST match order of Route_Id enum.
static GtkWidget *routes[NUM_ROUTES];
static GtkNotebook *_nav_host;

static GtkWidget *build_route(enum Route_Id route_id) {
    GtkWidget *route;

    switch (route_id) {
    case ROUTE_HOME:
        route = gtkpoc_route_home_new();
        break;
    case ROUTE_DB_TEST:
        route = gtkpoc_route_db_test_new();
        break;
    default:
        g_error("Invalid route ID: %d", route_id);
    }

    return route;
}

void gtkpoc_router_init(GtkNotebook *nav_host) {
    _nav_host = nav_host;
    
    for (int i = 0; i < NUM_ROUTES; i++) {
        GtkWidget *route = build_route(i);
        routes[i] = route;
        gtk_notebook_append_page(nav_host, route, NULL);
    }
}

void gtkpoc_router_navigate(enum Route_Id route_id) {
    if (route_id < 0 || route_id >= NUM_ROUTES) {
        g_error("Invalid route ID: %d", route_id);
    }

    if (gtk_notebook_get_current_page(_nav_host) == (int)route_id) {
        g_warning("Navigating to the current page is redundant: %d", route_id);
        return;
    }

    gtk_notebook_set_current_page(_nav_host, route_id);
}
