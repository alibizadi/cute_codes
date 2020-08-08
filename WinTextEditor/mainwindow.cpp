#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QFile"
#include "QFileDialog"
#include "QTextStream"
#include "QMessageBox"
#include "QVBoxLayout"
#include "QHBoxLayout"
#include "QLabel"
#include "QPushButton"
#include "QShortcut"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowIcon(QIcon(":/images/main-icon2.png"));
    this->setWindowTitle("Text Editor - New Text");

    fonts=new QFontComboBox(this);
    ui->toolBar->addWidget(fonts);

    connect(fonts,&QFontComboBox::currentFontChanged,this,&MainWindow::setFont);

    tedit=new QPlainTextEdit(this);
    tedit->setFocus();
    tedit->setFont(QFont("Ubuntu",15));
    tedit->setStyleSheet("border:none");
    setCentralWidget(tedit);

    connect(tedit,&QPlainTextEdit::textChanged,this,&MainWindow::star);

    w1=new QDialog(this);
    w1->setWindowTitle("Warning!");
    w1->setMaximumSize(500,180);
    w1->setMinimumSize(500,180);

    w2=new QDialog(this);
    w2->setWindowTitle("Warning!");
    w2->setMaximumSize(500,180);
    w2->setMinimumSize(500,180);

    QVBoxLayout* layout1=new QVBoxLayout;
    QHBoxLayout* layout11=new QHBoxLayout;
    QVBoxLayout* layout2=new QVBoxLayout;
    QHBoxLayout* layout22=new QHBoxLayout;

    QLabel* label1=new QLabel("Do you want to save changes?\nIf you No, a recent copy of this file will be temporarily available!");
    label1->setFont(QFont("Comic Sans MS",11));
    label1->setAlignment(Qt::AlignTop);

    QLabel* label2=new QLabel("Do you want to save changes?\nIf you No, a recent copy of this file will be temporarily available!");
    label2->setFont(QFont("Comic Sans MS",11));
    label2->setAlignment(Qt::AlignTop);

    QPushButton* yes1=new QPushButton("Yes");
    QPushButton* no1=new QPushButton("No");
    QPushButton* cansel1=new QPushButton("Cansel");

    QPushButton* yes2=new QPushButton("Yes");
    QPushButton* no2=new QPushButton("No");
    QPushButton* cansel2=new QPushButton("Cansel");

    yes1->setMaximumSize(110,35);
    no1->setMaximumSize(110,35);
    cansel1->setMaximumSize(110,35);
    yes2->setMaximumSize(110,35);
    no2->setMaximumSize(110,35);
    cansel2->setMaximumSize(110,35);

    layout11->addWidget(yes1);
    layout11->addWidget(no1);
    layout11->addWidget(cansel1);
    layout22->addWidget(yes2);
    layout22->addWidget(no2);
    layout22->addWidget(cansel2);

    layout1->addWidget(label1);
    layout1->addItem(layout11);
    layout2->addWidget(label2);
    layout2->addItem(layout22);

    layout1->setMargin(30);
    layout2->setMargin(30);

    w1->setLayout(layout1);
    w2->setLayout(layout2);

    connect(yes1,&QPushButton::clicked,this,&MainWindow::yesnew);
    connect(no1,&QPushButton::clicked,this,&MainWindow::nonew);
    connect(cansel1,&QPushButton::clicked,this,&MainWindow::cansel);

    connect(yes2,&QPushButton::clicked,this,&MainWindow::yesopen);
    connect(no2,&QPushButton::clicked,this,&MainWindow::noopen);
    connect(cansel2,&QPushButton::clicked,this,&MainWindow::cansel);

    ShortCuts();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    if(!currentfile.isEmpty()){
        if(isChanged())
            w1->show();
        else{
            currentfile.clear();
            tedit->setPlainText(QString());
        }
    }
    else{
        if(tedit->toPlainText().isEmpty())
            nonew();
        else w1->show();
    }
}

void MainWindow::on_actionOpen_triggered()
{
    if(!currentfile.isEmpty()){
        if(isChanged())
            w2->show();
        else noopen();
    }
    else{
        if(tedit->toPlainText().isEmpty())
            noopen();
        else w2->show();
    }
}

void MainWindow::on_actionSave_triggered()
{
    if(currentfile.isEmpty())
        currentfile=QFileDialog::getSaveFileName(this,"Save File","","Text File(*.txt)");

    if(!currentfile.isEmpty()){
        QFile file(currentfile);
        if(!file.open(QFile::WriteOnly|QFile::Text)){
            QMessageBox::critical(this,"Error","Sorry, Couldn't Save File!!!");
            return;
        }
        setWindowTitle("Text Editor - "+currentfile);

        QTextStream in(&file);
        QString text=tedit->toPlainText();
        in<<text;
        file.close();
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    currentfile=QFileDialog::getSaveFileName(this,"Save File","","Text File(*.txt)");

    if(!currentfile.isEmpty()){
        QFile file(currentfile);
        if(!file.open(QFile::WriteOnly|QFile::Text)){
            QMessageBox::critical(this,"Error","Sorry, Couldn't Save File!!!");
            return;
        }
        setWindowTitle("Text Editor - "+currentfile);

        QTextStream in(&file);
        QString text=tedit->toPlainText();
        in<<text;
        file.close();
    }
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this,"About","Text Editor Made With Qt 5.15\n By Ali Bizi");
}

void MainWindow::yesnew()
{
    on_actionSave_triggered();
    currentfile.clear();
    tedit->setPlainText(QString());
    w1->close();
}

void MainWindow::nonew()
{
    currentfile.clear();
    tedit->setPlainText(QString());
    w1->close();
}

