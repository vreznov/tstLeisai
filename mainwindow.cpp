#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pedit = ui->plainTextEdit;
    connect(&tmr, &QTimer::timeout, this, &MainWindow::tmot);
    tmr.start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    // "192.168.15.11:502"
    char cip[] =  "192.168.5.11";
    comret = smc_board_init(0, 2, cip, 0);
    if(comret != 0)
    {
        COUT<<"error when connect to board : code "<<comret<<endl;
    }
    else
    {
        COUT<<"connect sucessful"<<endl;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    comret = smc_board_close(0);
    if(comret != 0)
    {
        COUT<<"error when disconnect from board : code "<<comret<<endl;
    }
    else
    {
        COUT<<"disconnect sucessful"<<endl;
    }
}

void MainWindow::tmot()
{
    pedit->setPlainText("读取信息\r\n");

    short ret = 0;

    //获取模式
    WORD runmode = 0;
    ret = smc_get_axis_run_mode(0, axisnum, &runmode);
    pedit->appendPlainText(QString("runmode: %1").arg(runmode));

    //获取脉冲当量
    double equiv = 0;
    ret = smc_get_equiv(0, axisnum, &equiv);
    pedit->appendPlainText(QString("equiv: %1").arg(equiv));

    //读取使能状态
    short pwon = smc_axis_io_enable_status(0, axisnum);
    pedit->appendPlainText(QString("pow state: %1").arg(pwon));

    //读取运动状态
    short movestate = smc_check_done(0, axisnum);
    pedit->appendPlainText(QString("move state: %1").arg(movestate));

    //读取目标位置
    double target = 0;
    ret = smc_get_target_position_unit(0, axisnum, &target);
    pedit->appendPlainText(QString("target pos: %1").arg(target));

    //速度位置
    double curpos = 0;
    ret = smc_get_position_unit(0, axisnum, &curpos);
    pedit->appendPlainText(QString("current pos: %1").arg(curpos));

    //读取速度
    double curvel = 0;
    ret = smc_read_current_speed_unit(0, axisnum, &curvel);
    pedit->appendPlainText(QString("current vel: %1").arg(curvel));

    //读取轴停止原因
    long stopreason = 0;
    ret = smc_get_stop_reason(0, axisnum, &stopreason);
    pedit->appendPlainText(QString("current stop reason: %1").arg(stopreason));

    //读取回原点状态
    WORD homestate = 0;
    ret = smc_get_home_result(0, axisnum, &homestate);
    pedit->appendPlainText(QString("home state: %1").arg(homestate));
}

void MainWindow::on_pushButton_3_clicked()
{
    double setval = ui->lineEdit->text().toDouble();
    short ret = smc_set_position_unit(0, axisnum, setval);
}


void MainWindow::on_pushButton_4_clicked()
{
    axisnum = ui->spinBox->value();
}

//绝对运动
void MainWindow::on_pushButton_5_clicked()
{
    double target = ui->lineEdit_2->text().toDouble();
    short ret = smc_pmove_unit(0, axisnum, target, 1);
}

//相对运动
void MainWindow::on_pushButton_6_clicked()
{
    double target = ui->lineEdit_2->text().toDouble();
    short ret = smc_pmove_unit(0, axisnum, target, 0);

}

//减速停止
void MainWindow::on_pushButton_7_clicked()
{
    short ret = smc_stop(0, axisnum, 0);
}

//立即停止
void MainWindow::on_pushButton_8_clicked()
{
    short ret = smc_stop(0, axisnum, 0);
}

//回原点
void MainWindow::on_pushButton_9_clicked()
{
    short ret = smc_home_move(0, axisnum);
}

//PTT测试
void MainWindow::on_pushButton_10_clicked()
{
    WORD axislist[] = {0, 1, 2, 3, 4, 5, 6};
    double tm[] = {0, 1, 2, 3, 4, 5};
    double pnts[] = {0, 1000, 3000, 4000, 6000, 8000};
    short ret = smc_ptt_table_unit(0, axisnum, 6, tm, pnts);
    //注意：运动是增量模式
    ret = smc_pvt_move(0, 1, axislist);
}

//PVTS测试
void MainWindow::on_pushButton_11_clicked()
{
    WORD axislist[] = {0, 1, 2, 3, 4, 5, 6};
    double tm[] = {0, 1, 2, 3, 4, 5};
    double pnts[] = {0, 1000, 3000, 4000, 6000, 8000};
    short ret = smc_pvts_table_unit(0, axisnum, 6, tm, pnts, 0, 20000);
    //注意：运动是增量模式
    ret = smc_pvt_move(0, 1, axislist);
}
