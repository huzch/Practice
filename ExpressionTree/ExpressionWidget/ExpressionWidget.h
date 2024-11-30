#pragma once

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QSplitter>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QPen>
#include <QBrush>
#include <QFont>
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

        // ����������
        auto mainLayout = new QHBoxLayout(this);

        // ʹ�� QSplitter �ָ���������
        auto splitter = new QSplitter(Qt::Horizontal, this);
        mainLayout->addWidget(splitter);

        // ��ࣺ���ʽ���Ŀ��ӻ�
        auto leftWidget = new QWidget(this);
        auto leftLayout = new QVBoxLayout(leftWidget);
        leftLayout->addWidget(view);
        splitter->addWidget(leftWidget);

        // ���ó�����С
        view->setSceneRect(0, 0, 2000, 1000);

        // �Ҳࣺ����ؼ��Ͳ�����ť
        auto rightWidget = new QWidget(this);
        auto rightLayout = new QVBoxLayout(rightWidget);
        splitter->addWidget(rightWidget);

        // ��׺���ʽ��ʾ
        auto infixLabel = new QLabel(this);
        infixLabel->setText("Infix Expression: " + QString::fromStdString(tree.GetInfix()));
        rightLayout->addWidget(infixLabel);

        // ǰ׺���ʽ����͹�����ť
        auto prefixInput = new QLineEdit(this);
        prefixInput->setPlaceholderText("Enter prefix expression (e.g., +AB)");
        rightLayout->addWidget(prefixInput);

        auto buildTreeButton = new QPushButton("Build Tree", this);
        connect(buildTreeButton, &QPushButton::clicked, [=]() {
            QString prefix = prefixInput->text();
            if (prefix.isEmpty()) {
                return;
            }
            tree = ExpressionTree(prefix.toStdString());
            infixLabel->setText("Infix Expression: " + QString::fromStdString(tree.GetInfix()));
            scene->clear();
            drawTree(tree);
            });
        rightLayout->addWidget(buildTreeButton);

        // ���ʽ��������Ͱ�ť
        auto opNameInput = new QLineEdit(this);
        opNameInput->setPlaceholderText("Enter operator name");
        rightLayout->addWidget(opNameInput);

        auto anotherPrefixInput = new QLineEdit(this);
        anotherPrefixInput->setPlaceholderText("Enter prefix expression (e.g., +CD)");
        rightLayout->addWidget(anotherPrefixInput);

        auto compoundButton = new QPushButton("Compound", this);
        connect(compoundButton, &QPushButton::clicked, [=]() {
            QString opName = opNameInput->text();
            QString anotherPrefix = anotherPrefixInput->text();
            if (opName.isEmpty() || anotherPrefix.isEmpty()) {
                return;
            }
            char opChar = opName.toStdString()[0];
            tree = Compound(opChar, tree, ExpressionTree(anotherPrefix.toStdString()));
            infixLabel->setText("Infix Expression: " + QString::fromStdString(tree.GetInfix()));
            scene->clear();
            drawTree(tree);
            });
        rightLayout->addWidget(compoundButton);

        // ��������ʾ�͸�ֵ����
        auto resultLabel = new QLabel(this);
        resultLabel->setText("Result: ");
        rightLayout->addWidget(resultLabel);

        auto varNameInput = new QLineEdit(this);
        varNameInput->setPlaceholderText("Enter variable name");
        rightLayout->addWidget(varNameInput);

        auto varValueInput = new QLineEdit(this);
        varValueInput->setPlaceholderText("Enter variable value");
        rightLayout->addWidget(varValueInput);

        auto assignButton = new QPushButton("Assign", this);
        connect(assignButton, &QPushButton::clicked, [=]() {
            QString varName = varNameInput->text();
            QString varValue = varValueInput->text();
            if (varName.isEmpty() || varValue.isEmpty()) {
                return;
            }
            char varChar = varName.toStdString()[0];
            tree.Assign(varChar, std::stod(varValue.toStdString()));
            infixLabel->setText("Infix Expression: " + QString::fromStdString(tree.GetInfix()));
            scene->clear();
            drawTree(tree);
            });
        rightLayout->addWidget(assignButton);

        auto valueButton = new QPushButton("Value", this);
        connect(valueButton, &QPushButton::clicked, [=]() {
            DATATYPE result = tree.Value();
            resultLabel->setText("Result: " + QString::number(result));
            });
        rightLayout->addWidget(valueButton);

        // ƫ�������ʾ������
        auto diffLabel = new QLabel(this);
        diffLabel->setText("Partial Derivative: ");
        rightLayout->addWidget(diffLabel);

        auto diffVarInput = new QLineEdit(this);
        diffVarInput->setPlaceholderText("Enter variable for partial derivative");
        rightLayout->addWidget(diffVarInput);

        auto diffButton = new QPushButton("Diff", this);
        connect(diffButton, &QPushButton::clicked, [=]() {
            QString diffVar = diffVarInput->text();
            if (diffVar.isEmpty()) {
                return;
            }
            char varChar = diffVar.toStdString()[0];
            tree.Diff(varChar);
            diffLabel->setText("Partial Derivative: " + QString::fromStdString(tree.GetInfix()));
            scene->clear();
            drawTree(tree);
            });
        rightLayout->addWidget(diffButton);

        // �����ϲ������ʾ�Ͱ�ť
        auto mergeConstLabel = new QLabel(this);
        mergeConstLabel->setText("Merged Expression: ");
        rightLayout->addWidget(mergeConstLabel);

        auto mergeConstButton = new QPushButton("Merge Const", this);
        connect(mergeConstButton, &QPushButton::clicked, [=]() {
            tree.MergeConst();
            mergeConstLabel->setText("Merged Expression: " + QString::fromStdString(tree.GetInfix()));
            scene->clear();
            drawTree(tree);
            });
        rightLayout->addWidget(mergeConstButton);

        // ���� splitter ��Ĭ�ϱ���
        splitter->setStretchFactor(0, 3);  // ���ռ 3
        splitter->setStretchFactor(1, 1);  // �Ҳ�ռ 1

        // ���ô��ڴ�С
        setFixedSize(1500, 800);
    }

    ~ExpressionWidget()
    {
        delete scene;
        delete view;
    }

