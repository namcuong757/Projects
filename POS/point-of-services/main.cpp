// Micah Johnson
// Jorge Munoz
// Laijy Loiseau
// Nam Cuong Tran
// Nathan Ware
// Sydney Corrigan
#include "mainwindow.h"
#include "stylehelper.h"
#include <QApplication>
#include <dbmanager.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setStyle("Dark.qss");
    StyleHelper::setStyle("Dark.qss");
    dbmanager("QPSQL","postgres", "namcuong757","Mypassword@1");

    MainWindow w;
    w.show();

    return a.exec();
}
