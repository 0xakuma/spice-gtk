/*
   Copyright (C) 2011, 2012 Red Hat, Inc.

   Red Hat Authors:
   Hans de Goede <hdegoede@redhat.com>

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
#ifndef __SPICE_USB_DEVICE_MANAGER_H__
#define __SPICE_USB_DEVICE_MANAGER_H__

#if !defined(__SPICE_CLIENT_H_INSIDE__) && !defined(SPICE_COMPILATION)
#warning "Only <spice-client.h> can be included directly"
#endif

#include "spice-client.h"
#include <gio/gio.h>

G_BEGIN_DECLS

#define SPICE_TYPE_USB_DEVICE_MANAGER            (spice_usb_device_manager_get_type ())
#define SPICE_USB_DEVICE_MANAGER(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), SPICE_TYPE_USB_DEVICE_MANAGER, SpiceUsbDeviceManager))
#define SPICE_USB_DEVICE_MANAGER_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), SPICE_TYPE_USB_DEVICE_MANAGER, SpiceUsbDeviceManagerClass))
#define SPICE_IS_USB_DEVICE_MANAGER(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), SPICE_TYPE_USB_DEVICE_MANAGER))
#define SPICE_IS_USB_DEVICE_MANAGER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), SPICE_TYPE_USB_DEVICE_MANAGER))
#define SPICE_USB_DEVICE_MANAGER_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), SPICE_TYPE_USB_DEVICE_MANAGER, SpiceUsbDeviceManagerClass))

#define SPICE_TYPE_USB_DEVICE                    (spice_usb_device_get_type())

typedef struct _SpiceUsbDeviceManager SpiceUsbDeviceManager;
typedef struct _SpiceUsbDeviceManagerClass SpiceUsbDeviceManagerClass;
typedef struct _SpiceUsbDeviceManagerPrivate SpiceUsbDeviceManagerPrivate;

/**
 * SpiceUsbDevice:
 *
 * The #SpiceUsbDevice struct is opaque and cannot be accessed directly.
 */
typedef struct _SpiceUsbDevice SpiceUsbDevice;

/**
 * SpiceUsbDeviceManager:
 *
 * The #SpiceUsbDeviceManager struct is opaque and should not be accessed directly.
 */
struct _SpiceUsbDeviceManager
{
    GObject parent;

    /*< private >*/
    SpiceUsbDeviceManagerPrivate *priv;
    /* Do not add fields to this struct */
};

/**
 * SpiceUsbDeviceManagerClass:
 * @parent_class: Parent class.
 * @device_added: Signal class handler for the #SpiceUsbDeviceManager::device-added signal.
 * @device_removed: Signal class handler for the #SpiceUsbDeviceManager::device-removed signal.
 * @auto_connect_failed: Signal class handler for the #SpiceUsbDeviceManager::auto-connect-failed signal.
 * @device_error: Signal class handler for the #SpiceUsbDeviceManager::device_error signal.
 *
 * Class structure for #SpiceUsbDeviceManager.
 */
struct _SpiceUsbDeviceManagerClass
{
    GObjectClass parent_class;

    /* signals */
    void (*device_added) (SpiceUsbDeviceManager *manager,
                          SpiceUsbDevice *device);
    void (*device_removed) (SpiceUsbDeviceManager *manager,
                            SpiceUsbDevice *device);
    void (*auto_connect_failed) (SpiceUsbDeviceManager *manager,
                                 SpiceUsbDevice *device,
                                 GError *error);
    void (*device_error) (SpiceUsbDeviceManager *manager,
                          SpiceUsbDevice *device,
                          GError *error);
    /*< private >*/
    /*
     * If adding fields to this struct, remove corresponding
     * amount of padding to avoid changing overall struct size
     */
    gpointer _spice_reserved[10];
};

SPICE_GTK_AVAILABLE_IN_0_8
GType spice_usb_device_get_type(void);
SPICE_GTK_AVAILABLE_IN_0_8
GType spice_usb_device_manager_get_type(void);

SPICE_GTK_AVAILABLE_IN_0_8
gchar *spice_usb_device_get_description(SpiceUsbDevice *device, const gchar *format);
SPICE_GTK_AVAILABLE_IN_0_27
gconstpointer spice_usb_device_get_libusb_device(const SpiceUsbDevice *device);

SPICE_GTK_AVAILABLE_IN_0_8
SpiceUsbDeviceManager *spice_usb_device_manager_get(SpiceSession *session,
                                                    GError **err);

SPICE_GTK_AVAILABLE_IN_0_8
GPtrArray *spice_usb_device_manager_get_devices(SpiceUsbDeviceManager *manager);
SPICE_GTK_AVAILABLE_IN_0_20
GPtrArray* spice_usb_device_manager_get_devices_with_filter(SpiceUsbDeviceManager *manager,
                                                            const gchar *filter);

SPICE_GTK_AVAILABLE_IN_0_8
gboolean spice_usb_device_manager_is_device_connected(SpiceUsbDeviceManager *manager,
                                                      SpiceUsbDevice *device);
SPICE_GTK_AVAILABLE_IN_0_8
void spice_usb_device_manager_connect_device_async(SpiceUsbDeviceManager *manager,
                                                   SpiceUsbDevice *device,
                                                   GCancellable *cancellable,
                                                   GAsyncReadyCallback callback,
                                                   gpointer user_data);

SPICE_GTK_AVAILABLE_IN_0_32
void spice_usb_device_manager_disconnect_device_async(SpiceUsbDeviceManager *manager,
                                                      SpiceUsbDevice *device,
                                                      GCancellable *cancellable,
                                                      GAsyncReadyCallback callback,
                                                      gpointer user_data);

SPICE_GTK_AVAILABLE_IN_0_8
gboolean spice_usb_device_manager_connect_device_finish(SpiceUsbDeviceManager *manager,
                                                        GAsyncResult *res,
                                                        GError **err);

SPICE_GTK_AVAILABLE_IN_0_32
gboolean spice_usb_device_manager_disconnect_device_finish(SpiceUsbDeviceManager *manager,
                                                           GAsyncResult *res,
                                                           GError **err);

#ifndef SPICE_DISABLE_DEPRECATED
SPICE_GTK_DEPRECATED_IN_0_32_FOR(spice_usb_device_manager_disconnect_device_async)
void spice_usb_device_manager_disconnect_device(SpiceUsbDeviceManager *manager,
                                                SpiceUsbDevice *device);
#endif

SPICE_GTK_AVAILABLE_IN_0_10
gboolean
spice_usb_device_manager_can_redirect_device(SpiceUsbDeviceManager *manager,
                                             SpiceUsbDevice *device,
                                             GError **err);

SPICE_GTK_AVAILABLE_IN_0_32
gboolean spice_usb_device_manager_is_redirecting(SpiceUsbDeviceManager *manager);

SPICE_GTK_AVAILABLE_IN_0_38
gboolean
spice_usb_device_manager_create_shared_cd_device(SpiceUsbDeviceManager *manager,
                                                 gchar *filename,
                                                 GError **err);
SPICE_GTK_AVAILABLE_IN_0_38
gboolean
spice_usb_device_manager_is_device_shared_cd(SpiceUsbDeviceManager *manager,
                                             SpiceUsbDevice *device);

SPICE_GTK_AVAILABLE_IN_0_40
SpiceUsbDevice *
spice_usb_device_manager_allocate_device_for_file_descriptor(SpiceUsbDeviceManager *manager,
                                                             int file_descriptor,
                                                             GError **err);

G_END_DECLS

#endif /* __SPICE_USB_DEVICE_MANAGER_H__ */