private:
    QGraphicsScene* scene;
    QGraphicsView* view;

    ExpressionTree tree;

    // �ڵ㲼�ָ����ṹ
    struct NodePosition {
        double x;
        double y;
    };

    struct SubtreeMetrics {
        double width;   // �������
        double xOffset; // ���ڵ��ˮƽƫ��
    };

    // �ݹ����������ȼ�ˮƽƫ��
    SubtreeMetrics computeSubtreeMetrics(TreeNode* node, double nodeWidth, double gap) {
        if (!node) return { 0, 0 };

        SubtreeMetrics leftMetrics = computeSubtreeMetrics(node->_left, nodeWidth, gap);
        SubtreeMetrics rightMetrics = computeSubtreeMetrics(node->_right, nodeWidth, gap);

        // �����������������С���
        double subtreeWidth = leftMetrics.width + rightMetrics.width + gap;
        subtreeWidth = std::max(subtreeWidth, nodeWidth);

        // ���ڵ��ˮƽƫ����
        double xOffset = leftMetrics.width + gap / 2.0;

        return { subtreeWidth, xOffset };
    }

    // ����ڵ�����꣨���ֶԳ��ԣ�
    void assignNodePositions(TreeNode* node, double x, double y, double nodeWidth, double gap,
        map<TreeNode*, NodePosition>& positions, const SubtreeMetrics& metrics) {
        if (!node) return;

        // ��¼��ǰ�ڵ�λ��
        positions[node] = { x, y };

        // �ݹ鲼��������
        if (node->_left) {
            double leftX = x - metrics.xOffset;
            SubtreeMetrics leftMetrics = computeSubtreeMetrics(node->_left, nodeWidth, gap);
            assignNodePositions(node->_left, leftX, y + 60, nodeWidth, gap, positions, leftMetrics);
        }

        // �ݹ鲼��������
        if (node->_right) {
            double rightX = x + metrics.xOffset;
            SubtreeMetrics rightMetrics = computeSubtreeMetrics(node->_right, nodeWidth, gap);
            assignNodePositions(node->_right, rightX, y + 60, nodeWidth, gap, positions, rightMetrics);
        }
    }

    void drawTree(const ExpressionTree& tree) {
        double rootX = 1000;   // ���ڵ��ʼˮƽλ��
        double rootY = 30;    // ���ڵ��ʼ��ֱλ��
        double nodeWidth = 40; // �ڵ���
        double gap = 20;       // Ĭ�ϼ��

        SubtreeMetrics rootMetrics = computeSubtreeMetrics(tree.GetRoot(), nodeWidth, gap);

        map<TreeNode*, NodePosition> positions;
        assignNodePositions(tree.GetRoot(), rootX, rootY, nodeWidth, gap, positions, rootMetrics);

        for (const auto& [node, pos] : positions) {
            // ���ƽڵ�
            scene->addEllipse(pos.x - 20, pos.y - 20, 40, 40, QPen(Qt::black), QBrush(Qt::white));
            scene->addText(QString::fromStdString(node->_isCh ? string(1, node->_ch) :
                node->_isFunc ? node->_func :
                format("{:.1f}", node->_num)),
                QFont("Arial", 12))
                ->setPos(pos.x - 15, pos.y - 15);

            // ��������������
            if (node->_left) {
                auto leftPos = positions[node->_left];
                scene->addLine(pos.x, pos.y, leftPos.x, leftPos.y, QPen(Qt::black));
            }

            // ��������������
            if (node->_right) {
                auto rightPos = positions[node->_right];
                scene->addLine(pos.x, pos.y, rightPos.x, rightPos.y, QPen(Qt::black));
            }
        }
    }

};
