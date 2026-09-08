#include "minicad/circle.hpp"
#include "minicad/point.hpp"
#include "minicad/numeric.hpp"
#include <stdexcept>
#include <cmath>
#include <numbers>
#include <vector>

namespace minicad {
    //constructor
    Circle::Circle(const Point2D& center, double radius)
    : center_(center),
        radius_(radius)
    {
        if(radius < 0.0) {
            throw std::invalid_argument("Radius cannot be negative");
        }
    }

    double Circle::area() const {
        return std::numbers::pi * radius_ * radius_;
    }
    
    double Circle::circumference() const {
        return 2.0 * std::numbers::pi * radius_;
    }
    //checks where a point is in relation to a circle
    PointCircleRelation Circle::relationTo(const Point2D& point) const {
        double dist = distance(point, center_);

        if(approximatelyEqual(dist, radius_, epsilon)) {
            return PointCircleRelation::OnBoundry;
        }

        if(dist < radius_) {
            return PointCircleRelation::Inside;
        }

        return PointCircleRelation::Outside;
    }
    //checks where a circle is in relation to a circle
    CircleCircleRelation Circle::relationTo(const Circle& other) const {
        double centerDistance = distance(center_, other.center_);
        double radiusSum = radius_ + other.radius_;
        double radiusDiff = abs(radius_ - other.radius_);

        if(approximatelyEqual(centerDistance, 0.0, epsilon) && approximatelyEqual(radius_, other.radius_, epsilon)) { //identical circles
            return CircleCircleRelation::Identical;
        }

        if(approximatelyEqual(centerDistance, radiusSum, epsilon)) { //extermally tangent circles
            return CircleCircleRelation::ExternallyTangent;
        }

        if(centerDistance > radiusDiff && centerDistance < radiusSum) { //2 intersection points
            return CircleCircleRelation::Intersecting;
        }

        if(approximatelyEqual(centerDistance, radiusDiff, epsilon)) { //internally tangent circles
            return CircleCircleRelation::InternallyTanget;
        }

        if(centerDistance < radiusDiff) { //one circle is inside another
            return CircleCircleRelation::Contained;
        }

        

        return CircleCircleRelation::Seperate;
    }
    //calculates intersection points between a line and a circle
    std::vector<Point2D> Circle::intersects(const Line& line, const Circle& circle) {
        std::vector<Point2D> points;

        Vector2D pc = vectorBetween(line.point(), circle.center_);
        const Point2D& p = line.point();
        const Vector2D& d = line.direction();
        const Point2D& c = circle.center_;

        Vector2D unitDirection = normalize(d);

        double t = dot(pc, d) / dot(d , d);

        Point2D cloestPoint = p + t * d;

        double height = distance(cloestPoint, c);

        if(approximatelyEqual(height, circle.radius_, epsilon)) { //tangent 
            points.push_back(cloestPoint);
            return points;
        }

        if(height < circle.radius_) { //2 intersection points
            double offset = std::sqrt
            (circle.radius_ * circle.radius_ - height * height);

            Vector2D offsetVector = offset * unitDirection  ;
            
            Point2D p1 = cloestPoint + offsetVector;
            Point2D p2 = cloestPoint - offsetVector;
            
            points.push_back(p1);
            points.push_back(p2);

            return points;
        }
            
        return points; 
    }
    //calculates intersection points between 2 circles
    std::vector<Point2D> Circle::circleIntersection(const Circle& c1, const Circle& c2) {
        std::vector<Point2D> points;
        CircleCircleRelation relation = c1.relationTo(c2);

        Vector2D v = vectorBetween(c1.center_, c2.center_);
        v = normalize(v);

        double r1 = c1.radius_;
        double r2 = c2.radius_;
        double d = distance(c1.center_, c2.center_);


        if(relation == CircleCircleRelation::Identical) {
            return points;
        }

        if(relation == CircleCircleRelation::ExternallyTangent) {
            Point2D p1 {c1.center_.x + r1 * v.x, c1.center_.y + r1 * v.y};
            points.push_back(p1);
            return points;
        }

        if(relation == CircleCircleRelation::InternallyTanget) {
            if(r1 > r2) { //c2 is inside c1
                Point2D p1 {c1.center_.x + r1 * v.x, c1.center_.y + r1 * v.y};
                points.push_back(p1);
                return points;
            }

            //c1 is inside c2
             Point2D p1 {c2.center_.x - r2 * v.x, c2.center_.y - r2 * v.y};
             points.push_back(p1);
             return points;
        }

        if(relation == CircleCircleRelation::Intersecting) {
            double x = (r1 * r1 - r2 * r2 + d * d) / (2 * d);
            Point2D m {c1.center_.x + x * v.x, c1.center_.y + x * v.y};
            double h = std::sqrt(r1 * r1 - x * x);

            Vector2D perp {-v.y , v.x};
            Point2D p1 = m + h * perp;
            Point2D p2 = m - h * perp;

            points.push_back(p1);
            points.push_back(p2);

            return points;

        }

        //contains or seperate no intersection
        return points;
    }

}
        


    