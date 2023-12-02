
#include "three.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QRadioButton>
#include <QPushButton>
#include <QPlainTextEdit>


void Three::setFontUnder(bool checked)
{
    QFont font = txtEdit->font();
    font.setUnderline(checked);
    txtEdit->setFont(font);
}

void Three::setFontItalic(bool checked)
{
    QFont font = txtEdit->font();
    font.setItalic(checked);
    txtEdit->setFont(font);
}

void Three::setFontBold(bool checked)
{
    QFont font = txtEdit->font();
    font.setBold(checked);
    txtEdit->setFont(font);
}

void Three::setFontColor()
{
    QPalette palet = txtEdit->palette();
    if(radioBlack->isChecked())
        palet.setColor(QPalette::Text, Qt::black);
    if(radioBlue->isChecked())
        palet.setColor(QPalette::Text, Qt::blue);
    if(radioRed->isChecked())
        palet.setColor(QPalette::Text, Qt::red);
    txtEdit->setPalette(palet);
}

void Three::clearText()
{
    txtEdit->clear();
}

Three::Three(QWidget *parent)
    : QDialog(parent)
{
    chkBoxUnder = new QCheckBox("下划线");
    chkBoxItalic = new QCheckBox("斜体");
    chkBoxBold = new QCheckBox("加粗");
    QHBoxLayout *HlayFont = new QHBoxLayout();
    HlayFont->addWidget(chkBoxUnder);
    HlayFont->addWidget(chkBoxItalic);
    HlayFont->addWidget(chkBoxBold);

    radioBlack = new QRadioButton("黑色");
    radioBlue = new QRadioButton("蓝色");
    radioRed = new QRadioButton("红色");
    QHBoxLayout *HlayColor = new QHBoxLayout();
    HlayColor->addWidget(radioBlack);
    HlayColor->addWidget(radioBlue);
    HlayColor->addWidget(radioRed);

    txtEdit = new QPlainTextEdit();
    txtEdit->setPlainText("Qt6.5 Code.");
    QFont font = txtEdit->font();
    font.setPointSize(20);
    txtEdit->setFont(font);

    btnClear = new QPushButton("清空");
    btnOK = new QPushButton("确认");
    btnClose = new QPushButton("退出");
    QHBoxLayout *HlayBtn = new QHBoxLayout();
    HlayBtn->addStretch(1);
    HlayBtn->addWidget(btnClear);
    HlayBtn->addStretch(2);
    HlayBtn->addWidget(btnOK);
    HlayBtn->addWidget(btnClose);

    QVBoxLayout *VlayDlg = new QVBoxLayout();
    VlayDlg->addLayout(HlayFont);
    VlayDlg->addLayout(HlayColor);
    VlayDlg->addWidget(txtEdit);
    VlayDlg->addLayout(HlayBtn);
    setLayout(VlayDlg);

    setWindowTitle("CodeUI");

    connect(chkBoxUnder, SIGNAL(clicked(bool)), this, SLOT(setFontUnder(bool)));
    connect(chkBoxItalic, SIGNAL(clicked(bool)), this, SLOT(setFontItalic(bool)));
    connect(chkBoxBold, SIGNAL(clicked(bool)), this, SLOT(setFontBold(bool)));
    connect(radioBlack, SIGNAL(clicked(bool)), this, SLOT(setFontColor()));
    connect(radioBlue, SIGNAL(clicked(bool)), this, SLOT(setFontColor()));
    connect(radioRed, SIGNAL(clicked(bool)), this, SLOT(setFontColor()));
    connect(btnClear, SIGNAL(clicked()), this, SLOT(clearText()));
    connect(btnOK, SIGNAL(clicked()), this, SLOT(accept()));
    connect(btnClose, SIGNAL(clicked()), this, SLOT(close()));
}

Three::~Three()
{
}


