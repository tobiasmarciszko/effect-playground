#include "tunnel.h"
#include "effect.h"
#include "QRgb"
#include "math.h"

// Code from https://lodev.org/cgtutor/tunnel.html

static QVector<QRgb> palette = {
    qRgb(0x07,0x07,0x07),
    qRgb(0x1F,0x07,0x07),
    qRgb(0x2F,0x0F,0x07),
    qRgb(0x47,0x0F,0x07),
    qRgb(0x57,0x17,0x07),
    qRgb(0x67,0x1F,0x07),
    qRgb(0x77,0x1F,0x07),
    qRgb(0x8F,0x27,0x07),
    qRgb(0x9F,0x2F,0x07),
    qRgb(0xAF,0x3F,0x07),
    qRgb(0xBF,0x47,0x07),
    qRgb(0xC7,0x47,0x07),
    qRgb(0xDF,0x4F,0x07),
    qRgb(0xDF,0x57,0x07),
    qRgb(0xDF,0x57,0x07),
    qRgb(0xD7,0x5F,0x07),
    qRgb(0xD7,0x5F,0x07),
    qRgb(0xD7,0x67,0x0F),
    qRgb(0xCF,0x6F,0x0F),
    qRgb(0xCF,0x77,0x0F),
    qRgb(0xCF,0x7F,0x0F),
    qRgb(0xCF,0x87,0x17),
    qRgb(0xC7,0x87,0x17),
    qRgb(0xC7,0x8F,0x17),
    qRgb(0xC7,0x97,0x1F),
    qRgb(0xBF,0x9F,0x1F),
    qRgb(0xBF,0x9F,0x1F),
    qRgb(0xBF,0xA7,0x27),
    qRgb(0xBF,0xA7,0x27),
    qRgb(0xBF,0xAF,0x2F),
    qRgb(0xB7,0xAF,0x2F),
    qRgb(0xB7,0xB7,0x2F),
    qRgb(0xB7,0xB7,0x37),
    qRgb(0xCF,0xCF,0x6F),
    qRgb(0xDF,0xDF,0x9F),
    qRgb(0xEF,0xEF,0xC7),
    qRgb(0xFF,0xFF,0xFF)
};

static int distanceTable[240][320];
static int angleTable[240][320];

static uint texture[256][256];

static int elapsed = 0;

tunnel::tunnel()
{
    // Initialize framebuffer
    framebuffer = QImage(320, 240, QImage::Format_Indexed8);
    framebuffer.fill(0);
    framebuffer.setColorTable(palette);

    //generate texture
    for(uint y = 0; y < 256; y++)
    for(uint x = 0; x < 256; x++)
    {
        texture[y][x] = (x ^ y) % 37;
    }

    int w = 320;
    int h = 240;

    //generate non-linear transformation table
      for(int y = 0; y < h; y++)
      for(int x = 0; x < w; x++)
      {
        int angle, distance;
        float ratio = 16.0;
        distance = int(ratio * 256 / sqrt((x - w / 2.0) * (x - w / 2.0) + (y - h / 2.0) * (y - h / 2.0))) % 256;
        angle = (unsigned int)(0.5 * 256 * atan2(y - h / 2.0, x - w / 2.0) / 3.1416);
        distanceTable[y][x] = distance;
        angleTable[y][x] = angle;
      }
}

void tunnel::update()
{
    int h = 240;
    int w = 320;

    //calculate the shift values out of the animation value
        int shiftX = int(256 * elapsed / 100);
        int shiftY = int(256 * elapsed / 200);

        for(int y = 0; y < h; y++)
        for(int x = 0; x < w; x++)
        {
          //get the texel from the texture by using the tables, shifted with the animation values
          uint color = texture[(unsigned int)(distanceTable[y][x] + shiftX) % 256][(unsigned int)(angleTable[y][x] + shiftY) % 256];
          framebuffer.setPixel(x, y, color);
        }

    elapsed++;
}
