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

#include "clock-time.h"
#include "clock-digital.h"
#include "datetime-plugin.h"
#include "datetime-window-resources.h"

#include <gtk/gtk.h>
#include <glib-object.h>
#include <libxfce4ui/libxfce4ui.h>
#include <libxfce4util/libxfce4util.h>
#include <libxfce4panel/xfce-panel-plugin.h>



#define GET_WIDGET(builder, x) GTK_WIDGET (gtk_builder_get_object (builder, x))

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
	GtkWidget       *clock;
	GtkWidget       *calendar;

	ClockTime       *time;

	GtkBuilder      *builder;
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
	if (event->type == GDK_KEY_PRESS && event->keyval == GDK_KEY_Escape) {
		on_popup_window_closed (data);
		return TRUE;
	}

	return FALSE;
}

static void
on_popup_window_realized (GtkWidget *widget, gpointer data)
{
	gint x, y;
	GDateTime *time;

	DateTimePlugin *plugin = DATETIME_PLUGIN (data);

	time = clock_time_get_time (plugin->time);

	gtk_calendar_select_month (GTK_CALENDAR (plugin->calendar),
								g_date_time_get_month (time) - 1,
								g_date_time_get_year (time));

	gtk_calendar_select_day (GTK_CALENDAR (plugin->calendar), g_date_time_get_day_of_month (time));

	g_date_time_unref (time);

	xfce_panel_plugin_position_widget (XFCE_PANEL_PLUGIN (plugin), widget, plugin->button, &x, &y);
	gtk_window_move (GTK_WINDOW (widget), x, y);
}

static GtkWidget *
on_popup_window_open (DateTimePlugin *plugin)
{
	GError    *error = NULL;
	GdkScreen *screen;
	GtkWidget *window;

    gtk_builder_add_from_resource (plugin->builder, "/kr/gooroom/datetime/plugin/datetime-window.ui", NULL);
	if (error) {
		g_error_free (error);
		return;
	}

	window = GET_WIDGET (plugin->builder, "datetime-window");
//	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_type_hint (GTK_WINDOW (window), GDK_WINDOW_TYPE_HINT_UTILITY);
	gtk_window_set_decorated (GTK_WINDOW (window), FALSE);
	gtk_window_set_resizable (GTK_WINDOW (window), FALSE);
	gtk_window_set_skip_taskbar_hint (GTK_WINDOW (window), TRUE);
	gtk_window_set_skip_pager_hint(GTK_WINDOW (window), TRUE);
	gtk_window_set_keep_above (GTK_WINDOW (window), TRUE);
	gtk_window_stick(GTK_WINDOW (window));

	screen = gtk_widget_get_screen (GTK_WIDGET (plugin->button));
	gtk_window_set_screen (GTK_WINDOW (window), screen);

#if 0
	plugin->calendar = gtk_calendar_new ();
	gtk_calendar_set_display_options (GTK_CALENDAR (plugin->calendar),
			GTK_CALENDAR_SHOW_HEADING
			| GTK_CALENDAR_SHOW_DAY_NAMES
			| GTK_CALENDAR_SHOW_WEEK_NUMBERS);

	gtk_container_add (GTK_CONTAINER (plugin->popup_window), plugin->calendar);
	gtk_widget_show (plugin->calendar);
#endif

	g_signal_connect (G_OBJECT (window), "realize", G_CALLBACK (on_popup_window_realized), plugin);
	g_signal_connect_swapped (G_OBJECT (window), "delete-event", G_CALLBACK (on_popup_window_closed), plugin);
	g_signal_connect (G_OBJECT (window), "key-press-event", G_CALLBACK (on_popup_key_press_event), plugin);
	g_signal_connect_swapped (G_OBJECT (window), "focus-out-event", G_CALLBACK (on_popup_window_closed), plugin);

	gtk_widget_show (window);

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
				plugin->popup_window = on_popup_window_open (plugin);
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
  gdouble      ratio;
  gint         ratio_size;
  gint         offset;

  if (plugin->clock == NULL)
    return TRUE;

  /* get the width:height ratio */
  g_object_get (G_OBJECT (plugin->clock), "size-ratio", &ratio, NULL);
  if (ratio > 0)
    {
      ratio_size = size;
      offset = 0;
    }
  else
    {
      ratio_size = -1;
      offset = 0;
    }

  /* set the clock size */
  if (xfce_panel_plugin_get_mode (panel_plugin) == XFCE_PANEL_PLUGIN_MODE_HORIZONTAL)
    {
      if (ratio > 0)
        {
          ratio_size = ceil (ratio_size * ratio);
          ratio_size += offset;
        }

//      gtk_widget_set_size_request (GTK_WIDGET (panel_plugin), ratio_size, size);
      gtk_widget_set_size_request (GTK_WIDGET (panel_plugin), -1, size);
    }
  else
    {
      if (ratio > 0)
        {
          ratio_size = ceil (ratio_size / ratio);
          ratio_size += offset;
        }

//      gtk_widget_set_size_request (GTK_WIDGET (panel_plugin), size, ratio_size);
      gtk_widget_set_size_request (GTK_WIDGET (panel_plugin), size, -1);
    }

  if (plugin->popup_window != NULL
      && gtk_widget_get_visible (GTK_WIDGET (plugin->popup_window)))
    datetime_plugin_reposition_calendar (plugin);

  return TRUE;
}

