#pragma once
#include <touchgfx/widgets/Widget.hpp>
#include <touchgfx/hal/Types.hpp>
#include <touchgfx/Color.hpp>
#include <cstdlib>

class LineWidget : public touchgfx::Widget
{
public:
    LineWidget() : x1(0), y1(0), x2(0), y2(0), width(4), color(0x0000) {}

    void setLine(int x1_, int y1_, int x2_, int y2_) {
        x1 = x1_; y1 = y1_; x2 = x2_; y2 = y2_;
        int minX = x1 < x2 ? x1 : x2;
        int minY = y1 < y2 ? y1 : y2;
        int maxX = x1 > x2 ? x1 : x2;
        int maxY = y1 > y2 ? y1 : y2;
        setPosition(minX - width, minY - width, (maxX-minX) + 2*width, (maxY-minY) + 2*width);
        invalidate();
    }

    void setColor(touchgfx::colortype c) { color = c; invalidate(); }
    void setLineWidth(int w) { width = w; invalidate(); }

    virtual void draw(const touchgfx::Rect& invalidatedArea) const override {
        uint16_t* fb = reinterpret_cast<uint16_t*>(touchgfx::HAL::getInstance()->lockFrameBuffer());
        if (!fb) return;

        int min_x = getX();
        int min_y = getY();
        int sx = x1 < x2 ? 1 : -1;
        int sy = y1 < y2 ? 1 : -1;
        int dx = std::abs(x2 - x1);
        int dy = -std::abs(y2 - y1);
        int err = dx + dy, e2;
        int px = x1, py = y1;

        do {
            for (int wx = -width/2; wx <= width/2; ++wx)
            for (int wy = -width/2; wy <= width/2; ++wy) {
                int draw_x = px - min_x + wx;
                int draw_y = py - min_y + wy;
                if (draw_x >= 0 && draw_x < getWidth() && draw_y >= 0 && draw_y < getHeight()) {
                    fb[(draw_y + getY()) * touchgfx::HAL::DISPLAY_WIDTH + (draw_x + getX())] = color;
                }
            }
            if (px == x2 && py == y2) break;
            e2 = 2 * err;
            if (e2 >= dy) { err += dy; px += sx; }
            if (e2 <= dx) { err += dx; py += sy; }
        } while (true);

        touchgfx::HAL::getInstance()->unlockFrameBuffer();
    }

    virtual touchgfx::Rect getSolidRect() const override { return getRect(); }

private:
    int x1, y1, x2, y2, width;
    touchgfx::colortype color;
};
