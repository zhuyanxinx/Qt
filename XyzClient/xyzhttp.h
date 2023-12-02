#ifndef XYZHTTP_H
#define XYZHTTP_H

#include <QMainWindow>

class QNetworkAccessManager;
class QNetworkReply;

QT_BEGIN_NAMESPACE
namespace Ui {
class XyzHttp;
}
QT_END_NAMESPACE

class XyzHttp : public QMainWindow {
    Q_OBJECT

public:
    XyzHttp(QWidget* parent = nullptr);
    ~XyzHttp();

    void post();
    void replay(QNetworkReply* reply);

private slots:
    void on_cboMethod_currentTextChanged(const QString& arg1);

    void on_btnSend_clicked();

private:
    Ui::XyzHttp* ui;
    QNetworkAccessManager* manager;
    QString url;
    QString method;
    QString contentType;
    QString charset;
};
#endif // XYZHTTP_H
