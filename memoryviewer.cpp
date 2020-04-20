#include "memoryviewer.h"

QString leftPadZero(QString s, int len) {
    while(s.length() < len) {
        s = "0" + s;
    }
    return s;
}

MemoryViewer::MemoryViewer(QListWidget *view, uint8_t *_mem):
    listWidget(view)
{
    reload(_mem);
}

void MemoryViewer::display(uint16_t pc) {
    int row = pc / rowNumber;
    listWidget->setCurrentRow(row);
    // move to bottom first, for align
    listWidget->scrollToBottom();
    listWidget->scrollToItem(listWidget->item(row - 2));
}

void MemoryViewer::reload(uint8_t *mem) {
    listWidget->clear();
    int pos = 0;
    // init
    for( int r=0; r< 4096 / rowNumber; r++ )
    {
        pos += rowNumber;
        QString sstr = "0x" + leftPadZero(QString::number(pos, 16).toUpper(), 4) + " |";
        for (int i = 0; i < rowNumber; i++) {
            uint8_t reg = mem[r * rowNumber + i];
            sstr +=  " 0x" + leftPadZero(QString::number(reg, 16).toUpper(), 2);
        }
        listWidget->addItem(sstr);
    }
}
