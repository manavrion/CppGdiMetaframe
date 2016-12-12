#pragma once
#include "MetaTypes.h"

namespace MetaFrame {

    class Point {
    public:
        Point();
        Point(const Point &point);
        //Point(const Size &size);
        Point(int x, int y);

        int x;
        int y;

        void shiftTo(Point point) {
            x += point.x;
            y += point.y;
        }

        Point &operator+=(const Point& point);

        Point operator+(const Point& point) const;
        Point operator-(const Point& point) const;
        Point operator-() const;
        bool operator==(const Point &point) const;

        operator const Gdiplus::Point() const;
    };

    class PointF {
    public:
        PointF();
        PointF(const PointF &PointF);

        PointF(float x, float y);

        float x;
        float y;

        void shiftTo(Point point);

        PointF operator+(const PointF& pointf) const;
        PointF operator-(const PointF& pointf) const;
        bool operator==(const PointF& pointf) const;

        operator const Gdiplus::PointF() const;

        explicit operator const Point() const;
    };

}