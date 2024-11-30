#pragma once

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "ExpressionTree.h"

class ExpressionWidget : public QWidget
{
    Q_OBJECT

public:
    ExpressionWidget(QWidget* parent = nullptr)
        : QWidget(parent)
        , scene(new QGraphicsScene(this))
        , view(new QGraphicsView(scene, this))
    {
        view->setRenderHint(QPainter::Antialiasing);
        view->setRenderHint(QPainter::TextAntialiasing);
        setWindowTitle("Expression Tree Visualization");

        // �������ֹ�����
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(view);

        // �����������������ǰ׺���ʽ
        prefixInput = new QLineEdit(this);
        prefixInput->setPlaceholderText("Enter prefix expression (e.g., +AB)");
        layout->addWidget(prefixInput);

        // ������ť�����ڹ��������ǰ׺���ʽ
        buildTreeButton = new QPushButton("Build Tree", this);
        connect(buildTreeButton, &QPushButton::clicked, this, &ExpressionWidget::onBuildTreeButtonClicked);
        layout->addWidget(buildTreeButton);

        // ����������QLabel��������ʾ��׺���ʽ
        infixLabel = new QLabel(this);
        infixLabel->setText("Infix Expression: " + QString::fromStdString(tree.GetInfix()));
        layout->addWidget(infixLabel);

        // ����������������������ֵ
        varNameInput = new QLineEdit(this);
        varNameInput->setPlaceholderText("Enter variable name");
        layout->addWidget(varNameInput);

        varValueInput = new QLineEdit(this);
        varValueInput->setPlaceholderText("Enter variable value");
        layout->addWidget(varValueInput);

        // ������ť�������Ϊ������ֵ
        assignButton = new QPushButton("Assign", this);
        connect(assignButton, &QPushButton::clicked, this, &ExpressionWidget::onAssignButtonClicked);
        layout->addWidget(assignButton);

        // ������ť������������ʽ��ֵ
        valueButton = new QPushButton("Value", this);
        connect(valueButton, &QPushButton::clicked, this, &ExpressionWidget::onValueButtonClicked);
        layout->addWidget(valueButton);

        // ��ʾ������
        resultLabel = new QLabel(this);
        resultLabel->setText("Result: ");
        layout->addWidget(resultLabel);

        // �����������������Ҫ��ƫ���ı���
        diffVarInput = new QLineEdit(this);
        diffVarInput->setPlaceholderText("Enter variable for partial derivative");
        layout->addWidget(diffVarInput);

        // ������ť���������ƫ��
        diffButton = new QPushButton("Diff", this);
        connect(diffButton, &QPushButton::clicked, this, &ExpressionWidget::onDiffButtonClicked);
        layout->addWidget(diffButton);

        // ��ʾƫ�����
        diffLabel = new QLabel(this);
        diffLabel->setText("Partial Derivative: ");
        layout->addWidget(diffLabel);

        // ������ť���������г����ϲ�
        mergeConstButton = new QPushButton("Merge Const", this);
        connect(mergeConstButton, &QPushButton::clicked, this, &ExpressionWidget::onMergeConstButtonClicked);
        layout->addWidget(mergeConstButton);

        // ��ʾ�����ϲ���Ľ��
        mergeConstLabel = new QLabel(this);
        mergeConstLabel->setText("Merged Expression: ");
        layout->addWidget(mergeConstLabel);

        drawTree(tree);

        // ���ó�����С
        view->setSceneRect(0, 0, 1000, 800);
        setFixedSize(1000, 800);  // �̶����ڴ�С
    }

    ~ExpressionWidget()
    {
        delete scene;
        delete view;

        delete prefixInput;
        delete varNameInput;
        delete varValueInput;
        delete diffVarInput;

        delete buildTreeButton;
        delete assignButton;
        delete valueButton;
        delete diffButton;
        delete mergeConstButton;

        delete infixLabel;
        delete resultLabel;
        delete diffLabel;
        delete mergeConstLabel;
    }

private:
    QGraphicsScene* scene;
    QGraphicsView* view;
    
    QLineEdit* prefixInput;  // �������������ǰ׺���ʽ
    QLineEdit* varNameInput; // ������������������
    QLineEdit* varValueInput; // ����������������ֵ
    QLineEdit* diffVarInput; // �������������Ҫ��ƫ���ı���

    QPushButton* buildTreeButton;  // ��ť�����ʱ����ǰ׺���ʽ
    QPushButton* assignButton;  // ��ť�����ʱΪ������ֵ
    QPushButton* valueButton; // ��ť�����ʱ������ʽ��ֵ
    QPushButton* diffButton; // ��ť�����ʱ��ƫ��
    QPushButton* mergeConstButton; // ��ť�����ʱ���г����ϲ�

