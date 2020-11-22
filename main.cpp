#include "MainWindow.h"

#include <QApplication>
#include <crypto++/aes.h>
#include <crypto++/rsa.h>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

}

// ЗАМЕТКИ
// QFileDialog для файлового менеджера
// crypto++ для работы с ключами и шифрованием
//

// TODO
