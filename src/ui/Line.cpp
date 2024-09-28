#include "ui/Line.h"

Line::Line(QWidget *parent) : QFrame(parent) {
    setFrameShape(HLine);
    setFrameShadow(Sunken);
}
