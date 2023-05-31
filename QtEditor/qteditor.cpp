
#include "qteditor.h"
#include "./ui_qteditor.h"

#include <QFontComboBox>
#include <QIcon>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include <QSpinBox>
#include <QToolButton>

QtEditor::QtEditor(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::QtEditor)
{
    ui->setupUi(this);

    QToolButton* fontFamliay = new QToolButton(this);
    fontFamliay->setEnabled(false);
    fontFamliay->setIcon(QIcon(":/icon/ziti.svg"));
    ui->toolBar->addWidget(fontFamliay);

    comboFont = new QFontComboBox(this);
    comboFont->setFont(ui->textEdit->font());
    comboFont->setMinimumWidth(120);
    comboFont->setMaximumWidth(150);
    ui->toolBar->addWidget(comboFont);

    QToolButton* fontSize = new QToolButton(this);
    fontSize->setEnabled(false);
    fontSize->setIcon(QIcon(":/icon/zitidaxiao.svg"));
    ui->toolBar->addWidget(fontSize);

    spinFontSize = new QSpinBox(this);
    spinFontSize->setMinimum(5);
    spinFontSize->setMaximum(50);
    spinFontSize->setValue(ui->textEdit->font().pointSize());
    spinFontSize->setMaximumWidth(100);
    spinFontSize->setMinimumWidth(50);
    ui->toolBar->addWidget(spinFontSize);

    ui->toolBar->addSeparator();
    ui->toolBar->addAction(ui->actionZhEn);
    ui->toolBar->addAction(ui->actionQuit);

    labStatus = new QLabel(this);
    labStatus->setMinimumWidth(200);
    labStatus->setText("file:");
    ui->statusbar->addWidget(labStatus);

    progress = new QProgressBar(this);
    progress->setMinimumWidth(300);
    progress->setMinimum(0);
    progress->setMaximum(100);
    progress->setValue(ui->textEdit->font().pointSize());
    ui->statusbar->addWidget(progress);

    labInfo = new QLabel(this);
    labInfo->setText("permanent");
    ui->statusbar->addPermanentWidget(labInfo);

    connect(spinFontSize, &QSpinBox::valueChanged, this, &QtEditor::onSpinFontSizeChanged);
    connect(comboFont, &QComboBox::currentTextChanged, this, &QtEditor::onComboFontChanged);
}

QtEditor::~QtEditor()
{
    delete ui;
}

void QtEditor::on_actionNewFile_triggered()
{
    ui->textEdit->clear();
    ui->textEdit->document()->setModified(false);
    labStatus->setText("file: new file");

    QTextCharFormat txtFmt = ui->textEdit->currentCharFormat();
    txtFmt.setFontPointSize(spinFontSize->text().toInt());
    ui->textEdit->setCurrentCharFormat(txtFmt);
}

void QtEditor::on_actionEdit_triggered()
{
    labStatus->setText("file: edit file");
}

void QtEditor::on_actionSave_triggered()
{
    ui->textEdit->document()->setModified(true);
    labStatus->setText("file: save file");
}

void QtEditor::on_textEdit_copyAvailable(bool b)
{
    ui->actionCopy->setEnabled(b);
    ui->actionCut->setEnabled(b);
    ui->actionPaste->setEnabled(ui->textEdit->canPaste());
}

void QtEditor::on_textEdit_selectionChanged()
{
    QTextCharFormat txtFmt = ui->textEdit->currentCharFormat();
    ui->actionBold->setChecked(txtFmt.font().bold());
    ui->actionItalic->setChecked(txtFmt.font().italic());
    ui->actionUnderline->setChecked(txtFmt.font().underline());
}

void QtEditor::on_actionBold_triggered(bool checked)
{
    QTextCharFormat txtFmt = ui->textEdit->currentCharFormat();
    txtFmt.setFontWeight(checked ? QFont::Bold : QFont::Normal);
    ui->textEdit->setCurrentCharFormat(txtFmt);
}

void QtEditor::on_actionItalic_triggered(bool checked)
{
    QTextCharFormat txtFmt = ui->textEdit->currentCharFormat();
    txtFmt.setFontItalic(checked);
    ui->textEdit->setCurrentCharFormat(txtFmt);
}

void QtEditor::on_actionUnderline_toggled(bool checked)
{
    QTextCharFormat txtFmt = ui->textEdit->currentCharFormat();
    txtFmt.setFontUnderline(checked);
    ui->textEdit->setCurrentCharFormat(txtFmt);
}

void QtEditor::onSpinFontSizeChanged(int fontSize)
{
    QTextCharFormat txtFmt = ui->textEdit->currentCharFormat();
    txtFmt.setFontPointSize(fontSize);
    ui->textEdit->setCurrentCharFormat(txtFmt);
    progress->setValue(fontSize);
}

void QtEditor::onComboFontChanged(const QFont& font)
{
    QTextCharFormat txtFmt = ui->textEdit->currentCharFormat();
    txtFmt.setFont(font);
    ui->textEdit->setCurrentCharFormat(txtFmt);
    labInfo->setText(font.family());
}

void QtEditor::on_actionQuit_triggered()
{
    qApp->quit();
}

void QtEditor::on_actionZhEn_triggered(bool checked)
{
    QString text = checked ? tr("en_US") : tr("zh_CN");
    QIcon* icon = new QIcon(checked ? ":/icon/lang_en.svg" : ":/icon/lang_cn.svg");
    ui->actionZhEn->setText(text);
    ui->actionZhEn->setIcon(*icon);
    ui->actionZhEn->setChecked(!checked);
}
