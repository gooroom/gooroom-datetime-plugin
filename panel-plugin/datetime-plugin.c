/*
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#ifdef HAVE_MATH_H
#include <math.h>
#endif

#include "datetime-plugin.h"

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include <glib-object.h>
#include <libxfce4ui/libxfce4ui.h>
#include <libxfce4util/libxfce4util.h>
#include <libxfce4panel/xfce-panel-plugin.h>


#define DEFAULT_CLOCK_FORMAT "%P %I: %M"


struct _DateTimePluginClass
{
  XfcePanelPluginClass __parent__;
};

/* plugin structure */
struct _DateTimePlugin
{
	XfcePanelPlugin      __parent__;

	GtkWidget       *button;
	GtkWidget       *popup_window;
	GtkWidget       *clock_label;
	GtkWidget       *calendar;

	guint            timeout_id;
};

/* define the plugin */
XFCE_PANEL_DEFINE_PLUGIN (DateTimePlugin, datetime_plugin)


static gboolean
on_popup_window_closed (gpointer data)
{
	DateTimePlugin *plugin = DATETIME_PLUGIN (data);

	gtk_widget_destroy (plugin->popup_window);

	plugin->popup_window = NULL;

	xfce_panel_plugin_block_autohide (XFCE_PANEL_PLUGIN (plugin), FALSE);
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (plugin->button), FALSE);

	return TRUE;
}

static gboolean
on_popup_key_press_event (GtkWidget *widget, GdkEventKey *event, gpointer data)
{
	if (event->type == GDK_KEY_PRESS && event->keyval == GDK_Escape) {
		on_popup_window_closed (data);
		return TRUE;
	}

	return FALSE;
}

static void
on_popup_window_realized (GtkWidget *widget, gpointer data)
{
	gint x, y;
	GDateTime *dt;

	DateTimePlugin *plugin = DATETIME_PLUGIN (data);

	dt = g_date_time_new_now_local ();

	gtk_calendar_select_month (GTK_CALENDAR (plugin->calendar),
								g_date_time_get_month (dt) - 1,
								g_date_time_get_year (dt));

	gtk_calendar_select_day (GTK_CALENDAR (plugin->calendar), g_date_time_get_day_of_month (dt));

	g_date_time_unref (dt);

	xfce_panel_plugin_position_widget (XFCE_PANEL_PLUGIN (plugin), widget, plugin->button, &x, &y);
	gtk_window_move (GTK_WINDOW (widget), x, y);
}

static GtkWidget *
popup_datetime_window (DateTimePlugin *plugin)
{
	GError    *error = NULL;
	GtkWidget *window;

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_type_hint (GTK_WINDOW (window), GDK_WINDOW_TYPE_HINT_UTILITY);
    gtk_window_set_decorated (GTK_WINDOW (window), FALSE);
    gtk_window_set_resizable (GTK_WINDOW (window), FALSE);
    gtk_window_set_skip_taskbar_hint (GTK_WINDOW (window), TRUE);
    gtk_window_set_skip_pager_hint(GTK_WINDOW (window), TRUE);
    gtk_window_set_keep_above (GTK_WINDOW (window), TRUE);
    gtk_window_stick(GTK_WINDOW (window));
    gtk_window_set_screen (GTK_WINDOW (window), gtk_widget_get_screen (GTK_WIDGET (plugin)));

	GtkWidget *main_vbox = gtk_vbox_new (FALSE, 0);
	gtk_container_add (GTK_CONTAINER (window), main_vbox);
	gtk_widget_show (main_vbox);

	GtkWidget *ebox = gtk_event_box_new ();
	gtk_widget_set_name (ebox, "panel-popup-window-frame");
	gtk_box_pack_start (GTK_BOX (main_vbox), ebox, FALSE, FALSE, 0);
	gtk_widget_show (ebox);

	GtkWidget *alignment = gtk_alignment_new (0.0, 0.5, 0.0, 0.0);
	gtk_alignment_set_padding (GTK_ALIGNMENT (alignment), 5, 5, 5, 5);
	gtk_container_add (GTK_CONTAINER (ebox), alignment);
	gtk_widget_show (alignment);

	GtkWidget *title = gtk_label_new (NULL);
	gtk_label_set_markup (GTK_LABEL (title), _("<big><b>Date &amp; Time</b></big>"));
	gtk_label_set_justify (GTK_LABEL (title), GTK_JUSTIFY_LEFT);
	gtk_container_add (GTK_CONTAINER (alignment), title);
	gtk_widget_show (title);

	alignment = gtk_alignment_new (0.5, 0.5, 1.0, 1.0);
	gtk_alignment_set_padding (GTK_ALIGNMENT (alignment), 10, 10, 10, 10);
	gtk_box_pack_start (GTK_BOX (main_vbox), alignment, FALSE, FALSE, 0);
	gtk_widget_show (alignment);

	plugin->calendar = gtk_calendar_new ();
	gtk_calendar_set_display_options (GTK_CALENDAR (plugin->calendar),
                                      GTK_CALENDAR_SHOW_HEADING
                                      | GTK_CALENDAR_SHOW_DAY_NAMES
                                      | GTK_CALENDAR_SHOW_WEEK_NUMBERS);
	gtk_container_add (GTK_CONTAINER (alignment), plugin->calendar);

	gtk_widget_set_size_request (window, 256, -1);
	gtk_widget_show (plugin->calendar);

	g_signal_connect (G_OBJECT (window), "realize", G_CALLBACK (on_popup_window_realized), plugin);
	g_signal_connect_swapped (G_OBJECT (window), "delete-event", G_CALLBACK (on_popup_window_closed), plugin);
	g_signal_connect (G_OBJECT (window), "key-press-event", G_CALLBACK (on_popup_key_press_event), plugin);
	g_signal_connect_swapped (G_OBJECT (window), "focus-out-event", G_CALLBACK (on_popup_window_closed), plugin);

	gtk_widget_show_all (window);

	xfce_panel_plugin_block_autohide (XFCE_PANEL_PLUGIN (plugin), TRUE);
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (plugin->button), TRUE);

	return window;
}

