#include <QApplication>
#include "ExpressionWidget.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    // 创建并显示图形化窗口
    ExpressionWidget w(nullptr);
    w.show();

    return a.exec();
}