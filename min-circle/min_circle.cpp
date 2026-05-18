#include "min_circle.h"
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <random>

bool Point2D::operator==(const Point2D& other) const
{
    if (x == other.x && y == other.y)
    {
        return true;
    }
    return false;
}
bool Point2D::operator!=(const Point2D& other) const 
{
    return !(*this == other);
}
bool Circle::isValid() const 
{
    return radius >= 0;
}
bool Circle::contains(const Point2D& point) const 
{
    if (distance(center, point) <= radius)
    {
        return true;
    }
    return false;
}
bool Circle::contains(const LineSegment& segment) const {
    if (distance(segment.start, center) <= radius && distance(segment.end, center) <= radius)
    {
        return true;
    }
    return false;
}
bool Circle::containsEntireSegment(const LineSegment& segment) const 
{
    Point2D mid = findMidPoint(segment);
    if (distance(segment.start, center) <= radius && distance(segment.end, center) <= radius && distance(mid, center) <= radius)
    {
        return true;
    }
    return false;
}

Circle MinimumEnclosingCircleForSegments(const std::vector<LineSegment>& segments) {
    if (segments.empty())
    {
        return { {0, 0}, -1.0 };
    }

    std::vector<Point2D> points = extractPointsFromSegments(segments);

    Circle res = minCircle(points);

    for (const auto& seg : segments) {
        if (!res.containsEntireSegment(seg)) 
        {
            Point2D farthestPoint;
            double maxDist = 0;
            Point2D mid = findMidPoint(seg);
            if (distance(res.center, seg.start) > maxDist) 
            {
                maxDist = distance(res.center, seg.start);
                farthestPoint = seg.start;
            }
            if (distance(res.center, seg.end) > maxDist)
            {
                maxDist = distance(res.center, seg.end);
                farthestPoint = seg.end;
            }
            if (distance(res.center, mid) > maxDist) 
            {
                maxDist = distance(res.center, mid);
                farthestPoint = mid;
            }

            res = circleFromDiameter(res.center, farthestPoint);
        }
    }

    return res;
}
double distanceSquared(const Point2D& p1, const Point2D& p2)
{
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return dx * dx + dy * dy;
}
double distance(const Point2D& p1, const Point2D& p2)
{
    return std::sqrt(distanceSquared(p1, p2));
}
Circle circleFromDiameter(const Point2D& p1, const Point2D& p2)
{
    LineSegment segment;
    segment.start = p1;
    segment.end = p2;
    Point2D mid = findMidPoint(segment);
    Circle res;
    res.center = mid;
    res.radius = distance(mid, p1);
    return res;
}
Circle circleFrom3Points(const Point2D& p1, const Point2D& p2, const Point2D& p3)
{
    Circle res;
    double d = 2 * (p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y));
    if (std::abs(d) < 1e-9) 
    {
        double d12 = distanceSquared(p1, p2);
        double d23 = distanceSquared(p2, p3);
        double d31 = distanceSquared(p3, p1);

        if (d12 >= d23 && d12 >= d31)
            return circleFromDiameter(p1, p2);
        else if (d23 >= d12 && d23 >= d31)
            return circleFromDiameter(p2, p3);
        else
            return circleFromDiameter(p3, p1);
    }

    double centerx = ((p1.x * p1.x + p1.y * p1.y) * (p2.y - p3.y) +
        (p2.x * p2.x + p2.y * p2.y) * (p3.y - p1.y) +
        (p3.x * p3.x + p3.y * p3.y) * (p1.y - p2.y)) / d;

    double centery = ((p1.x * p1.x + p1.y * p1.y) * (p3.x - p2.x) +
        (p2.x * p2.x + p2.y * p2.y) * (p1.x - p3.x) +
        (p3.x * p3.x + p3.y * p3.y) * (p2.x - p1.x)) / d;

    res.center = {centerx, centery};
    res.radius = distance(res.center, p1);
    return res;
}

Circle minCircleHelper(std::vector<Point2D>& points, std::vector<Point2D> boundary, size_t n)
{
    if (n == 0 || boundary.size() == 3)
    {
        if (boundary.empty())
        {
            return { {0,0}, -1.0 };
        }
        else if (boundary.size() == 1)
        {
            return { boundary[0], 0.0 };
        }
        else if (boundary.size() == 2)
        {
            return circleFromDiameter(boundary[0], boundary[1]);
        }
        else
        {
            return circleFrom3Points(boundary[0], boundary[1], boundary[2]);
        }
    }

    size_t idx = rand() % n;
    Point2D p = points[idx];

    std::swap(points[idx], points[n - 1]);

    Circle res = minCircleHelper(points, boundary, n - 1);

    if (res.isValid() && res.contains(p))
        return res;

    boundary.push_back(p);
    return minCircleHelper(points, boundary, n - 1);

}

Circle minCircle(std::vector<Point2D> points)
{
    if (points.empty())
    {
        return { {0, 0}, -1.0 };
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(points.begin(), points.end(), g);

    return minCircleHelper(points, {}, points.size());
}
std::vector<Point2D> extractPointsFromSegments(const std::vector<LineSegment>& segments)
{
    std::vector<Point2D> res;
    res.reserve(segments.size() * 3);  

    for (const auto& seg : segments)
    {
        res.push_back(seg.start);
        res.push_back(findMidPoint(seg));
        res.push_back(seg.end);
    }

    return res;
}
Point2D findMidPoint(const LineSegment& segment)
{
    Point2D mid;
    mid.x = (segment.start.x + segment.end.x) / 2;
    mid.y = (segment.start.y + segment.end.y) / 2;
    return mid;
}
