#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Dormitory Management System");
    this->resize(1100, 600);

    // 🎨 تطبيق الـ Premium Light Theme (ألوان تفتح النفس ومفروسة)
    this->setStyleSheet(
        "QMainWindow { background-color: #f8fafc; }"

        "QPushButton { "
        "   background-color: #3b82f6; "
        "   color: #ffffff; "
        "   border-radius: 8px; "
        "   font-weight: bold; "
        "   font-size: 13px; "
        "   border: none; "
        "   min-width: 200px; "
        "   max-width: 200px; "
        "   min-height: 42px; "
        "   max-height: 42px; "
        "   margin-bottom: 10px; "
        "}"
        "QPushButton:hover { background-color: #2563eb; cursor: pointer; }"
        "QPushButton:pressed { background-color: #1d4ed8; }"

        "QTableWidget { "
        "   background-color: #ffffff; "
        "   color: #1e293b; "
        "   gridline-color: #e2e8f0; "
        "   border: 1px solid #cbd5e1; "
        "   border-radius: 8px; "
        "   font-size: 13px; "
        "}"
        "QTableWidget::item { padding: 8px; }"
        "QTableWidget::item:selected { background-color: #eff6ff; color: #2563eb; font-weight: bold; }"

        "QHeaderView::section { "
        "   background-color: #f1f5f9; "
        "   color: #1e293b; "
        "   font-weight: bold; "
        "   padding: 8px; "
        "   border: 1px solid #e2e8f0; "
        "   font-size: 13px; "
        "}"

        "QLabel { color: #0f172a; font-size: 14px; font-weight: bold; }"

        "QDialog { background-color: #f8fafc; color: #1e293b; }"
        "QLineEdit { background-color: #ffffff; color: #1e293b; border: 1px solid #cbd5e1; border-radius: 6px; padding: 8px; font-size: 13px; }"
        "QMessageBox { background-color: #ffffff; }"
        "QMessageBox QLabel { color: #1e293b; font-size: 13px; }"
        "QMessageBox QPushButton { min-width: 80px; }"
        );

    // وجبة المطعم الافتراضية
    savedMeal = "Traditional Couscous / Steak & Fries 🍲";


    if(system.getAllDormitories().empty()) {
        Dormitory d1("Dormitory Central");
        d1.addRoom(Room(101, 2));
        d1.addRoom(Room(102, 3));
        system.addDormitory(d1);
    }

    refreshTables();
}

MainWindow::~MainWindow()
{
    system.saveData();
    delete ui;
}

// 1. زر إضافة طالب جديد
void MainWindow::on_btnAddStudent_clicked()
{
    bool okId, okName, okYear;
    QString id = QInputDialog::getText(this, "Add Student", "Enter Student ID:", QLineEdit::Normal, "", &okId);
    if (!okId || id.isEmpty()) return;

    QString name = QInputDialog::getText(this, "Add Student", "Enter Student Name:", QLineEdit::Normal, "", &okName);
    if (!okName || name.isEmpty()) return;

    QString year = QInputDialog::getText(this, "Add Student", "Enter Academic Year:", QLineEdit::Normal, "", &okYear);
    if (!okYear || year.isEmpty()) return;

    bool exists = false;
    for (const auto& s : system.getAllStudents()) {
        if (s.getId() == id.toStdString()) { exists = true; break; }
    }

    if (exists) {
        QMessageBox::warning(this, "Duplicate ID", "This Student ID already exists!");
        return;
    }

    Student newStudent(id.toStdString(), name.toStdString(), year.toStdString());
    system.registerStudent(newStudent);

    QMessageBox::information(this, "Success", "Student registered successfully!");
    refreshTables();
}

// 2. زر إضافة إقامة جديدة
void MainWindow::on_btnAddDorm_clicked()
{
    bool okDorm, okRoom;
    QString dormName = QInputDialog::getText(this, "Add Dormitory", "Enter Dormitory Name:", QLineEdit::Normal, "", &okDorm);
    if (!okDorm || dormName.isEmpty()) return;

    int roomNum = QInputDialog::getInt(this, "Add Room", "Enter Initial Room Number:", 105, 100, 999, 1, &okRoom);
    if (!okRoom) return;

    Dormitory newDorm(dormName.toStdString());
    newDorm.addRoom(Room(roomNum, 2));

    system.addDormitory(newDorm);
    QMessageBox::information(this, "Success", "Dormitory created with Room " + QString::number(roomNum));
    refreshTables();
}

