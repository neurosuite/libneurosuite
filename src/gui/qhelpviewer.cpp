/*
Copyright (C) 2012 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
*/

#include "qhelpviewer.h"
#include <QVBoxLayout>
#include <QWebView>
#include <QDialogButtonBox>

QHelpViewer::QHelpViewer(QWidget *parent)
    :QDialog(parent)
{
    QVBoxLayout *lay = new QVBoxLayout;
    mView = new QWebView;
    lay->addWidget(mView);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Close);
    lay->addWidget(buttonBox);
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    setLayout(lay);
}

QHelpViewer::~QHelpViewer()
{
}

void QHelpViewer::setHtml(const QString& filename)
{
    mView->load(QUrl(filename));
}
