#include "calculator.h"
#include <QDebug>
#include <QPushButton>

Calculator::Calculator(QLabel *resultLabel, QLabel *prevLabel, QObject *parent)
    : QObject{parent}
    , currentInput{resultLabel}
    , previousInput{prevLabel}
    , hasDot{false}
    , waitingNumber{true}
    , currentOperator{""}
    , firstNumber{0}
    , secondNumber{0}
    , resultNumber{0}
{

}

void Calculator::saveNumber(double &number)
{
    try
    {
        bool ok;
        number = currentInput->text().toDouble(&ok);
        if (!ok)
        {
            throw std::runtime_error("Failed to convert QString to double");
        }
    }
    catch (const std::exception &e)
    {
        qDebug() << "Error: " << e.what();
        return;
    }
}

void Calculator::showResult(bool onEqualsButton)
{
    if (onEqualsButton)
    {
        calculateResult(currentOperator);

        previousInput->setText(previousInput->text() + currentInput->text() + "=");
        currentInput->setText(QString::number(resultNumber));
        currentOperator = "";
    }
    else
    {
        calculateResult(prevOperator);

        previousInput->setText(QString::number(resultNumber) + "prevOperator");
        currentInput->setText(QString::number(resultNumber));
        firstNumber = resultNumber;
        waitingNumber = true;
    }

    return;
}

void Calculator::calculateResult(const QString &op)
{
    if (op == "+")
    {
        resultNumber = firstNumber + secondNumber;
    }
    else if (op == "-")
    {
        resultNumber = firstNumber - secondNumber;
    }
    else if (op == "×")
    {
        resultNumber = firstNumber * secondNumber;
    }
    else if (op == "/")
    {
        resultNumber = firstNumber / secondNumber;
    }
    else
    {
        return;
    }
}

void Calculator::onNumericButtonClicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(QObject::sender());

    if (waitingNumber || currentInput->text() == "0")
    {
        waitingNumber = false;
        currentInput->setText("");
    }

    currentInput->setText(currentInput->text() + btn->text());
}

void Calculator::onBinaryOperatorClicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(QObject::sender());
    prevOperator = currentOperator;
    currentOperator = btn->text();

    if (prevOperator != "" && !waitingNumber)
    {
        saveNumber(secondNumber);
        showResult(false);
    }

    saveNumber(firstNumber);

    previousInput->setText(currentInput->text() + currentOperator);
    waitingNumber = true;
}

void Calculator::onUnaryOperatorClicked()
{

}

void Calculator::onEqualsButtonClicked()
{
    saveNumber(secondNumber);
    showResult(true);
}

void Calculator::onDotButtonClicked()
{
    if (hasDot)
        return;
    currentInput->setText(currentInput->text() + '.');
    hasDot = true;
    waitingNumber = false;
}

void Calculator::onClearButtonClicked()
{
    previousInput->clear();
    currentInput->setText("0");
    currentOperator = "";
    prevOperator = "";
    resultNumber = 0;
    firstNumber = 0;
    secondNumber = 0;
    waitingNumber = true;
}

void Calculator::onCleanEntryButtonClicked()
{
    currentInput->setText("0");
}


