#ifndef MEMORYVIEWER_H
#define MEMORYVIEWER_H

#include <QListWidget>

class MemoryViewer
{
public:
    MemoryViewer(QListWidget *view, uint8_t *mem);
    void display();

private:
    QListWidget *listWidget;
    uint8_t *mem;
};

#endif // MEMORYVIEWER_H
