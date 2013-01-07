/*
    location-supl-fix.c - Fix A-GPS location supl server
    Copyright (C) 2013  Pali Rohár <pali.rohar@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <glib.h>
#include <glib/gprintf.h>
#include <gtk/gtk.h>
#include <hildon/hildon.h>
#include <gconf/gconf-client.h>

#define NOKIA_SERVER "supl.nokia.com"
#define GOOGLE_SERVER "supl.google.com"
#define SUPL_SERVER "/system/nokia/location/supl/server"
#define SUPL_ASKVALUE "/system/nokia/location/supl/askvalue"

#define QUESTION "A-GPS location supl server is set to " NOKIA_SERVER " which does not working anymore. Do you want to set A-GPS location supl server to alternative " GOOGLE_SERVER " ? Without valid supl server A-GPS will not work!"
#define RESPONSE_YES "Yes (always)"
#define RESPONSE_NO "No (never)"
#define RESPONSE_APPLY "Yes (for now)"
#define RESPONSE_CLOSE "No (for now)"

int main(int argc, char * argv[]) {

	gint ret;
	gchar * server;
	GtkWidget * dialog;
	GConfClient * gconf;

	hildon_gtk_init(&argc, &argv);

	gconf = gconf_client_get_default();
	if ( ! gconf )
		return 0;

	server = gconf_client_get_string(gconf, SUPL_SERVER, NULL);
	if ( g_strcmp0(server, NOKIA_SERVER) != 0 )
		return 0;

	ret = gconf_client_get_int(gconf, SUPL_ASKVALUE, NULL);

	if ( ret == 0 ) {

		dialog = hildon_note_new_confirmation_add_buttons(NULL, QUESTION, RESPONSE_YES, GTK_RESPONSE_YES, RESPONSE_NO, GTK_RESPONSE_NO, RESPONSE_APPLY, GTK_RESPONSE_APPLY, RESPONSE_CLOSE, GTK_RESPONSE_CLOSE, NULL);
		if ( ! dialog )
			return 0;

		ret = gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);

	}

	if ( ret == GTK_RESPONSE_YES || ret == GTK_RESPONSE_APPLY )
		gconf_client_set_string(gconf, SUPL_SERVER, GOOGLE_SERVER, NULL);

	if ( ret == GTK_RESPONSE_YES || ret == GTK_RESPONSE_NO )
		gconf_client_set_int(gconf, SUPL_ASKVALUE, ret, NULL);

	return 0;

}
