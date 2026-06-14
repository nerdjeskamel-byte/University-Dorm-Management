#include "mainwindow.h"
#include <QApplication>
#include <QDialog>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //ل (Login Page)
    QDialog loginDlg;
    loginDlg.setWindowTitle("System Login");
    loginDlg.setFixedSize(350, 280);


    loginDlg.setStyleSheet(
        "QDialog { background-color: #f8fafc; }"
        "QLabel { color: #1e293b; font-size: 13px; font-weight: bold; }"
        "QLineEdit { background-color: #ffffff; color: #1e293b; border: 1px solid #cbd5e1; border-radius: 6px; padding: 8px; font-size: 13px; }"
        "QPushButton { background-color: #3b82f6; color: #ffffff; border-radius: 6px; font-weight: bold; font-size: 13px; padding: 10px; border: none; }"
        "QPushButton:hover { background-color: #2563eb; cursor: pointer; }"
        "QPushButton:pressed { background-color: #1d4ed8; }"
        );

    QVBoxLayout *layout = new QVBoxLayout(&loginDlg);
    layout->setSpacing(12);
    layout->setContentsMargins(30, 30, 30, 30);

    QLabel *lblTitle = new QLabel("Dormitory System Admin", &loginDlg);
    lblTitle->setStyleSheet("font-size: 18px; color: #2563eb; margin-bottom: 10px;");
    lblTitle->setAlignment(Qt::AlignCenter);
    layout->addWidget(lblTitle);

    QLabel *lblUser = new QLabel("Username:", &loginDlg);
    QLineEdit *txtUser = new QLineEdit(&loginDlg);
    txtUser->setPlaceholderText("Enter Admin Username");
    layout->addWidget(lblUser);
    layout->addWidget(txtUser);

    QLabel *lblPass = new QLabel("Password:", &loginDlg);
    QLineEdit *txtPass = new QLineEdit(&loginDlg);
    txtPass->setEchoMode(QLineEdit::Password);
    txtPass->setPlaceholderText("Enter Password");
    layout->addWidget(lblPass);
    layout->addWidget(txtPass);

    QPushButton *btnLogin = new QPushButton("Login", &loginDlg);
    layout->addWidget(btnLogin);

    // التحقق من الحساب
    QObject::connect(btnLogin, &QPushButton::clicked, [&]() {
        if (txtUser->text() == "admin" && txtPass->text() == "admin123") {
            loginDlg.accept();
        } else {
            QMessageBox::critical(&loginDlg, "Access Denied", "Invalid Username or Password! ❌");
        }
    });


    if (loginDlg.exec() == QDialog::Accepted) {
        MainWindow w;
        w.show();
        return a.exec();
    }

    return 0;
}