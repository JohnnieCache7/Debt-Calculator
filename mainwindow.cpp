#include "mainwindow.h"
#include <QGridLayout>
#include <QMessageBox>
#include <QString>
#include <cmath>
#include <vector>
#include <iostream>


using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Set GUI title
    setWindowTitle("Snowball Debt Calculator");

    // Initialize labels and input fields
    debtAmountLabel = new QLabel("Debt Amount:");
    interestRateLabel = new QLabel("Interest Rate (%):");
    monthlyPaymentLabel = new QLabel("Your Monthly Payment:");
    debtAmountEdit = new QLineEdit;
    interestRateEdit = new QLineEdit;
    monthlyPaymentEdit = new QLineEdit;
    addDebtButton = new QPushButton("Add Debt To List");
    calculateButton = new QPushButton("Calculate");
    resultLabel = new QLabel;

    // Create layout for debt information
    debtLayout = new QVBoxLayout;

    // Set GUI size
    resize(250, 200);

    // Create central widget and set layout
    QWidget *centralWidget = new QWidget;
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout;

    // Add widgets to the layout
    layout->addWidget(debtAmountLabel);
    layout->addWidget(debtAmountEdit);
    layout->addWidget(interestRateLabel);
    layout->addWidget(interestRateEdit);
    layout->addWidget(addDebtButton);
    layout->addLayout(debtLayout);
    layout->addWidget(monthlyPaymentLabel);
    layout->addWidget(monthlyPaymentEdit);
    layout->addWidget(calculateButton);
    layout->addWidget(resultLabel);

    // Connect buttons to slots
    connect(addDebtButton, &QPushButton::clicked, this, &MainWindow::addDebtField);
    connect(calculateButton, &QPushButton::clicked, this, &MainWindow::calculateRepaymentPlan);

    // Set layout for central widget
    centralWidget->setLayout(layout);
}

MainWindow::~MainWindow()
{
}

void MainWindow::calculateRepaymentPlan()
{
    // Get monthly payment amount
    QString monthlyPaymentText = monthlyPaymentEdit->text();
    if (monthlyPaymentText.isEmpty()) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid monthly payment amount.");
        return;
    }
    double monthlyPayment = monthlyPaymentText.toDouble();

    // Declare variables
    double totalDebtAmount = 0;
    double totalInterest = 0;
    int months;

    // Calculate total debt amount and interest
    for (const auto& debt : debts) {
        totalDebtAmount += debt.amount;
        totalInterest += debt.amount * (debt.interestRate / 100.0);
    }

    // Calculate total amount to be paid including interest
    double totalAmountPaid = totalDebtAmount + totalInterest;

    // Check if monthly payment is enough to pay off debts
    if (monthlyPayment <= 0) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a monthly payment greater than zero.");
        return;
    }

    // Calculate number of months to pay off debt using Snowball Method
    months = static_cast<int>(ceil(totalAmountPaid / monthlyPayment));

    // Display result
    resultLabel->setText(QString("Total amount paid off including interest: $%1\nEstimated time to pay off debt (Snowball Method): %2 months").arg(totalAmountPaid, 0, 'f', 2).arg(months));
}

void MainWindow::addDebtField()
{
    // Get amount and interest rate from input fields
    double amount = debtAmountEdit->text().toDouble();
    double interestRate = interestRateEdit->text().toDouble();

    // Add debt to list
    debts.push_back({ amount, interestRate });

    // Display added debt information in the layout
    QLabel *debtLabel = new QLabel(QString("Debt %1: $%2 at %3% interest").arg(debts.size()).arg(amount).arg(interestRate));
    debtLayout->addWidget(debtLabel);

    // Clear input fields after adding debt
    debtAmountEdit->clear();
    interestRateEdit->clear();
}
