#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QThread>
#include <QDateTime>
#include <QAbstractButton>
#include <QCheckBox>
#include <QTableWidgetItem>
#include <QTimer>

static MainWindow *s_mainWnd = nullptr;

//api

static const int HIGH = 1, LOW = 0;
static const int INPUT = 0, OUTPUT = 1;

extern void setup();
extern void loop();

extern void _pre_setup(); //non-api

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	s_mainWnd = this;


    _pre_setup();

	setup();

	QTimer *timer = new QTimer(this);
	connect(timer, &QTimer::timeout, [this] { loop(); });
	timer->start(0);

}

MainWindow::~MainWindow()
{
	delete ui;
}

int MainWindow::readPin(int pin, int defVal)
{
	QObjectList pinBtns = ui->groupBox->children();
	for(auto &obj: pinBtns)
	{
		auto btn = qobject_cast<QAbstractButton*>(obj);
		if (!btn)
			continue;
		int p = btn->text().toInt();
		if (p == pin)
		{
            return (btn->isChecked() && btn->isChecked())? HIGH: LOW;
		}
	}
	auto *btn = new QCheckBox;
	btn->setText(QString::number(pin));
    btn->setChecked(defVal);
	ui->groupBox->layout()->addWidget(btn);
    return LOW;
}

void MainWindow::writePin(int pin, int value)
{
	for (int i = 0 ; i < ui->tableWidget->rowCount(); ++i)
	{
		auto item = ui->tableWidget->item(i, 0);
		if (item->data(0).toInt() == pin)
		{
			item = ui->tableWidget->item(i, 1);
			item->setData(0, QString::number(value));
			item->setBackgroundColor(value? Qt::red: Qt::white);
			return;
		}
	}
	ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
	ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(QString::number(pin)));
	auto item =  new QTableWidgetItem(QString::number(value));
	ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, item);
	item->setBackgroundColor(value? Qt::red: Qt::white);
}

//api

unsigned long millis()
{
    return (unsigned long)(QDateTime::currentMSecsSinceEpoch()/* & 0xffffffff*/);
}

void delay(unsigned long ms)
{
	qint64 start = QDateTime::currentMSecsSinceEpoch();
	while (QDateTime::currentMSecsSinceEpoch() - start < qint64(ms))
	{
		QApplication::processEvents();
		QThread::msleep(0);
	}
}

int digitalRead(int pin, int defVal)
{
    return s_mainWnd->readPin(pin, defVal);
}

void digitalWrite(int pin, int value)
{
	s_mainWnd->writePin(pin, value);
}

void pinMode(int /*pin*/, int /*mode*/)
{

}
