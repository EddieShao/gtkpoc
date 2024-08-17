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
