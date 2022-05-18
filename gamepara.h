#ifndef GAMEPARA_H
#define GAMEPARA_H

#include <QWidget>

namespace Ui {
class gamepara;
}

class gamepara : public QWidget
{
    Q_OBJECT

public:
    explicit gamepara(QWidget *parent = nullptr);
    ~gamepara();

private:
    Ui::gamepara *ui;
};

#endif // GAMEPARA_H
