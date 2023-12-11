#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <Graphics/Renderer.h>

struct CubicBezierPoint
{
	glm::vec3 point;
	glm::vec3 controlPoint;

	CubicBezierPoint(const glm::vec3& point, const glm::vec3& controlPoint)
	{
		this->point = point;
		this->controlPoint = controlPoint;
	}

};

struct PointOnCurve
{
	glm::vec3 point;
	glm::vec3 tangent;

	PointOnCurve(const glm::vec3& point, const glm::vec3& tangent)
	{
		this->point = point;
		this->tangent = tangent;
	}
};

class CubicBezierCurve
{
public:
	
	float spacing = 0;

	CubicBezierCurve(float spacing = 0.01f);

	void CalculateCurve();
	void DrawCurve();

	int GetCurveCount();

	void AddPoint(CubicBezierPoint point);

	PointOnCurve GetCachedPointOnCurve(int index);

private:

	Renderer* renderer;

	bool visualize = true;

	std::vector<CubicBezierPoint> listOfPoints;
	std::vector<PointOnCurve> listOfPointsOnCurve;

	PointOnCurve GetPointOnCurve(float t) const;

};

