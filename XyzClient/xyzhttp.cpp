#include "xyzhttp.h"
#include "./ui_xyzhttp.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QStringLiteral>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

XyzHttp::XyzHttp(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::XyzHttp)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &XyzHttp::replay);
}

XyzHttp::~XyzHttp()
{
    delete ui;
}

void XyzHttp::replay(QNetworkReply* reply)
{
    QByteArray bytes = reply->readAll();
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(bytes, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << QStringLiteral("Reply json error!");
        return;
    }
    QByteArray byteArray = jsonDoc.toJson(QJsonDocument::Compact);
    QString body(byteArray);
    ui->txtBody->appendPlainText(body);
    if (jsonDoc.isObject()) {
        QJsonObject jsonO = jsonDoc.object();
        qDebug() << jsonO["state"].toString();
    }
}

void XyzHttp::on_cboMethod_currentTextChanged(const QString& arg1)
{
}

void XyzHttp::on_btnSend_clicked()
{
    url = ui->editUrl->text();
    method = ui->cboMethod->currentText();
    contentType = ui->cboContType->currentText();
    charset = ui->cboCharset->currentText();
    QString json = ui->txtJson->toPlainText();

    QJsonDocument document = QJsonDocument::fromJson(json.toLocal8Bit().data());
    if (document.isNull()) {
        qDebug() << "Null json:" << json;
    }
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);

    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, contentType);

    QStringList options;
    options << "POST"
            << "GET"
            << "DELETE"
            << "PUT";
    switch (options.indexOf(method)) {
    case 0:
        manager->post(request, byteArray);
        break;
    case 1:
        manager->get(request);
        break;
    case 2:
        break;
    case 3:
        break;
    default:
        break;
    }
}
