/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/

#pragma once

#include "clangtool.h"

namespace ClangTools {
namespace Internal {

class DiagnosticFilterModel;
class ClangToolsDiagnosticModel;
class DiagnosticView;
class Diagnostic;

const char ClangStaticAnalyzerPerspectiveId[] = "ClangStaticAnalyzer.Perspective";
const char ClangStaticAnalyzerDockId[]        = "ClangStaticAnalyzer.Dock";

class ClangStaticAnalyzerTool final : public ClangTool
{
    Q_OBJECT

public:
    ClangStaticAnalyzerTool();

    static ClangStaticAnalyzerTool *instance();

    void startTool(bool askUserForFileSelection) final;

    QList<Diagnostic> read(const QString &,
                           const QString &logFilePath,
                           QString *errorMessage) const final;

private:
    void handleStateUpdate() final;

    void updateRunActions();

    DiagnosticFilterModel *m_diagnosticFilterModel = nullptr;

    QAction *m_goBack = nullptr;
    QAction *m_goNext = nullptr;
};

} // namespace Internal
} // namespace ClangTools
