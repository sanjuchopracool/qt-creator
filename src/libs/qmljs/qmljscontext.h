/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2011 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: Nokia Corporation (info@qt.nokia.com)
**
**
** GNU Lesser General Public License Usage
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this file.
** Please review the following information to ensure the GNU Lesser General
** Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** Other Usage
**
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
** If you have questions regarding the use of this file, please contact
** Nokia at info@qt.nokia.com.
**
**************************************************************************/

#ifndef QMLJS_CONTEXT_H
#define QMLJS_CONTEXT_H

#include "qmljs_global.h"
#include "qmljsvalueowner.h"

#include <QtCore/QSharedPointer>

namespace QmlJS {

class Document;
class Snapshot;

namespace Interpreter {

// shared among threads, completely threadsafe
// currently also safe to copy, but will be deprecated
class QMLJS_EXPORT Context
{
public:
    typedef QSharedPointer<Context> Ptr;
    typedef QHash<const Document *, QSharedPointer<const Imports> > ImportsPerDocument;

    // Context takes ownership of valueOwner
    Context(const Snapshot &snapshot, ValueOwner *valueOwner, const ImportsPerDocument &imports);
    ~Context();

    ValueOwner *valueOwner() const;
    Snapshot snapshot() const;

    const Imports *imports(const Document *doc) const;

    const ObjectValue *lookupType(const Document *doc, AST::UiQualifiedId *qmlTypeName,
                                  AST::UiQualifiedId *qmlTypeNameEnd = 0) const;
    const ObjectValue *lookupType(const Document *doc, const QStringList &qmlTypeName) const;
    const Value *lookupReference(const Value *value) const;

    QString defaultPropertyName(const ObjectValue *object) const;

private:
    Snapshot _snapshot;
    QSharedPointer<ValueOwner> _valueOwner;
    ImportsPerDocument _imports;
};

// for looking up references
class QMLJS_EXPORT ReferenceContext
{
public:
    // implicit conversion ok
    ReferenceContext(const Context *context);

    const Value *lookupReference(const Value *value);

    const Context *context() const;
    operator const Context *() const;

private:
    const Context *m_context;
    QList<const Reference *> m_references;
};


} // namespace Interpreter
} // namespace QmlJS

#endif // QMLJS_CONTEXT_H
