#include <QApplication>
#include "fenprincipale.cpp"
//#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);

    Fenprincipale fenetrePrincip;
    fenetrePrincip.setWindowState(Qt::WindowMaximized);
    fenetrePrincip.show();

//    QFile file("C:/Users/Fortune/Documents/Experience plus/ExperiencePlus/style.qss");
//    if(file.open(QFile::ReadOnly)) {
//       QString StyleSheet = QLatin1String(file.readAll());
//       fenetrePrincip.setStyleSheet(StyleSheet);
//       qDebug()<<"Open";
//    }else
//        qDebug()<<"not Open";

    app.setWindowIcon(QIcon("Image/WindowIcon.ico"));
    return app.exec();
}
