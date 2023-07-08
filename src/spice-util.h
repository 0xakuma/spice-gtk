/*
   Copyright (C) 2010 Red Hat, Inc.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, see <http://www.gnu.org/licenses/>.
*/
#ifndef SPICE_UTIL_H
#define SPICE_UTIL_H

#include <glib-object.h>

G_BEGIN_DECLS

SPICE_GTK_AVAILABLE_IN_ALL
void spice_util_set_debug(gboolean enabled);
SPICE_GTK_AVAILABLE_IN_ALL
gboolean spice_util_get_debug(void);
SPICE_GTK_AVAILABLE_IN_ALL
const gchar *spice_util_get_version_string(void);
SPICE_GTK_AVAILABLE_IN_0_8
gulong spice_g_signal_connect_object(gpointer instance,
                                     const gchar *detailed_signal,
                                     GCallback c_handler,
                                     gpointer gobject,
                                     GConnectFlags connect_flags);
SPICE_GTK_AVAILABLE_IN_0_11
gchar* spice_uuid_to_string(const guint8 uuid[16]);

#define SPICE_DEBUG(fmt, ...)                                   \
    do {                                                        \
        if (G_UNLIKELY(spice_util_get_debug()))                 \
            g_debug(G_STRLOC " " fmt, ## __VA_ARGS__);          \
    } while (0)


#define SPICE_RESERVED_PADDING (10 * sizeof(void*)) GLIB_DEPRECATED_MACRO

G_END_DECLS

#endif /* SPICE_UTIL_H */
