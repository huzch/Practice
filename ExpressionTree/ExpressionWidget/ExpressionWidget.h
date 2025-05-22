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

        // 创建主布局
        auto mainLayout = new QHBoxLayout(this);

        // 使用 QSplitter 分割左右区域
        auto splitter = new QSplitter(Qt::Horizontal, this);
        mainLayout->addWidget(splitter);

        // 左侧：表达式树的可视化
        auto leftWidget = new QWidget(this);
        auto leftLayout = new QVBoxLayout(leftWidget);
        leftLayout->addWidget(view);
        splitter->addWidget(leftWidget);

        // 设置场景大小
        view->setSceneRect(0, 0, 2000, 1000);

        // 右侧：输入控件和操作按钮
        auto rightWidget = new QWidget(this);
        auto rightLayout = new QVBoxLayout(rightWidget);
        splitter->addWidget(rightWidget);

        // 中缀表达式显示
        auto infixLabel = new QLabel(this);
        infixLabel->setText("Infix Expression: " + QString::fromStdString(tree.GetInfix()));
        rightLayout->addWidget(infixLabel);

        // 前缀表达式输入和构建按钮
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

        // 表达式复合输入和按钮
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

        // 计算结果显示和赋值输入
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

        // 偏导结果显示和输入
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

        // 常数合并结果显示和按钮
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

        // 设置 splitter 的默认比例
        splitter->setStretchFactor(0, 3);  // 左侧占 3
        splitter->setStretchFactor(1, 1);  // 右侧占 1

        // 设置窗口大小
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

    // 节点布局辅助结构
    struct NodePosition {
        double x;
        double y;
    };

    struct SubtreeMetrics {
        double width;   // 子树宽度
        double xOffset; // 根节点的水平偏移
    };

    // 递归计算子树宽度及水平偏移
    SubtreeMetrics computeSubtreeMetrics(TreeNode* node, double nodeWidth, double gap) {
        if (!node) return { 0, 0 };

        SubtreeMetrics leftMetrics = computeSubtreeMetrics(node->_left, nodeWidth, gap);
        SubtreeMetrics rightMetrics = computeSubtreeMetrics(node->_right, nodeWidth, gap);

        // 保持左右子树间的最小间距
        double subtreeWidth = leftMetrics.width + rightMetrics.width + gap;
        subtreeWidth = std::max(subtreeWidth, nodeWidth);

        // 根节点的水平偏移量
        double xOffset = leftMetrics.width + gap / 2.0;

        return { subtreeWidth, xOffset };
    }

    // 分配节点的坐标（保持对称性）
    void assignNodePositions(TreeNode* node, double x, double y, double nodeWidth, double gap,
        map<TreeNode*, NodePosition>& positions, const SubtreeMetrics& metrics) {
        if (!node) return;

        // 记录当前节点位置
        positions[node] = { x, y };

        // 递归布置左子树
        if (node->_left) {
            double leftX = x - metrics.xOffset;
            SubtreeMetrics leftMetrics = computeSubtreeMetrics(node->_left, nodeWidth, gap);
            assignNodePositions(node->_left, leftX, y + 60, nodeWidth, gap, positions, leftMetrics);
        }

        // 递归布置右子树
        if (node->_right) {
            double rightX = x + metrics.xOffset;
            SubtreeMetrics rightMetrics = computeSubtreeMetrics(node->_right, nodeWidth, gap);
            assignNodePositions(node->_right, rightX, y + 60, nodeWidth, gap, positions, rightMetrics);
        }
    }

    void drawTree(const ExpressionTree& tree) {
        double rootX = 1000;   // 根节点初始水平位置
        double rootY = 30;    // 根节点初始垂直位置
        double nodeWidth = 40; // 节点宽度
        double gap = 20;       // 默认间距

        SubtreeMetrics rootMetrics = computeSubtreeMetrics(tree.GetRoot(), nodeWidth, gap);

        map<TreeNode*, NodePosition> positions;
        assignNodePositions(tree.GetRoot(), rootX, rootY, nodeWidth, gap, positions, rootMetrics);

        for (const auto& [node, pos] : positions) {
            // 绘制节点
            scene->addEllipse(pos.x - 20, pos.y - 20, 40, 40, QPen(Qt::black), QBrush(Qt::white));
            scene->addText(QString::fromStdString(node->_isCh ? string(1, node->_ch) :
                node->_isFunc ? node->_func :
                format("{:.1f}", node->_num)),
                QFont("Arial", 12))
                ->setPos(pos.x - 15, pos.y - 15);

            // 绘制左子树连线
            if (node->_left) {
                auto leftPos = positions[node->_left];
                scene->addLine(pos.x, pos.y, leftPos.x, leftPos.y, QPen(Qt::black));
            }

            // 绘制右子树连线
            if (node->_right) {
                auto rightPos = positions[node->_right];
                scene->addLine(pos.x, pos.y, rightPos.x, rightPos.y, QPen(Qt::black));
            }
        }
    }

};
