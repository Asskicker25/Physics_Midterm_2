#include <iostream>

#include "CubicBezierCurve.h"
#include "../RendererInstance.h"

CubicBezierCurve::CubicBezierCurve(float spacing)
{
    this->renderer = renderer;
    this->spacing = spacing;

    renderer = RendererInstance::GetInstance().GetRenderer();
}

void CubicBezierCurve::CalculateCurve()
{
    listOfPointsOnCurve.clear();

    int count = 1 / spacing;

    for (int i = 0; i <= count; i++)
    {
        listOfPointsOnCurve.push_back(GetPointOnCurve(i * spacing));
    }
}

void CubicBezierCurve::DrawCurve()
{
    if (!visualize) return;

    for(PointOnCurve point : listOfPointsOnCurve)
    { 
        renderer->DrawCube(point.point, glm::vec3(0), glm::vec3(0.1f), glm::vec4(1, 0, 0, 1), false);
    }
}

int CubicBezierCurve::GetCurveCount()
{
    return listOfPointsOnCurve.size();
}

void CubicBezierCurve::AddPoint(CubicBezierPoint point)
{
	listOfPoints.push_back(point);
}

PointOnCurve CubicBezierCurve::GetCachedPointOnCurve(int index)
{
    return listOfPointsOnCurve[index];
}

PointOnCurve CubicBezierCurve::GetPointOnCurve(float t) const {
    int numPoints = static_cast<int>(listOfPoints.size());

    if (numPoints < 2) {
        std::cout << "Insufficient points to create a Bezier curve." << std::endl;
        return PointOnCurve(glm::vec3(0.0f), glm::vec3(0.0f));
    }

    std::vector<glm::vec3> points;
    std::vector<glm::vec3> controlPoints;

    for (const CubicBezierPoint& bezierPoint : listOfPoints) {
        points.push_back(bezierPoint.point);
        controlPoints.push_back(bezierPoint.controlPoint);
    }

    glm::vec3 tangent = glm::vec3(0.0f);

    while (points.size() > 1) {
        std::vector<glm::vec3> nextPoints;
        std::vector<glm::vec3> nextControlPoints;

        for (size_t i = 0; i < points.size() - 1; ++i) {
            glm::vec3 p0 = points[i];
            glm::vec3 p1 = points[i + 1];
            glm::vec3 controlPoint = controlPoints[i];
            glm::vec3 q0 = p0 + t * (controlPoint - p0);
            glm::vec3 q1 = controlPoint + t * (p1 - controlPoint);
            glm::vec3 q2 = q0 + t * (q1 - q0);

            nextPoints.push_back(q2);
            nextControlPoints.push_back(controlPoint);
        }

        // Calculate the tangent at the last point
        tangent = (nextPoints.back() - points.back());

        points = nextPoints;
        controlPoints = nextControlPoints;
    }

    // Normalize the tangent to get the right vector
    glm::vec3 rightVector = (glm::length(tangent) > 0.0f) ? glm::normalize(tangent) :
        listOfPointsOnCurve[listOfPointsOnCurve.size() - 1].tangent;

    return PointOnCurve(points.back(), rightVector);
}
