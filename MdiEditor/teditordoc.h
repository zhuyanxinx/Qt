#ifndef TEDITORDOC_H
#define TEDITORDOC_H

#include <QWidget>

namespace Ui {
class TEditorDoc;
}

class TEditorDoc : public QWidget {
    Q_OBJECT
public:
    void loadFromFile(QString& fname);
    QString currentFileName();
    bool fileOpened();
    void saveFile();

    void textCopy();
    void textCut();
    void textPaste();
    void setEditorFont();

private:
    QString mfileName;
    bool mfileOpened = false;

public:
    explicit TEditorDoc(QWidget* parent = nullptr);
    ~TEditorDoc();

private:
    Ui::TEditorDoc* ui;
};

#endif // TEDITORDOC_H
