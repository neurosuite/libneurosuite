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
#include <QFile>
#include <QStringDecoder>
#include <QTextBrowser>

namespace
{
// The handbook pages are DocBook output without a charset declaration
// (mostly ISO-8859-1). Decode as UTF-8 when valid, else as Latin-1, the
// same fallback a web browser uses.
class QHelpBrowser : public QTextBrowser
{
  public:
    using QTextBrowser::QTextBrowser;

  protected:
    QVariant loadResource(int type, const QUrl& name) override
    {
        if (type == QTextDocument::HtmlResource && name.isLocalFile())
        {
            QFile file(name.toLocalFile());
            if (file.open(QIODevice::ReadOnly))
            {
                const QByteArray data = file.readAll();
                QStringDecoder utf8(QStringDecoder::Utf8);
                const QString text = utf8(data);
                return utf8.hasError() ? QString::fromLatin1(data) : text;
            }
        }
        return QTextBrowser::loadResource(type, name);
    }
};
} // namespace
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
    QHelpBrowser* view = new QHelpBrowser;
    view->setOpenExternalLinks(true);
    // The pages assume black text on white, independent of the desktop theme.
    QPalette pal = view->palette();
    pal.setColor(QPalette::Base, Qt::white);
    pal.setColor(QPalette::Text, Qt::black);
    view->setPalette(pal);
    view->document()->setDefaultStyleSheet(QStringLiteral("a[href] { color: #0000EE; }"));
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
