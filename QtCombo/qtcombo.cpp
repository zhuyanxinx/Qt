#include "qtcombo.h"
#include "./ui_qtcombo.h"

QtCombo::QtCombo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QtCombo)
{
    ui->setupUi(this);
}

QtCombo::~QtCombo()
{
    delete ui;
}


void QtCombo::on_btnClear_clicked()
{
    ui->txtShow->clear();
}


void QtCombo::on_btnInitCity_clicked()
{
    QList<QString> lstCity;
    lstCity.push_back("北京");
    lstCity.push_back("天津");
    lstCity.push_back("重庆");
    lstCity.push_back("广州");
    lstCity.push_back("成都");
    lstCity.push_back("乌鲁木齐");

    ui->comboCity->clear();
    ui->comboCity->addItems(lstCity);
    for (int i = 0; i < lstCity.size(); ++i) {
        //        ui->comboCity->addItem();
    }

}


void QtCombo::on_btnCityEditable_clicked(bool checked)
{
    ui->comboCity->setEditable(checked);
}


void QtCombo::on_btnClearCity_clicked()
{
    ui->comboCity->clear();
}


void QtCombo::on_btnInitCityNum_clicked()
{
    ui->comboCItyNum->clear();
    QMap<QString, int> mapCityNum;
    mapCityNum.insert("北京", 101);
    mapCityNum.insert("天津", 201);
    mapCityNum.insert("重庆", 301);
    mapCityNum.insert("广州", 401);
    mapCityNum.insert("成都", 501);
    mapCityNum.insert("乌鲁木齐", 601);

    foreach (const QString &city, mapCityNum.keys()) {
        ui->comboCItyNum->addItem(city, mapCityNum.value(city));
    }
}


void QtCombo::on_comboCity_currentTextChanged(const QString &text)
{
    ui->txtShow->appendPlainText(text);
}


void QtCombo::on_comboCItyNum_currentIndexChanged(int index)
{
    QString text = ui->comboCItyNum->currentText();
    QString data = ui->comboCItyNum->currentData().toString();
    ui->txtShow->appendPlainText(text+"--"+data);
}
