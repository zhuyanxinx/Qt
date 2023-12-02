#include "mdieditor.h"
#include "tlogindialog.h"

#include <QApplication>

int main(int argc, char* argv[])
{

    QApplication a(argc, argv);

    TLoginDialog* loginDlg = new TLoginDialog;
    loginDlg->setMaximumWidth(600);
    loginDlg->setMaximumHeight(400);
    if (loginDlg->exec() != QDialog::Accepted) {
        return 0;
    }

    MdiEditor w;
    w.show();
    return a.exec();
}
