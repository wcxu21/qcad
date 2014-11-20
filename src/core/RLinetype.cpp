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
#include "RLinetype.h"
#include "RSettings.h"
#include "RMetaTypes.h"


RPropertyTypeId RLinetype::PropertyName;
RPropertyTypeId RLinetype::PropertyDescription;
RPropertyTypeId RLinetype::PropertyMetric;
RPropertyTypeId RLinetype::PropertyPattern;

RLinetype::RLinetype(RDocument* document) : RObject(document) {
}

RLinetype::RLinetype(RDocument* document, const RLinetypePattern& pattern)
    : RObject(document), pattern(pattern) {
}

RLinetype::~RLinetype() {
}

bool RLinetype::operator==(const RLinetype & linetype) const {
    return getName().compare(linetype.getName(), Qt::CaseInsensitive) == 0;
}

bool RLinetype::operator!=(const RLinetype & linetype) const{
    return !operator ==(linetype);
}

void RLinetype::init() {
    RLinetype::PropertyName.generateId(typeid(RLinetype), "", QT_TRANSLATE_NOOP("RLinetype", "Name"));
    RLinetype::PropertyDescription.generateId(typeid(RLinetype), "", QT_TRANSLATE_NOOP("RLinetype", "Description"));
    RLinetype::PropertyMetric.generateId(typeid(RLinetype), "", QT_TRANSLATE_NOOP("RLinetype", "Metric"));
    RLinetype::PropertyPattern.generateId(typeid(RLinetype), "", QT_TRANSLATE_NOOP("RLinetype", "Pattern"));
}

bool RLinetype::setProperty(RPropertyTypeId propertyTypeId,
    const QVariant& value, RTransaction* transaction) {

    Q_UNUSED(transaction);

    bool ret = false;
    ret = RObject::setMember(pattern.name, value, PropertyName == propertyTypeId);
    ret = RObject::setMember(pattern.description, value, PropertyDescription == propertyTypeId);
    ret = RObject::setMember(pattern.metric, value, PropertyMetric == propertyTypeId);
    ret = RObject::setMember(pattern.pattern, value, PropertyPattern == propertyTypeId);
    return ret;
}

QPair<QVariant, RPropertyAttributes> RLinetype::getProperty(
        RPropertyTypeId& propertyTypeId, bool /*humanReadable*/,
        bool /*noAttributes*/) {

    if (propertyTypeId == PropertyName) {
        return qMakePair(QVariant(pattern.name), RPropertyAttributes());
    }
    if (propertyTypeId == PropertyDescription) {
        return qMakePair(QVariant(pattern.description), RPropertyAttributes());
    }
    if (propertyTypeId == PropertyMetric) {
        return qMakePair(QVariant(pattern.metric), RPropertyAttributes());
    }
    if (propertyTypeId == PropertyPattern) {
        QVariant v;
        v.setValue(pattern.pattern);
        return qMakePair(v, RPropertyAttributes(RPropertyAttributes::List));
    }

    return qMakePair(QVariant(), RPropertyAttributes());
}

bool RLinetype::isSelectedForPropertyEditing() {
    return false;
}

bool RLinetype::isValid() const {
    return !pattern.name.isNull();
}

RLinetypePattern RLinetype::getPattern() const {
    return pattern;
}

void RLinetype::setPattern(const RLinetypePattern& p) {
    pattern = p;
}

bool RLinetype::operator<(const RLinetype & linetype) const {
    return getName().toLower() < linetype.getName().toLower();
}

void RLinetype::print(QDebug dbg) const {
    dbg.nospace() << "RLinetype(";
    RObject::print(dbg);
    dbg.nospace()
        << ", pattern: " << getPattern()
        << ")";
}

