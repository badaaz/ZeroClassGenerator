#include <QApplication>

#include "FenReglage.h"
#include "FenGeneration.h"


int main(int argc, char *argv[])

{
    QApplication app(argc, argv);

    FenReglage reglage;
    reglage.show();



    return app.exec();

}
