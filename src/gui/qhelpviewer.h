/*
Copyright (C) 2012 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
*/

#ifndef QHELPVIEWER_H
#define QHELPVIEWER_H
#include <QDialog>
#include <QUrl>

#include "libneurosuite_export.h"

class NEUROSUITE_EXPORT QHelpViewer : public QDialog
{
    Q_OBJECT
  public:
    explicit QHelpViewer(QWidget* parent);
    ~QHelpViewer();
    void setHtml(const QString& filename, const QString& anchor = QString());

  private:
    // Either a QWebEngineView or a QTextBrowser, depending on how the
    // library was built. Kept as QWidget so the public header does not
    // depend on QtWebEngine.
    QWidget* mView;
};

#endif // QHELPVIEWER_H
