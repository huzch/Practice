#include <QApplication>
#include "ExpressionWidget.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    // ��������ʾͼ�λ�����
    ExpressionWidget w(nullptr);
    w.show();

    return a.exec();
}