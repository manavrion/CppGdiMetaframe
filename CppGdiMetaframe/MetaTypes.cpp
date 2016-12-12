#include "stdafx.h"
namespace MetaFrame {
#define Override

    Size::Size() : width(0), height(0) {}

    Size::Size(const Size &size) : width(size.width), height(size.height) {}

    Size::Size(int width, int height) : width(width), height(height) {}

    Size MetaFrame::Size::operator+(const Size &sz) const {
        return Size(width + sz.width, height + sz.height);
    }

    Size Size::operator-(const Size &sz) const {
        return Size(width - sz.width, height - sz.height);
    }

    bool Size::operator==(const Size &sz) const {
        return (width == sz.width) && (height == sz.height);
    }

    bool Size::empty() const {
        return (width == 0 && height == 0);
    }

    Rect Size::toRect() const {
        return Rect(0, 0, width, height);
    }

    Size::operator const Gdiplus::Size() const {
        return Gdiplus::Size(width, height);
    }

    Size::operator const Gdiplus::Rect() const {
        return Gdiplus::Rect(0, 0, width, height);
    }

    

    

    Rect::Rect() : x(0), y(0), width(0), height(0) {}

    Rect::Rect(const Point &location, const Size &size) : x(location.x), y(location.y), width(size.width), height(size.height) {}

    Rect::Rect(const Rect & a, const Rect & b) {
        int right = min(a.getRightPos(), b.getRightPos());
        int bottom = min(a.getBottomPos(), b.getBottomPos());
        int left = max(a.getLeftPos(), b.getLeftPos());
        int top = max(a.getTopPos(), b.getTopPos());
        this->x = left;
        this->y = top;
        this->width = max(right - left, 0);
        this->height = max(bottom - top, 0);
    }

    Rect::Rect(RECT lprect) : x(lprect.left), y(lprect.top), width(lprect.right - x), height(lprect.bottom - y) {  }

    Rect::Rect(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}

    Point Rect::getLocation() const {
        return Point(x, y);
    }

    Size Rect::getSize() const {
        return Size(width, height);
    }

    Rect Rect::getBounds() const {
        return *this;
    }

    int Rect::getLeftPos() const {
        return x;
    }

    int Rect::getTopPos() const {
        return y;
    }

    int Rect::getRightPos() const {
        return x + width;
    }

    int Rect::getBottomPos() const {
        return y + height;
    }

    void Rect::setSize(const Size &size) {
        this->width = size.width;
        this->height = size.height;
    }

    void Rect::setPoint(const Point &point) {
        x = point.x;
        y = point.y;
    }

    bool Rect::isEmptyArea() const {
        return (width <= 0) || (height <= 0);
    }

    bool Rect::contains(int x, int y) const {
        return (x >= this->x && x < this->x + this->width) &&
            (y >= this->y && y < this->y + this->height);
    }

    bool Rect::contains(const Point &pt) const {
        return contains(pt.x, pt.y);
    }

    bool Rect::contains(const PointF & pt) const {
        return (pt.x >= this->x && pt.x < this->x + this->width) &&
            (pt.y >= this->y && pt.y < this->y + this->height);
    }

    bool Rect::contains(Rect &rect) const {
        return (x <= rect.x) && (rect.getRightPos() <= getRightPos()) &&
            (y <= rect.y) && (rect.getBottomPos() <= getBottomPos());
    }

    void Rect::inflate(int dx, int dy) {
        x -= dx;
        y -= dy;
        width += 2 * dx;
        height += 2 * dy;
    }

    void Rect::inflate(const Point &point) {
        inflate(point.x, point.y);
    }

    bool Rect::intersect(const Rect &rect) const {
        const Rect &a = *this;
        const Rect &b = rect;
        Rect c;
        int right = min(a.getRightPos(), b.getRightPos());
        int bottom = min(a.getBottomPos(), b.getBottomPos());
        int left = max(a.getLeftPos(), b.getLeftPos());
        int top = max(a.getTopPos(), b.getTopPos());
        c.x = left;
        c.y = top;
        c.width = right - left;
        c.height = bottom - top;
        return !c.isEmptyArea();
    }

    void Rect::offset(const Point &point) {
        offset(point.x, point.y);
    }

    void Rect::offset(int dx, int dy) {
        x += dx;
        y += dy;
    }

    inline void Rect::shiftTo(Point point) {
        x += point.x;
        y += point.y;
        //width += point.x;
        //height += point.y;
    }

    Rect::operator const Gdiplus::Rect() const {
        return Gdiplus::Rect(x, y, width, height);
    }

    Rect::operator const Gdiplus::RectF() const {
        return Gdiplus::RectF(x, y, width, height);
    }

    Rect::operator const RECT() const {
        RECT a;
        a.left = x;
        a.top = y;
        a.right = this->getRightPos();
        a.bottom = this->getBottomPos();
        return a;
    }


    Color::Color() : red(0), green(0), blue(0), alpha(255) {}

    Color::Color(byte red, byte green, byte blue) : red(red), green(green), blue(blue), alpha(255){}

    Color::Color(byte red, byte green, byte blue, byte alpha) : red(red), green(green), blue(blue), alpha(alpha) {}

    Color::Color(const Color &color) : red(color.red), green(color.green), blue(color.blue), alpha(color.alpha) {}

    byte Color::getAlpha() const {
        return alpha;
    }

    byte Color::getRed() const {
        return red;
    }

    byte Color::getGreen() const {
        return green;
    }

    byte Color::getBlue() const {
        return blue;
    }

    Color::operator const Gdiplus::Color() const {
        return Gdiplus::Color(alpha, red, green, blue);
    }
}