/**
 * Copyright (c) 2011-2014 by Andrew Mustun. All rights reserved.
 * 
 * This file is part of the QCAD project.
 *
 * QCAD is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QCAD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QCAD.
 */

include("../Snap.js");

/**
 * \class RestrictOff
 * \ingroup ecma_snap
 * \brief Switch off all snap restrictions.
 */
function RestrictOff(guiAction) {
    Snap.call(this, guiAction);
}

RestrictOff.prototype = new Snap();

RestrictOff.prototype.beginEvent = function() {
    Snap.prototype.beginEvent.call(this);
    var di = this.getDocumentInterface();
    di.setSnapRestriction(new RRestrictOff(di));
    this.terminate();
};
