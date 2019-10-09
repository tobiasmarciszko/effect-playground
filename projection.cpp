#include "projection.h"
#include "effect.h"
#include "QRgb"
#include <cmath>

projection::projection()
{
    // Initialize framebuffer
    framebuffer = QImage(320, 240, QImage::Format_RGB16);
    framebuffer.fill(qRgb(0,0,0));
}

void projection::update()
{
    framebuffer.fill(qRgb(0,0,0));

    rotateX(bl);
    rotateX(br);
    rotateX(tl);
    rotateX(tr);
    rotateX(blz);
    rotateX(brz);
    rotateX(tlz);
    rotateX(trz);

    rotateY(bl);
    rotateY(br);
    rotateY(tl);
    rotateY(tr);
    rotateY(blz);
    rotateY(brz);
    rotateY(tlz);
    rotateY(trz);

    rotateZ(bl);
    rotateZ(br);
    rotateZ(tl);
    rotateZ(tr);
    rotateZ(blz);
    rotateZ(brz);
    rotateZ(tlz);
    rotateZ(trz);

    point2 blr, brr, tlr, trr;
    point2 blrz, brrz, tlrz, trrz;

    blr = worldToScreen(bl);
    brr = worldToScreen(br);
    tlr = worldToScreen(tl);
    trr = worldToScreen(tr);

    blrz = worldToScreen(blz);
    brrz = worldToScreen(brz);
    tlrz = worldToScreen(tlz);
    trrz = worldToScreen(trz);

    framebuffer.setPixel(blr.x, blr.y, qRgb(255, 255, 255));
    framebuffer.setPixel(brr.x, brr.y, qRgb(255, 255, 255));
    framebuffer.setPixel(tlr.x, tlr.y, qRgb(255, 255, 255));
    framebuffer.setPixel(trr.x, trr.y, qRgb(255, 255, 255));

    framebuffer.setPixel(blrz.x, blrz.y, qRgb(255, 255, 255));
    framebuffer.setPixel(brrz.x, brrz.y, qRgb(255, 255, 255));
    framebuffer.setPixel(tlrz.x, tlrz.y, qRgb(255, 255, 255));
    framebuffer.setPixel(trrz.x, trrz.y, qRgb(255, 255, 255));

    // frontmost square
    drawLine(blr, brr);
    drawLine(blr, tlr);
    drawLine(tlr, trr);
    drawLine(brr, trr);

    // z square
    drawLine(blrz, brrz);
    drawLine(blrz, tlrz);
    drawLine(tlrz, trrz);
    drawLine(brrz, trrz);

    // connect the squares
    drawLine(blr, blrz);
    drawLine(brr, brrz);
    drawLine(tlr, tlrz);
    drawLine(trr, trrz);
}

point2 projection::worldToScreen(point3 &p) {
    float factor = 320.0;
    return {p.x / p.z * factor + 160, p.y / p.z * factor + 120};
}

// cos(angle) = 1
// sin(angle) = angle
void projection::rotateX(point3 &p, float angle) {
    p.z -= 6.0f;
    p.y = p.y - p.z*angle;
    p.z = p.y*angle + p.z;
    p.z += 6.0f;
}

void projection::rotateY(point3 &p, float angle) {
    p.z -= 6.0f;
    p.x = p.x + p.z*angle;
    p.z = -p.x*angle + p.z;
    p.z += 6.0f;
}

void projection::rotateZ(point3 &p, float angle) {
    p.x = p.x - p.y*angle;
    p.y = p.y + p.x*angle;
}

void projection::drawLine(const point2& p0, const point2& p1, const uint color) {
    drawLine(p0.x, p0.y, p1.x, p1.y, color);
}

void projection::drawLine(int x0, int y0, const int x1, const int y1, const uint color) {
    const auto dx = abs(x1 - x0);
    const auto dy = abs(y1 - y0);
    const auto sx = (x0 < x1) ? 1 : -1;
    const auto sy = (y0 < y1) ? 1 : -1;
    auto err = dx - dy;

    while (true) {
       if (x0 >= 0 &&
           y0 >= 0 &&
           x0 < 320 &&
           y0 < 240) {
            framebuffer.setPixel(x0, y0, color);
       }

       if ((x0 == x1) && (y0 == y1)) break;
       const auto e2 = 2 * err;
       if (e2 > -dy) { err -= dy; x0 += sx; }
       if (e2 < dx) { err += dx; y0 += sy; }
    }
}
