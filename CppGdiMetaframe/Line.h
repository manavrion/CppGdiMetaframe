#pragma once

#include "FrameElement.h"

namespace MetaFrame {

    class GraphLine : public FrameElement {
    public:
        GraphLine() : FrameElement() {
            this->setHorizontalAlignment(HorizontalAlignment::Absolute);
            this->setVerticalAlignment(VerticalAlignment::Absolute);
            this->setAutoWidth(false);
            this->setAutoHeight(false);
        };


    public:

        virtual Rect getRect() {
            Rect rect(x, y, width, height);
            if (width < 0) {
                rect.x = x + width;
                rect.width = std::abs(rect.width);
            }
            if (height < 0) {
                rect.y = y + height;
                rect.height = std::abs(rect.height);
            }
            return rect;
        }

        PointF getPointOfBegin() {
            return PointF(x, y);
        }
        PointF getPointOfEnd() {
            return PointF(x + width, y + height);
        }
        Color getColor() {
            return color;
        }
        float getLineWidth() {
            return lineWidth;
        }

        GraphLine *setPointOfBegin(PointF pointOfBegin) {
            x = pointOfBegin.x;
            y = pointOfBegin.y;
            return this;
        }
        GraphLine *setPointOfEnd(PointF pointOfEnd) {
            width = pointOfEnd.x - x;
            height = pointOfEnd.y - y;
            return this;
        }
        GraphLine *setColor(Color color) {
            this->color = color;
            return this;
        }
        GraphLine *setLineWidth(float lineWidth) {
            this->lineWidth = lineWidth;
            return this;
        }

    private:

        Color color;
        float lineWidth;

        virtual void repaintRect(Graphics *graphics) {
            ///graphics->drawRectangle(Rect(0, 0, width, height), color);
            graphics->drawLineSP(PointF(lineWidth, lineWidth), PointF(width - lineWidth, height - lineWidth), color, lineWidth);
        };


    public:
        ~GraphLine() {};
    };

}