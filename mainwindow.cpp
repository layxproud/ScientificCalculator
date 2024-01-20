#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    calculator = new Calculator(ui->resultDisplay, ui->prevResultDisplay, this);

    populateButtonLists();

    connect(ui->dotButton, &QPushButton::clicked, calculator, &Calculator::onDotButtonClicked);
    connect(ui->equalsButton, &QPushButton::clicked, calculator, &Calculator::onEqualsButtonClicked);
    connect(ui->clearButton, &QPushButton::clicked, calculator, &Calculator::onClearButtonClicked);
    connect(ui->cleanEntryButton, &QPushButton::clicked, calculator, &Calculator::onCleanEntryButtonClicked);
}

MainWindow::~MainWindow()
{
    delete calculator;
    delete ui;
}

void MainWindow::populateButtonLists()
{
    static QRegularExpression numericRegex(".*Numeric$");
    static QRegularExpression binaryOperatorRegex(".*ButtonBinary$");
    static QRegularExpression unaryOperatorRegex(".*ButtonUnary$");

    QList<QPushButton*> buttons = findChildren<QPushButton*>();
    QList<QPushButton*> binaryOperators;
    QList<QPushButton*> unaryOperators;
    QList<QPushButton*> numericButtons;

    for (auto &btn : buttons)
    {
        QString objectName = btn->objectName();
        if (binaryOperatorRegex.match(objectName).hasMatch())
        {
            connect(btn, &QPushButton::clicked, calculator, &Calculator::onBinaryOperatorClicked);
            binaryOperators.append(btn);
        }
        else if (unaryOperatorRegex.match(objectName).hasMatch())
        {
            connect(btn, &QPushButton::clicked, calculator, &Calculator::onUnaryOperatorClicked);
            unaryOperators.append(btn);
        }
        else if (numericRegex.match(objectName).hasMatch())
        {
            connect(btn, &QPushButton::clicked, calculator, &Calculator::onNumericButtonClicked);
            numericButtons.append(btn);
        }
    }
}