static void
datetime_plugin_size_ratio_changed (XfcePanelPlugin *panel_plugin)
{
	datetime_plugin_size_changed (panel_plugin, xfce_panel_plugin_get_size (panel_plugin));
}

static void
datetime_plugin_add_clock (DateTimePlugin *plugin)
{
	GtkOrientation      orientation;

	if (plugin->clock != NULL)
		gtk_widget_destroy (plugin->clock);

	/* create a new clock */
	plugin->clock = xfce_clock_digital_new (plugin->time);

	orientation = (xfce_panel_plugin_get_mode (XFCE_PANEL_PLUGIN (plugin)) == XFCE_PANEL_PLUGIN_MODE_VERTICAL) ?
					GTK_ORIENTATION_VERTICAL : GTK_ORIENTATION_HORIZONTAL;

	g_object_set (G_OBJECT (plugin->clock), "orientation", orientation, NULL);

	/* watch width/height changes */
	g_signal_connect_swapped (G_OBJECT (plugin->clock), "notify::size-ratio",
							G_CALLBACK (datetime_plugin_size_ratio_changed), plugin);

	datetime_plugin_size_changed (XFCE_PANEL_PLUGIN (plugin),
			xfce_panel_plugin_get_size (XFCE_PANEL_PLUGIN (plugin)));

	gtk_container_add (GTK_CONTAINER (plugin->button), plugin->clock);

	gtk_widget_show (plugin->clock);
}

static void
datetime_plugin_free_data (XfcePanelPlugin *panel_plugin)
{
	DateTimePlugin *plugin = DATETIME_PLUGIN (panel_plugin);

	if (plugin->popup_window)
		gtk_widget_destroy (plugin->popup_window);

	if (plugin->time)
		g_object_unref (G_OBJECT (plugin->time));

	if (plugin->builder)
		g_object_unref (G_OBJECT (plugin->builder));
}

static void
datetime_plugin_init (DateTimePlugin *plugin)
{
	GError *error        = NULL;

	plugin->clock        = NULL;
	plugin->button       = NULL;

	g_resources_register (datetime_window_get_resource ());

	plugin->builder = gtk_builder_new ();

	plugin->time = clock_time_new ();
}

static void
datetime_plugin_construct (XfcePanelPlugin *panel_plugin)
{
	GtkWidget *image;
	GtkCssProvider *css_provider;

	DateTimePlugin *plugin = DATETIME_PLUGIN (panel_plugin);

	xfce_textdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR, "UTF-8");

	plugin->button = xfce_panel_create_toggle_button ();
	gtk_widget_set_name (plugin->button, "clock-button");
	gtk_button_set_relief (GTK_BUTTON (plugin->button), GTK_RELIEF_NONE);
	gtk_container_add (GTK_CONTAINER (plugin), plugin->button);
	xfce_panel_plugin_add_action_widget (XFCE_PANEL_PLUGIN (plugin), plugin->button);
	gtk_widget_show (plugin->button);

    /* Sane default Gtk style */
	css_provider = gtk_css_provider_new ();
	gtk_css_provider_load_from_data (css_provider,
                                     "#clock-button {"
                                     "-GtkWidget-focus-padding: 0;"
                                     "-GtkWidget-focus-line-width: 0;"
                                     "-GtkButton-default-border: 0;"
                                     "-GtkButton-inner-border: 0;"
                                     "padding: 6px;"
                                     "border-width: 1px;}",
                                     -1, NULL);
	gtk_style_context_add_provider (GTK_STYLE_CONTEXT (gtk_widget_get_style_context (GTK_WIDGET (plugin->button))),
			GTK_STYLE_PROVIDER (css_provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);


	g_signal_connect (G_OBJECT (plugin->button), "button-press-event", G_CALLBACK (on_plugin_button_pressed), plugin);

	datetime_plugin_add_clock (plugin);
}

static void
datetime_plugin_class_init (DateTimePluginClass *klass)
{
	XfcePanelPluginClass *plugin_class;

	plugin_class = XFCE_PANEL_PLUGIN_CLASS (klass);
	plugin_class->construct = datetime_plugin_construct;
	plugin_class->free_data = datetime_plugin_free_data;
	plugin_class->size_changed = datetime_plugin_size_changed;
}
