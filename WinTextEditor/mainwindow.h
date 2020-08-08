#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include "QCloseEvent"
#include "QKeyEvent"
#include "QFontComboBox"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_actionExit_triggered();

    void on_actionAbout_triggered();

    void yesnew();
    void nonew();
    void yesopen();
    void noopen();
    void cansel();
    void star();
    void setFont(QFont);

    void on_actionZoom_In_triggered();

    void on_actionZoom_Out_triggered();

    void on_actionDefult_Zoom_triggered();

private:
    Ui::MainWindow *ui;
    QPlainTextEdit* tedit;
    QString currentfile;

    QFontComboBox* fonts;

    QDialog* w1,*w2;

protected:
    void closeEvent(QCloseEvent*);

    bool isChanged();

    void ShortCuts();

//    void keyPressEvent(QKeyEvent*);
};
#endif // MAINWINDOW_H
