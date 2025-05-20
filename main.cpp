#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    // Apply fusion style for a modern look
    app.setStyle(QStyleFactory::create("Fusion"));
    
    MainWindow mainWindow;
    mainWindow.show();
    
    return app.exec();
}