static gboolean
on_plugin_button_pressed (GtkWidget *widget, GdkEventButton *event, gpointer data)
{
	DateTimePlugin *plugin = DATETIME_PLUGIN (data);

	if (event->button == 1 || event->button == 2) {
		if (event->type == GDK_BUTTON_PRESS) {
			if (plugin->popup_window != NULL) {
				on_popup_window_closed (plugin);
			} else {
				plugin->popup_window = popup_datetime_window (plugin);
			}

			return TRUE;
		}
	}

	/* bypass GTK_TOGGLE_BUTTON's handler and go directly to the plugin's one */
	return (*GTK_WIDGET_CLASS (datetime_plugin_parent_class)->button_press_event) (GTK_WIDGET (plugin), event);
}

static void
datetime_plugin_reposition_calendar (DateTimePlugin *plugin)
{
	gint x, y;

	xfce_panel_plugin_position_widget (XFCE_PANEL_PLUGIN (plugin),
			GTK_WIDGET (plugin->popup_window), NULL, &x, &y);

	gtk_window_move (GTK_WINDOW (plugin->popup_window), x, y);
}

static gboolean
datetime_plugin_size_changed (XfcePanelPlugin *panel_plugin, gint size)
{
	DateTimePlugin *plugin = DATETIME_PLUGIN (panel_plugin);

	if (xfce_panel_plugin_get_mode (panel_plugin) == XFCE_PANEL_PLUGIN_MODE_HORIZONTAL) {
		gtk_widget_set_size_request (GTK_WIDGET (panel_plugin), -1, size);
	} else {
		gtk_widget_set_size_request (GTK_WIDGET (panel_plugin), size, -1);
	}

	if (plugin->popup_window != NULL && gtk_widget_get_visible (GTK_WIDGET (plugin->popup_window)))
		datetime_plugin_reposition_calendar (plugin);

	return TRUE;
}

static void
datetime_plugin_mode_changed (XfcePanelPlugin *plugin, XfcePanelPluginMode mode)
{
	datetime_plugin_size_changed (plugin, xfce_panel_plugin_get_size (plugin));
}


static gboolean
date_clock_label_update (gpointer data)
{
	gchar *str, *format;
	GDateTime *dt;

	DateTimePlugin *plugin = DATETIME_PLUGIN (data);

	/* update clock */
	dt = g_date_time_new_now_local ();
	format = g_date_time_format (dt, DEFAULT_CLOCK_FORMAT);
	str = g_strdup_printf ("<b><big>%s</big></b>", format);
	gtk_label_set_markup (GTK_LABEL (plugin->clock_label), str);
	g_free (format);
	g_free (str);

	g_date_time_unref (dt);

	return TRUE;
}

static void
datetime_plugin_free_data (XfcePanelPlugin *panel_plugin)
{
	DateTimePlugin *plugin = DATETIME_PLUGIN (panel_plugin);

	if (plugin->popup_window)
		gtk_widget_destroy (plugin->popup_window);

	if (G_LIKELY (plugin->timeout_id != 0))
		g_source_remove (plugin->timeout_id);
}

static void
datetime_plugin_init (DateTimePlugin *plugin)
{
	plugin->button       = NULL;
	plugin->clock_label  = NULL;

	plugin->button = xfce_panel_create_toggle_button ();
	gtk_widget_set_name (plugin->button, "gooroom-plugin-button");
	xfce_panel_plugin_add_action_widget (XFCE_PANEL_PLUGIN (plugin), plugin->button);
	gtk_container_add (GTK_CONTAINER (plugin), plugin->button);

	plugin->clock_label = gtk_label_new (NULL);
	gtk_label_set_justify (GTK_LABEL (plugin->clock_label), GTK_JUSTIFY_CENTER);
	gtk_container_add (GTK_CONTAINER (plugin->button), plugin->clock_label);
	gtk_widget_show_all (plugin->button);

	g_signal_connect (G_OBJECT (plugin->button), "button-press-event", G_CALLBACK (on_plugin_button_pressed), plugin);
}

static void
datetime_plugin_construct (XfcePanelPlugin *panel_plugin)
{
	GtkWidget *image;

	DateTimePlugin *plugin = DATETIME_PLUGIN (panel_plugin);

	xfce_textdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR, "UTF-8");

	date_clock_label_update (plugin);

	// update time label per 1 sec
	plugin->timeout_id = g_timeout_add_seconds_full (G_PRIORITY_DEFAULT, 1,
                                                     date_clock_label_update, plugin, NULL);
}

static void
datetime_plugin_class_init (DateTimePluginClass *klass)
{
	XfcePanelPluginClass *plugin_class;

	plugin_class = XFCE_PANEL_PLUGIN_CLASS (klass);
	plugin_class->construct = datetime_plugin_construct;
	plugin_class->free_data = datetime_plugin_free_data;
	plugin_class->size_changed = datetime_plugin_size_changed;
	plugin_class->mode_changed = datetime_plugin_mode_changed;
}