    QLabel* infixLabel;   // ������ʾ��׺���ʽ
    QLabel* resultLabel;  // ������ʾ������
    QLabel* diffLabel;  // ������ʾƫ�����
    QLabel* mergeConstLabel; // ������ʾ�����ϲ���ı��ʽ

    ExpressionTree tree;

    void drawTree(const ExpressionTree& tree)
    {
        double yOffset = 30;
        drawNode(scene, tree.GetRoot(), 460, yOffset, 200, yOffset);  // ����һ����ʼ��ˮƽ���
    }

    void drawNode(QGraphicsScene* scene, TreeNode* node, double x, double y, double xOffset, double& yOffset)
    {
        if (node == nullptr) return;

        // ���ƽڵ�ԲȦ
        QGraphicsEllipseItem* ellipse = scene->addEllipse(x - 20, y - 20, 40, 40, QPen(Qt::black), QBrush(Qt::white));

        // ���ƽڵ��ı�
        QGraphicsTextItem* textItem = scene->addText(QString::fromStdString(node->_isCh ? std::string(1, node->_ch) :
            node->_isFunc ? node->_func :
            to_string((int)node->_num)),
            QFont("Arial", 12));
        textItem->setPos(x - 15, y - 15);

        // �ݹ�����ӽڵ�
        double leftX = x - xOffset;
        double rightX = x + xOffset;
        double newYOffset = y + 60;

        // �����ӽڵ�������̬����ÿ���ڵ�֮��ļ��
        if (node->_left != nullptr) {
            drawEdge(scene, x, y, leftX, newYOffset);
            drawNode(scene, node->_left, leftX, newYOffset, xOffset / 1.5, yOffset);
        }
        if (node->_right != nullptr) {
            drawEdge(scene, x, y, rightX, newYOffset);
            drawNode(scene, node->_right, rightX, newYOffset, xOffset / 1.5, yOffset);
        }
    }

    void drawEdge(QGraphicsScene* scene, double x1, double y1, double x2, double y2)
    {
        scene->addLine(x1, y1, x2, y2, QPen(Qt::black));
    }

    void onBuildTreeButtonClicked()  // ������ť����ۺ���
    {
        QString prefix = prefixInput->text();  // ��ȡ������е�ǰ׺���ʽ�ַ���
        if (prefix.isEmpty()) {
            return;
        }

        // ����ǰ׺���ʽ��������
        
        tree = ExpressionTree(prefix.toStdString());   // �������Ѿ���һ����������ǰ׺���ʽ������

        // ������ʾ��׺���ʽ
        infixLabel->setText("Infix Expression: " + QString::fromStdString(tree.GetInfix()));

        // �������Ŀ��ӻ�
        scene->clear();
        drawTree(tree);
    }

    void onAssignButtonClicked()  // ��ֵ��ť����ۺ���
    {
        QString varName = varNameInput->text();  // ��ȡ������
        QString varValue = varValueInput->text();  // ��ȡ����ֵ

        if (varName.isEmpty() || varValue.isEmpty()) {
            return;
        }

        // ������ֵ�������е���Ӧ�ڵ�
        char varChar = varName.toStdString()[0];
        tree.Assign(varChar, std::stod(varValue.toStdString()));

        
        // ������ʾ��׺���ʽ
        infixLabel->setText("Infix Expression: " + QString::fromStdString(tree.GetInfix()));

        // �������Ŀ��ӻ�
        scene->clear();
        drawTree(tree);
    }

    void onValueButtonClicked()  // ��ֵ��ť����ۺ���
    {
        // ������ʽ��ֵ
        DATATYPE result = tree.Value();

        // ��ʾ���
        resultLabel->setText("Result: " + QString::number(result));
    }

    void onDiffButtonClicked()  // ��ƫ����ť����ۺ���
    {
        // ��ȡƫ������
        QString diffVar = diffVarInput->text();

        if (diffVar.isEmpty()) {
            return;
        }

        // ת��������Ϊchar
        char varChar = diffVar.toStdString()[0];

        // ����ƫ����
        tree.Diff(varChar);

        // ������ʾƫ�����ʽ
        diffLabel->setText("Partial Derivative: " + QString::fromStdString(tree.GetInfix()));

        // �������Ŀ��ӻ�
        scene->clear();
        drawTree(tree);
    }

    void onMergeConstButtonClicked()  // �����ϲ���ť����ۺ���
    {
        // ִ�г����ϲ�����
        tree.MergeConst();

        // ������ʾ�ϲ������׺���ʽ
        mergeConstLabel->setText("Merged Expression: " + QString::fromStdString(tree.GetInfix()));

        // �������Ŀ��ӻ�
        scene->clear();
        drawTree(tree);
    }
};
