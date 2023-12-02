
#include "edittext.h"
#include "./ui_edittext.h"


EditText::EditText(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditText)
{
    ui->setupUi(this);
    connect(ui->rbtnBlue, SIGNAL(clicked()), this, SLOT(set_FontColor()));
    connect(ui->rbtnGray, SIGNAL(clicked()), this, SLOT(set_FontColor()));
    connect(ui->rbtnRed, SIGNAL(clicked()), this, SLOT(set_FontColor()));
}

EditText::~EditText()
{
    delete ui;
}



void EditText::on_pbtnClear_clicked()
{
    ui->plainTextEdit->clear();
}


void EditText::on_chbUnderLine_clicked(bool checked)
{
    QFont font = ui->plainTextEdit->font();
    font.setUnderline(checked);
    ui->plainTextEdit->setFont(font);
}


void EditText::on_chbItailc_clicked(bool checked)
{
    QFont font = ui->plainTextEdit->font();
    font.setItalic(checked);
    ui->plainTextEdit->setFont(font);
}


void EditText::on_chbBold_clicked(bool checked)
{
    QFont font = ui->plainTextEdit->font();
    font.setBold(checked);
    ui->plainTextEdit->setFont(font);
}

void EditText::set_FontColor()
{
    QPalette palet = ui->plainTextEdit->palette();

    if(ui->rbtnBlue->isChecked())
        palet.setColor(QPalette::Text, Qt::blue);
    if(ui->rbtnGray->isChecked())
        palet.setColor(QPalette::Text, Qt::gray);
    if(ui->rbtnRed->isChecked())
        palet.setColor(QPalette::Text, Qt::red);

    ui->plainTextEdit->setPalette(palet);
}

