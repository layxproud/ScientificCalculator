#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QObject>
#include <QLabel>

class Calculator : public QObject
{
    Q_OBJECT
public:
    explicit Calculator(QLabel *resultLabel, QLabel *prevLabel, QObject *parent = nullptr);

private:
    QLabel *currentInput;
    QLabel *previousInput;
    bool hasDot;
    bool waitingNumber;
    QString prevOperator;
    QString currentOperator;
    double firstNumber;
    double secondNumber;
    double resultNumber;

    void saveNumber(double &number);
    void showResult(bool onEqualsButton);
    void calculateResult(const QString &op);

public slots:
    void onNumericButtonClicked();
    void onBinaryOperatorClicked();
    void onUnaryOperatorClicked();
    void onEqualsButtonClicked();
    void onDotButtonClicked();
    void onClearButtonClicked();
    void onCleanEntryButtonClicked();


signals:

};

#endif // CALCULATOR_H
