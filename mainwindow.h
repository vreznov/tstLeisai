#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/* 雷塞API测试
 * @brief: 使用了msvc2015/mingw 32编译器，64库文件无法使用
 * @author: kare
 *
 * */
#include <QMainWindow>
#include "LTSMC.h"
#include <QDebug>
#include <QTimer>
#include <QPlainTextEdit>

#define COUT qDebug()

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

private:
    Ui::MainWindow *ui;

private:
    short comret = 0;
    QTimer tmr;
    void tmot();
    QPlainTextEdit* pedit = nullptr;
    WORD axisnum = 0;
};

#endif // MAINWINDOW_H
