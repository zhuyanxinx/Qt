#ifndef TFORMDOC_H
#define TFORMDOC_H

#include <QWidget>

namespace Ui {
class TFormDoc;
}

class TFormDoc : public QWidget {
    Q_OBJECT

public:
    explicit TFormDoc(QWidget* parent = nullptr);
    ~TFormDoc();

private slots:
    void on_actionOpen_triggered();

    void on_actionFont_triggered();

    void on_actionSave_triggered();
signals:
    void titleChanged(QString title);

private:
    Ui::TFormDoc* ui;
};

#endif // TFORMDOC_H
