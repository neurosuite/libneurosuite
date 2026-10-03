/*
Copyright (C) 2012 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
*/

#include "qhelpviewer.h"
#include <QDesktopServices>
#include <QDialogButtonBox>
#include <QVBoxLayout>

#ifdef NEUROSUITE_HAVE_WEBENGINE
#include <QWebEnginePage>
#include <QWebEngineView>

namespace
{
// Keeps navigation inside the handbook in the viewer and hands every
// other link (http, mailto, ...) to the system browser.
class QHelpViewerPage : public QWebEnginePage
{
  public:
    explicit QHelpViewerPage(QObject* parent = nullptr): QWebEnginePage(parent) {}

  protected:
    bool acceptNavigationRequest(const QUrl& url, NavigationType type, bool isMainFrame) override
    {
        if (type == NavigationTypeLinkClicked && !url.isLocalFile())
        {
            QDesktopServices::openUrl(url);
            return false;
        }
        return QWebEnginePage::acceptNavigationRequest(url, type, isMainFrame);
    }
};
} // namespace
#else
#include <QTextBrowser>
#endif

QHelpViewer::QHelpViewer(QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Handbook"));
    QVBoxLayout* lay = new QVBoxLayout;

#ifdef NEUROSUITE_HAVE_WEBENGINE
    QWebEngineView* view = new QWebEngineView;
    view->setPage(new QHelpViewerPage(view));
    mView = view;
#else
    QTextBrowser* view = new QTextBrowser;
    view->setOpenExternalLinks(true);
    mView = view;
#endif

    lay->addWidget(mView);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Close);
    lay->addWidget(buttonBox);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    setLayout(lay);
    resize(800, 600);
}

QHelpViewer::~QHelpViewer()
{
}

void QHelpViewer::setHtml(const QString& filename, const QString& anchor)
{
    QUrl url = QUrl::fromLocalFile(filename);
    if (!anchor.isEmpty())
        url.setFragment(anchor);

#ifdef NEUROSUITE_HAVE_WEBENGINE
    static_cast<QWebEngineView*>(mView)->load(url);
#else
    static_cast<QTextBrowser*>(mView)->setSource(url);
#endif
}
