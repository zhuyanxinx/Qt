
#include "qtmetainfo.h"

#include <QMetaClassInfo>
#include <QMetaProperty>

#include "tperson.h"
#include "ui_qtmetainfo.h"

QtMetaInfo::QtMetaInfo(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::QtMetaInfo)
{
    ui->setupUi(this);
    ui->spinBoy->setProperty("isBoy", true);
    ui->spinGirl->setProperty("isBoy", false);

    boy = new TPerson("XY", this);
    boy->setAge(17);
    boy->setProperty("sex", "boy");
    girl = new TPerson("YY", this);
    girl->setAge(17);
    girl->setProperty("sex", "girl");
    connect(boy, SIGNAL(ageChanged(int)), this, SLOT(ageChanged(int)));
    connect(girl, SIGNAL(ageChanged(int)), this, SLOT(ageChanged(int)));
    connect(boy, SIGNAL(ageChanged(int)), ui->spinBoy, SLOT(setValue(int)));
    connect(girl, SIGNAL(ageChanged(int)), ui->spinGirl, SLOT(setValue(int)));
    connect(ui->spinGirl, SIGNAL(valueChanged(int)), this, SLOT(spinChanged(int)));
    connect(ui->spinBoy, SIGNAL(valueChanged(int)), this, SLOT(spinChanged(int)));
}

QtMetaInfo::~QtMetaInfo() { delete ui; }

void QtMetaInfo::ageChanged(int value)
{
    TPerson* person = qobject_cast<TPerson*>(sender());
    QString sex = person->property("sex").toString();
    QString name = person->property("name").toString();
    QString content = QString("sex:%1, age:%2, name:%3").arg(sex).arg(value).arg(name);
    ui->txtPrint->appendPlainText(content);
}

void QtMetaInfo::spinChanged(int value)
{
    QSpinBox* spinBox = qobject_cast<QSpinBox*>(sender());
    if (spinBox->property("isBoy").toBool()) {
        boy->setAge(value);
    } else {
        girl->setAge(value);
    }
}

void QtMetaInfo::on_btnBoyInc_clicked() { boy->incAge(); }

void QtMetaInfo::on_btnGirlInc_clicked() { girl->incAge(); }

void QtMetaInfo::on_btnClear_clicked() { ui->txtPrint->clear(); }

void QtMetaInfo::on_btnQtMeta_clicked()
{
    const QMetaObject* meta = boy->metaObject();
    ui->txtPrint->appendPlainText(QString("Class:%1\n").arg(meta->className()));
    ui->txtPrint->appendPlainText("Prop:");
    for (int i = meta->propertyOffset(); i < meta->propertyCount(); ++i) {
        const char* name = meta->property(i).name();
        QString value = boy->property(name).toString();
        ui->txtPrint->appendPlainText(QString("%1--->%2").arg(name, value));
    }

    ui->txtPrint->appendPlainText("ClassInfo:");
    for (int i = meta->classInfoOffset(); i < meta->classInfoCount(); ++i) {
        QMetaClassInfo clsInfo = meta->classInfo(i);
        ui->txtPrint->appendPlainText(QString("%1--->%2").arg(clsInfo.name(), clsInfo.value()));
    }
}
