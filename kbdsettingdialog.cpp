#include "kbdsettingdialog.h"
#include "ui_kbdsettingdialog.h"

KbdSettingDialog::KbdSettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KbdSettingDialog)
{
    ui->setupUi(this);
}

KbdSettingDialog::~KbdSettingDialog()
{
    delete ui;
}
