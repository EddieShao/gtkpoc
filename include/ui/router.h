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

enum Route_Id {
    ROUTE_HOME,
    ROUTE_DB_TEST,
    NUM_ROUTES
};

/**
 * Create and populate [nav_host] widget with all routes.
 * 
 * @param nav_host Widget to use as the navigation host.
 */
void gtkpoc_router_init(GtkNotebook *nav_host);

/**
 * Navigate to [route].
 * 
 * @param route ID of the route to navigate to.
 */
void gtkpoc_router_navigate(enum Route_Id route);