// 3. زر توجيه طالب لغرفة (النسخة الذكية والمضمونة والمحدثة لايف)
void MainWindow::on_btnAssignStudent_clicked()
{
    bool okId, okDorm, okRoom;
    QString id = QInputDialog::getText(this, "Assign Accommodation", "Enter Student ID:", QLineEdit::Normal, "", &okId);
    if (!okId || id.isEmpty()) return;

    QString dormName = QInputDialog::getText(this, "Assign Accommodation", "Enter Dormitory Name:", QLineEdit::Normal, "", &okDorm);
    if (!okDorm || dormName.isEmpty()) return;

    int roomNum = QInputDialog::getInt(this, "Assign Accommodation", "Enter Room Number:", 105, 100, 999, 1, &okRoom);
    if (!okRoom) return;

    bool studentFound = false;
    int studentRow = -1;
    if (ui->tableStudents) {
        for (int r = 0; r < ui->tableStudents->rowCount(); ++r) {
            if (ui->tableStudents->item(r, 3) && ui->tableStudents->item(r, 3)->text().trimmed() == id.trimmed()) {
                studentFound = true;
                studentRow = r;
                break;
            }
        }
    }

    bool dormFound = false;
    int dormRow = -1;
    if (ui->tableDorms) {
        for (int r = 0; r < ui->tableDorms->rowCount(); ++r) {
            bool nameMatch = (ui->tableDorms->item(r, 0) && ui->tableDorms->item(r, 0)->text().trimmed() == dormName.trimmed());
            bool roomMatch = (ui->tableDorms->item(r, 1) && ui->tableDorms->item(r, 1)->text().trimmed() == QString::number(roomNum));
            if (nameMatch && roomMatch) {
                dormFound = true;
                dormRow = r;
                break;
            }
        }
    }

    if (studentFound && dormFound) {
        QString newStatus = dormName + " (Room " + QString::number(roomNum) + ") 🟢";
        ui->tableStudents->setItem(studentRow, 2, new QTableWidgetItem(newStatus));

        QString currentBeds = ui->tableDorms->item(dormRow, 2)->text();
        if(currentBeds.contains("0 / 2")) {
            ui->tableDorms->setItem(dormRow, 2, new QTableWidgetItem("1 / 2 (Available 🟢)"));
        } else if(currentBeds.contains("1 / 2")) {
            ui->tableDorms->setItem(dormRow, 2, new QTableWidgetItem("2 / 2 (Full ⚠️)"));
        } else if(currentBeds.contains("0 / 3")) {
            ui->tableDorms->setItem(dormRow, 2, new QTableWidgetItem("1 / 3 (Available 🟢)"));
        }

        system.assignStudentToDorm(id.toStdString(), dormName.toStdString(), roomNum);
        QMessageBox::information(this, "Success", "Student successfully assigned!");
    } else {
        QString errorMsg = "Allocation Failed!\nReason: ";
        if(!studentFound) errorMsg += "- Student ID [" + id + "] not found.\n";
        if(!dormFound) errorMsg += "- Dormitory [" + dormName + "] with Room [" + QString::number(roomNum) + "] not found.";
        QMessageBox::critical(this, "Error", errorMsg);
    }
}

// 4. زر حذف طالب
void MainWindow::on_btnRemoveStudent_clicked()
{
    bool ok;
    QString id = QInputDialog::getText(this, "Remove Student", "Enter Student ID to delete:", QLineEdit::Normal, "", &ok);
    if (!ok || id.isEmpty()) return;

    if (system.removeStudent(id.toStdString())) {
        QMessageBox::information(this, "Success", "Student removed successfully!");
    } else {
        QMessageBox::warning(this, "Not Found", "Student ID not found!");
    }
    refreshTables();
}

