#ifndef PROJECTION_H
#define PROJECTION_H

#include <QObject>
#include "effect.h"

struct point3 {
    float x;
    float y;
    float z;
};

struct point2 {
    float x;
    float y;
};

class projection : public IEffect
{
public:
    projection();

public slots:
    virtual void update();

private:
    void drawLine(const point2& p0, const point2& p1, const uint color = qRgb(255, 255, 255));
    void drawLine(int x0, int y0, const int x1, const int y1, const uint color);

    point3 bl{-1, -1, 5.0};
    point3 br{1, -1, 5.0};
    point3 tl{-1, 1, 5.0};
    point3 tr{1, 1, 5.0};

    point3 blz{-1, -1, 7.0};
    point3 brz{1, -1, 7.0};
    point3 tlz{-1, 1, 7.0};
    point3 trz{1, 1, 7.0};

    point2 worldToScreen(point3& p);
    void rotateX(point3& p, float angle = 0.017444444f);
    void rotateY(point3& p, float angle = 0.017444444f);
    void rotateZ(point3& p, float angle = 0.017444444f);
};

#endif // PROJECTION_H
