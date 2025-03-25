#include <QApplication>
#include "MainWindow.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;

    mainWindow.show();

    return app.exec();
}
/* Pour compiler :
cmake -G "MinGW Makefiles" .
cmake --build .
.\main.exe
*/