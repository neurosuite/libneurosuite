#include <QApplication>
#include <qhelpviewer.h>
#include <utilities.h>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QHelpViewer viewer(nullptr);
    return 0;
}
