#include <QLineEdit>
#include <QKeyEvent>

class MyTextEdit : public QLineEdit
{
    Q_OBJECT
signals:
	void returnKey_pressed();
public:
	MyTextEdit();
    void keyPressEvent(QKeyEvent *event);
};