// 5. زر تحديث قائمة الوجبات للمطعم
void MainWindow::on_btnUpdateMenu_clicked()
{
    bool okDorm, okMenu;
    QString dormName = QInputDialog::getText(this, "Restaurant Admin", "Enter Dormitory Name:", QLineEdit::Normal, "", &okDorm);
    if (!okDorm || dormName.isEmpty()) return;

    bool found = false;
    if (ui->tableDorms) {
        for (int r = 0; r < ui->tableDorms->rowCount(); ++r) {
            if (ui->tableDorms->item(r, 0) && ui->tableDorms->item(r, 0)->text().trimmed() == dormName.trimmed()) {
                found = true;
                break;
            }
        }
    }

    if (found) {
        QString meal = QInputDialog::getText(this, "Update Menu", "Enter today's menu:", QLineEdit::Normal, "", &okMenu);
        if (okMenu && !meal.isEmpty()) {
            savedMeal = meal;
            QMessageBox::information(this, "Success", "Menu Updated Successfully for: " + dormName);
        }
    } else {
        QMessageBox::warning(this, "Error", "Dormitory not found! Please check the exact name.");
    }
}

// 6. زر عرض منيو المطعم
void MainWindow::on_btnShowMenu_clicked()
{
    bool ok;
    QString dormName = QInputDialog::getText(this, "View Restaurant", "Enter Dormitory Name:", QLineEdit::Normal, "", &ok);
    if (!ok || dormName.isEmpty()) return;

    bool found = false;
    if (ui->tableDorms) {
        for (int r = 0; r < ui->tableDorms->rowCount(); ++r) {
            if (ui->tableDorms->item(r, 0) && ui->tableDorms->item(r, 0)->text().trimmed() == dormName.trimmed()) {
                found = true;
                break;
            }
        }
    }

    if (found) {
        QMessageBox::information(this, "Restaurant Info",
                                 "Dormitory: " + dormName +
                                     "\nToday's Menu: " + savedMeal +
                                     "\nTotal Meals Served Today: 65\nStatus: Open 🟢");
    } else {
        QMessageBox::warning(this, "Error", "Dormitory not found!");
    }
}

void MainWindow::refreshTables()
{
    if(ui->tableStudents) {
        ui->tableStudents->clearContents();
        auto students = system.getAllStudents();
        ui->tableStudents->setRowCount(students.size());
        for(size_t i = 0; i < students.size(); ++i) {
            ui->tableStudents->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(students[i].getName())));
            ui->tableStudents->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(students[i].getAcademicYear())));

            QString dormDisplay = "(Not Assigned 🔴)";
            if(students[i].getAccommodationStatus()) {
                for(const auto& d : system.getAllDormitories()) {
                    for(auto r : d.getRooms()) {
                        for(const auto& stud : r.getStudents()) {
                            if(stud.getId() == students[i].getId()) {
                                dormDisplay = QString::fromStdString(d.getDormName()) + " (Room " + QString::number(r.getRoomNumber()) + ") 🟢";
                                break;
                            }
                        }
                    }
                }
            }
            ui->tableStudents->setItem(i, 2, new QTableWidgetItem(dormDisplay));
            ui->tableStudents->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(students[i].getId())));
        }
        ui->tableStudents->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableStudents->verticalHeader()->setVisible(false);
    }

    if(ui->tableDorms) {
        ui->tableDorms->clearContents();
        int totalRows = 0;
        for(const auto& dorm : system.getAllDormitories()) {
            totalRows += dorm.getRooms().size();
        }
        ui->tableDorms->setRowCount(totalRows);
        int currentRow = 0;
        for(const auto& dorm : system.getAllDormitories()) {
            for(auto& room : const_cast<Dormitory&>(dorm).getRooms()) {
                ui->tableDorms->setItem(currentRow, 0, new QTableWidgetItem(QString::fromStdString(dorm.getDormName())));
                ui->tableDorms->setItem(currentRow, 1, new QTableWidgetItem(QString::number(room.getRoomNumber())));
                int occupied = room.getStudents().size();
                int capacity = room.getCapacity();
                QString capacityStr = QString::number(occupied) + " / " + QString::number(capacity) + (occupied >= capacity ? " (Full ⚠️)" : " (Available 🟢)");
                ui->tableDorms->setItem(currentRow, 2, new QTableWidgetItem(capacityStr));
                currentRow++;
            }
        }
        ui->tableDorms->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableDorms->verticalHeader()->setVisible(false); //
    }
}