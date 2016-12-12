#pragma once
#include "stdafx.h"
#include "String.h"
namespace MetaFrame {

    //typedef Gdiplus::Color Color;//todo rewrite


    template<typename T1, typename T2>
    using HashMap = std::unordered_map<T1, T2>;

    template<typename T>
    using ArrayList = std::vector<T>;

    class Rect;

    class Size {
    public:

        Size();
        Size(const Size& size);
        Size(int width, int height);

        int width;
        int height;

        Size operator+(const Size &sz) const;
        Size operator-(const Size &sz) const;
        bool operator==(const Size &sz) const;
        bool empty() const;

        Rect toRect() const;

        //platform
        operator const Gdiplus::Size() const;
        operator const Gdiplus::Rect() const;
    };

    class Point {
    public:
        Point();
        Point(const Point &point);
        Point(const Size &size);
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

        void shiftTo(Point point) {
            x += point.x;
            y += point.y;
        }

        PointF operator+(const PointF& pointf) const;
        PointF operator-(const PointF& pointf) const;
        bool operator==(const PointF& pointf) const;

        operator const Gdiplus::PointF() const;

        explicit operator const Point() const;
    };


    class Rect {
    public:
        Rect();
        Rect(int x, int y, int width, int height);
        Rect(const Point& location, const Size& size);

        Rect(const Rect &a, const Rect &b);

        //platform
        Rect(RECT lprect);

        int x;
        int y;
        int width;
        int height;

        Point getLocation() const;
        Size getSize() const;

        Rect getBounds() const;
        int getLeftPos() const;
        int getTopPos() const;
        int getRightPos() const;
        int getBottomPos() const;


        void setSize(const Size &size);
        void setPoint(const Point &point);

        bool isEmptyArea() const;

        virtual bool contains(int x, int y) const;
        virtual bool contains(const Point& pt) const;
        virtual bool contains(const PointF& pt) const;
        virtual bool contains(Rect& rect) const;
        virtual void inflate(int dx, int dy);
        virtual void inflate(const Point& point);

        virtual bool intersect(const Rect& rect) const;

        virtual void offset(const Point& point);
        virtual void offset(int dx, int dy);

        virtual void shiftTo(Point point);


        //platform
        operator const Gdiplus::Rect() const;
        explicit operator const Gdiplus::RectF() const;
        operator const RECT() const;
    };

    class Color {
    public:
        Color();
        Color(byte red, byte green, byte blue);
        Color(byte red, byte green, byte blue, byte alpha);
        Color(const Color &color);

        byte red;
        byte green;
        byte blue;
        byte alpha;

        byte getAlpha() const;
        byte getRed() const;
        byte getGreen() const;
        byte getBlue() const;

        //platform
        operator const Gdiplus::Color() const;

    };

    struct Margin {
        int left;
        int right;
        int top;
        int bottom;
        Margin( int left,
                int right,
                int top,
                int bottom) :
            left(left),
            right(right),
            top(top),
            bottom(bottom) {
        };
        Margin():
            left(0),
            right(0),
            top(0),
            bottom(0) {};
    };


    enum class HorizontalAlignment {
        Absolute,
        Left,
        Center,
        Right,
        Stretch
    };

    enum class VerticalAlignment {
        Absolute,
        Top,
        Center,
        Bottom,
        Stretch
    };
}