void MainWindow::yesopen()
{
    on_actionSave_triggered();
    w2->close();
    currentfile=QFileDialog::getOpenFileName(this,"Open Text File","","Text File(*.txt)");

    if(!currentfile.isEmpty()){
        QFile file(currentfile);
        if(!file.open(QFile::ReadOnly|QFile::Text)){
            QMessageBox::critical(this,"Error","Sorry, Couldn't Open File!!!");
            return;
        }

        QTextStream out(&file);
        QString text=out.readAll();
        file.close();

        tedit->setPlainText(text);

        setWindowTitle("Text Editor - "+currentfile);
    }
}

void MainWindow::noopen()
{
    currentfile=QFileDialog::getOpenFileName(this,"Open Text File","","Text File(*.txt)");

    if(!currentfile.isEmpty()){
        QFile file(currentfile);
        if(!file.open(QFile::ReadOnly|QFile::Text)){
            QMessageBox::critical(this,"Error","Sorry, Couldn't Open File!!!");
            return;
        }

        QTextStream out(&file);
        QString text=out.readAll();
        file.close();

        tedit->setPlainText(text);

        setWindowTitle("Text Editor - "+currentfile);
    }
    w2->close();
}

void MainWindow::cansel()
{
    w1->close();
    w2->close();
}

void MainWindow::star()
{
    if(currentfile.isEmpty())
        setWindowTitle("Text Editor - New Text*");
    else{
        if(isChanged()){
            setWindowTitle("Text Editor - "+currentfile+"*");
        }
        else setWindowTitle("Text Editor - "+currentfile);
    }
}

void MainWindow::setFont(QFont f)
{
    f.setPointSize(15);
    tedit->setFont(f);
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    if(!currentfile.isEmpty()){
        if(isChanged()){
            QMessageBox::StandardButton btn=QMessageBox::question(this,"Exit?","Do You Want To Save Changes?",QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
            if(btn==QMessageBox::Yes){
                on_actionSave_triggered();
                e->accept();
            }
            else if(btn==QMessageBox::No)
                e->accept();
            else e->ignore();
        }
        else e->accept();
    }
    else {
        if(tedit->toPlainText().isEmpty())
            e->accept();
        else{QMessageBox::StandardButton btn=QMessageBox::question(this,"Exit?","Do You Want To Save Changes?",QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
            if(btn==QMessageBox::Yes){
                on_actionSave_triggered();
                e->accept();
            }
            else if(btn==QMessageBox::No)
                e->accept();
            else e->ignore();
        }
    }
}

bool MainWindow::isChanged()
{
    QFile file(currentfile);
    if(!file.open(QFile::ReadOnly|QFile::Text)){
        QMessageBox::critical(this,"Error","Sorry, A problem occurred!!!");
        exit(0);
    }
    QTextStream out(&file);
    QString text=out.readAll();
    file.close();

    if(tedit->toPlainText().compare(text))
        return true;
    return false;
}

void MainWindow::ShortCuts()
{
    QShortcut* osh = new QShortcut(QKeySequence(Qt::Key_Control,Qt::Key_O),this);
    QObject::connect(osh,&QShortcut::activated,this,&MainWindow::on_actionOpen_triggered);

    QShortcut* nsh = new QShortcut(QKeySequence(Qt::Key_Control,Qt::Key_N),this);
    QObject::connect(nsh,&QShortcut::activated,this,&MainWindow::on_actionNew_triggered);

    QShortcut* ssh = new QShortcut(QKeySequence(Qt::Key_Control,Qt::Key_S),this);
    QObject::connect(ssh,&QShortcut::activated,this,&MainWindow::on_actionSave_triggered);

    QShortcut* ssh2 = new QShortcut(QKeySequence(Qt::Key_Control,Qt::Key_Shift,Qt::Key_S),this);
    QObject::connect(ssh2,&QShortcut::activated,this,&MainWindow::on_actionSave_As_triggered);

    QShortcut* zish = new QShortcut(QKeySequence(Qt::Key_Control,Qt::Key_Plus),this);
    QObject::connect(zish,&QShortcut::activated,this,&MainWindow::on_actionZoom_In_triggered);

    QShortcut* zosh = new QShortcut(QKeySequence(Qt::Key_Control,Qt::Key_Minus),this);
    QObject::connect(zosh,&QShortcut::activated,this,&MainWindow::on_actionZoom_Out_triggered);

    QShortcut* dzsh = new QShortcut(QKeySequence(Qt::Key_Control,Qt::Key_0),this);
    QObject::connect(dzsh,&QShortcut::activated,this,&MainWindow::on_actionDefult_Zoom_triggered);

    QShortcut* esh = new QShortcut(QKeySequence(Qt::Key_Shift,Qt::Key_Escape),this);
    QObject::connect(esh,&QShortcut::activated,this,&MainWindow::on_actionExit_triggered);
}

//void MainWindow::keyPressEvent(QKeyEvent *e)
//{
//    if(e->key()==Qt::Key_Control && e->key()==Qt::Key_S)
//        on_actionSave_triggered();
//}

void MainWindow::on_actionZoom_In_triggered()
{
    QFont f=tedit->font();
    f.setPointSize(f.pointSize()+1);
    tedit->setFont(f);
}

void MainWindow::on_actionZoom_Out_triggered()
{
    QFont f=tedit->font();
    int size=f.pointSize()-1;
    if(size>=0)
        f.setPointSize(size);
    else f.setPointSize(0);
    tedit->setFont(f);
}

void MainWindow::on_actionDefult_Zoom_triggered()
{
    QFont f=tedit->font();
    f.setPointSize(15);
    tedit->setFont(f);
}
