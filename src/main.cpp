#include "TVController.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Ui_TVController controller{};
    TVController window(&controller);

    window.show();
    return QApplication::exec();
}
