#ifndef KBDSETTINGDIALOG_H
#define KBDSETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class KbdSettingDialog;
}

class KbdSettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit KbdSettingDialog(QWidget *parent = nullptr);
    ~KbdSettingDialog();

private:
    Ui::KbdSettingDialog *ui;
};

#endif // KBDSETTINGDIALOG_H
