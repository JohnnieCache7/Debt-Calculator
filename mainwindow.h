// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QVBoxLayout>
#include <vector>
using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addDebtField();
    void calculateRepaymentPlan();

private:
    struct Debt {
        double amount; // debt amount
        double interestRate; // interest rates for debt
    };

    // widgets
    QLabel *debtAmountLabel;
    QLabel *interestRateLabel;
    QLabel *strategyLabel;
    QLabel *monthlyPaymentLabel;
    QLineEdit *debtAmountEdit;
    QLineEdit *interestRateEdit;
    QLineEdit *monthlyPaymentEdit;
    QPushButton *addDebtButton;
    QPushButton *calculateButton;
    QLabel *resultLabel;
    QVBoxLayout *debtLayout;

    vector<Debt> debts; // list of debt
};

#endif // MAINWINDOW_H
