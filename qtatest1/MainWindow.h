#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

    int readPin(int pin, int defVal = 0);
	void writePin(int pin, int value);

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
