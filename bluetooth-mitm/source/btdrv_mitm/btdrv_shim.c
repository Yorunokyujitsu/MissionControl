/*
 * Copyright (C) 2020 ndeadly
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "btdrv_shim.h"
#include <stratosphere/sf/sf_mitm_dispatch.h>

Result btdrvInitializeBluetoothFwd(Service* srv, Handle *out_handle) {
    return serviceMitmDispatch(srv, 1, 
        .out_handle_attrs = { SfOutHandleAttr_HipcCopy },
        .out_handles = out_handle,
    );
}

Result btdrvFinalizeBluetoothFwd(Service* srv) {
    return serviceMitmDispatch(srv, 4);
}

Result btdrvInitializeHidFwd(Service* srv, Handle *out_handle, u16 version) {
    return serviceMitmDispatchIn(srv, 16, version,
        .out_handle_attrs = { SfOutHandleAttr_HipcCopy },
        .out_handles = out_handle,
    );
}

Result btdrvWriteHidDataFwd(Service* srv, const BtdrvAddress *address, const BtdrvHidReport *data) {
    return serviceMitmDispatchIn(srv, 19, *address,
        .buffer_attrs = { SfBufferAttr_FixedSize | SfBufferAttr_HipcPointer | SfBufferAttr_In },
        .buffers = { {data, sizeof(BtdrvHidReport)} }
    );
}

Result btdrvFinalizeHidFwd(Service* srv) {
    return serviceMitmDispatch(srv, 26);
}

Result btdrvRegisterHidReportEventFwd(Service* srv, Handle *out_handle) {
    return serviceMitmDispatch(srv, hosversionBefore(4, 0, 0) ? 36 : 37,
        .out_handle_attrs = { SfOutHandleAttr_HipcCopy },
        .out_handles = out_handle,
    );
}

Result btdrvGetHidReportEventInfoFwd(Service* srv, Handle *out_handle) {
    return serviceMitmDispatch(srv, 38,
        .out_handle_attrs = { SfOutHandleAttr_HipcCopy },
        .out_handles = out_handle,
    );
}

Result btdrvInitializeBleFwd(Service* srv, Handle *out_handle) {
    return serviceMitmDispatch(srv, 46, 
        .out_handle_attrs = { SfOutHandleAttr_HipcCopy },
        .out_handles = out_handle,
    );
}

Result btdrvFinalizeBleFwd(Service* srv) {
    return serviceMitmDispatch(srv, 49);
}