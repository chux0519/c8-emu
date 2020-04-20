#ifndef MEMORYVIEWER_H
#define MEMORYVIEWER_H

#include <QListWidget>

class MemoryViewer
{
public:
    MemoryViewer(QListWidget *view, uint8_t *mem);
    void display(uint16_t pc);
    void reload(uint8_t *_mem);

private:
    QListWidget *listWidget;
    int rowNumber = 4;
};

#endif // MEMORYVIEWER_H
