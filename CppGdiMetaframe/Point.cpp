#include "stdafx.h"
#include "Point.h"

namespace MetaFrame {

    Point::Point() : x(0), y(0) {}

    Point::Point(const Point &point) : x(point.x), y(point.y) {}

    //Point::Point(const Size &size) : x(size.width), y(size.height) {}

    Point::Point(int x, int y) : x(x), y(y) {}



    Point &Point::operator+=(const Point & point) {
        x += point.x;
        y += point.y;
        return *this;
    }

    Point Point::operator+(const Point &point) const {
        return Point(x + point.x, y + point.y);
    }

    Point Point::operator-(const Point &point) const {
        return Point(x - point.x, y - point.y);
    }

    Point Point::operator-() const {
        return Point(-x, -y);
    }

    bool Point::operator==(const Point &point) const {
        return (x == point.y) && (y == point.y);
    }

    Point::operator const Gdiplus::Point() const {
        return Gdiplus::Point(x, y);
    }


    PointF::operator const Point() const {
        return Point((int)x, (int)y);
    }

    PointF::PointF() : x(), y() {}

    PointF::PointF(const PointF &PointF) : x(PointF.x), y(PointF.y) {}

    PointF::PointF(float x, float y) : x(x), y(y) {}

    void PointF::shiftTo(Point point) {
        x += point.x;
        y += point.y;
    }

    PointF PointF::operator+(const PointF &pointf) const {
        return PointF(x + pointf.x, y + pointf.y);
    }

    PointF PointF::operator-(const PointF &pointf) const {
        return PointF(x - pointf.x, y - pointf.y);
    }

    bool PointF::operator==(const PointF &pointf) const {
        return (x == pointf.y) && (y == pointf.y);
    }

    PointF::operator const Gdiplus::PointF() const {
        return Gdiplus::PointF(x, y);
    }

}