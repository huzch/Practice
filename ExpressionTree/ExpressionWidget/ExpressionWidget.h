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

        // 创建布局管理器
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(view);

        // 创建输入框，用于输入前缀表达式
        prefixInput = new QLineEdit(this);
        prefixInput->setPlaceholderText("Enter prefix expression (e.g., +AB)");
        layout->addWidget(prefixInput);

        // 创建按钮，用于构建输入的前缀表达式
        buildTreeButton = new QPushButton("Build Tree", this);
        connect(buildTreeButton, &QPushButton::clicked, this, &ExpressionWidget::onBuildTreeButtonClicked);
        layout->addWidget(buildTreeButton);

        // 创建并设置QLabel，用于显示中缀表达式
        infixLabel = new QLabel(this);
        infixLabel->setText("Infix Expression: " + QString::fromStdString(tree.GetInfix()));
        layout->addWidget(infixLabel);

        // 创建输入框，用于输入变量和值
        varNameInput = new QLineEdit(this);
        varNameInput->setPlaceholderText("Enter variable name");
        layout->addWidget(varNameInput);

        varValueInput = new QLineEdit(this);
        varValueInput->setPlaceholderText("Enter variable value");
        layout->addWidget(varValueInput);

        // 创建按钮，点击后为变量赋值
        assignButton = new QPushButton("Assign", this);
        connect(assignButton, &QPushButton::clicked, this, &ExpressionWidget::onAssignButtonClicked);
        layout->addWidget(assignButton);

        // 创建按钮，点击后计算表达式的值
        valueButton = new QPushButton("Value", this);
        connect(valueButton, &QPushButton::clicked, this, &ExpressionWidget::onValueButtonClicked);
        layout->addWidget(valueButton);

        // 显示计算结果
        resultLabel = new QLabel(this);
        resultLabel->setText("Result: ");
        layout->addWidget(resultLabel);

        // 创建输入框，用于输入要求偏导的变量
        diffVarInput = new QLineEdit(this);
        diffVarInput->setPlaceholderText("Enter variable for partial derivative");
        layout->addWidget(diffVarInput);

        // 创建按钮，点击后求偏导
        diffButton = new QPushButton("Diff", this);
        connect(diffButton, &QPushButton::clicked, this, &ExpressionWidget::onDiffButtonClicked);
        layout->addWidget(diffButton);

        // 显示偏导结果
        diffLabel = new QLabel(this);
        diffLabel->setText("Partial Derivative: ");
        layout->addWidget(diffLabel);

        // 创建按钮，点击后进行常数合并
        mergeConstButton = new QPushButton("Merge Const", this);
        connect(mergeConstButton, &QPushButton::clicked, this, &ExpressionWidget::onMergeConstButtonClicked);
        layout->addWidget(mergeConstButton);

        // 显示常数合并后的结果
        mergeConstLabel = new QLabel(this);
        mergeConstLabel->setText("Merged Expression: ");
        layout->addWidget(mergeConstLabel);

        drawTree(tree);

        // 设置场景大小
        view->setSceneRect(0, 0, 1000, 800);
        setFixedSize(1000, 800);  // 固定窗口大小
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
    
    QLineEdit* prefixInput;  // 输入框，允许输入前缀表达式
    QLineEdit* varNameInput; // 输入框，用于输入变量名
    QLineEdit* varValueInput; // 输入框，用于输入变量值
    QLineEdit* diffVarInput; // 输入框，用于输入要求偏导的变量

    QPushButton* buildTreeButton;  // 按钮，点击时构建前缀表达式
    QPushButton* assignButton;  // 按钮，点击时为变量赋值
    QPushButton* valueButton; // 按钮，点击时计算表达式的值
    QPushButton* diffButton; // 按钮，点击时求偏导
    QPushButton* mergeConstButton; // 按钮，点击时进行常数合并

    QLabel* infixLabel;   // 用于显示中缀表达式
    QLabel* resultLabel;  // 用于显示计算结果
    QLabel* diffLabel;  // 用于显示偏导结果
    QLabel* mergeConstLabel; // 用于显示常数合并后的表达式

    ExpressionTree tree;

    void drawTree(const ExpressionTree& tree)
    {
        double yOffset = 30;
        drawNode(scene, tree.GetRoot(), 460, yOffset, 200, yOffset);  // 传递一个初始的水平间距
    }

    void drawNode(QGraphicsScene* scene, TreeNode* node, double x, double y, double xOffset, double& yOffset)
    {
        if (node == nullptr) return;

        // 绘制节点圆圈
        QGraphicsEllipseItem* ellipse = scene->addEllipse(x - 20, y - 20, 40, 40, QPen(Qt::black), QBrush(Qt::white));

        // 绘制节点文本
        QGraphicsTextItem* textItem = scene->addText(QString::fromStdString(node->_isCh ? std::string(1, node->_ch) :
            node->_isFunc ? node->_func :
            to_string((int)node->_num)),
            QFont("Arial", 12));
        textItem->setPos(x - 15, y - 15);

        // 递归绘制子节点
        double leftX = x - xOffset;
        double rightX = x + xOffset;
        double newYOffset = y + 60;

        // 根据子节点数量动态调整每个节点之间的间距
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

    void onBuildTreeButtonClicked()  // 构建按钮点击槽函数
    {
        QString prefix = prefixInput->text();  // 获取输入框中的前缀表达式字符串
        if (prefix.isEmpty()) {
            return;
        }

        // 解析前缀表达式并构建树
        
        tree = ExpressionTree(prefix.toStdString());   // 假设你已经有一个方法来从前缀表达式构建树

        // 更新显示中缀表达式
        infixLabel->setText("Infix Expression: " + QString::fromStdString(tree.GetInfix()));

        // 更新树的可视化
        scene->clear();
        drawTree(tree);
    }

    void onAssignButtonClicked()  // 赋值按钮点击槽函数
    {
        QString varName = varNameInput->text();  // 获取变量名
        QString varValue = varValueInput->text();  // 获取变量值

        if (varName.isEmpty() || varValue.isEmpty()) {
            return;
        }

        // 将变量值赋给树中的相应节点
        char varChar = varName.toStdString()[0];
        tree.Assign(varChar, std::stod(varValue.toStdString()));

        
        // 更新显示中缀表达式
        infixLabel->setText("Infix Expression: " + QString::fromStdString(tree.GetInfix()));

        // 更新树的可视化
        scene->clear();
        drawTree(tree);
    }

    void onValueButtonClicked()  // 求值按钮点击槽函数
    {
        // 计算表达式的值
        DATATYPE result = tree.Value();

        // 显示结果
        resultLabel->setText("Result: " + QString::number(result));
    }

    void onDiffButtonClicked()  // 求偏导按钮点击槽函数
    {
        // 获取偏导变量
        QString diffVar = diffVarInput->text();

        if (diffVar.isEmpty()) {
            return;
        }

        // 转换变量名为char
        char varChar = diffVar.toStdString()[0];

        // 计算偏导数
        tree.Diff(varChar);

        // 更新显示偏导表达式
        diffLabel->setText("Partial Derivative: " + QString::fromStdString(tree.GetInfix()));

        // 更新树的可视化
        scene->clear();
        drawTree(tree);
    }

    void onMergeConstButtonClicked()  // 常数合并按钮点击槽函数
    {
        // 执行常数合并操作
        tree.MergeConst();

        // 更新显示合并后的中缀表达式
        mergeConstLabel->setText("Merged Expression: " + QString::fromStdString(tree.GetInfix()));

        // 更新树的可视化
        scene->clear();
        drawTree(tree);
    }
};
