#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <set>
#include "IntersectProject.h"

using namespace std;

pair<double, double>
Line::get_line_line_intersect(Line* line) {
	pair<double, double> intersect;
	intersect.first = (b * line->c - line->b * c) / (a * line->b - line->a * b);
	intersect.second = (line->a * c - a * line->c) / (a * line->b - line->a * b);
	return intersect;
}

pair<pair<double, double>, pair<double, double>>
Line::get_line_circle_intersect(Circle* circle, double distance) {
	pair<pair<double, double>, pair<double, double>> intersect;
	//求垂足坐标
	Line* temp = new Line(b, -a, a * circle->get_y() - b * circle->get_x());
	pair<double, double> foot = get_line_line_intersect(temp);
	//求直线单位向量
	pair<double, double> e;
	e.first = b / sqrt(a * a + b * b);
	e.second = -a / sqrt(a * a + b * b);
	//那一小段的长度
	double base = sqrt(circle->get_r() * circle->get_r() - distance * distance);
	//得出两个交点
	intersect.first.first = foot.first + e.first * base;
	intersect.first.second = foot.second + e.second * base;
	intersect.second.first = foot.first - e.first * base;
	intersect.second.second = foot.second - e.second * base;
	return intersect;
}

pair<pair<double, double>, pair<double, double>>
Circle::get_circle_line_intersect(Line* line, double distance) {
	pair<pair<double, double>, pair<double, double>> intersect;
	//求垂足坐标
	Line* temp = new Line(line->get_b(), -line->get_a(), line->get_a() * y - line->get_b() * x);
	pair<double, double> foot = (line)->get_line_line_intersect(temp);
	//求直线单位向量
	pair<double, double> e;
	e.first = line->get_b() / sqrt(line->get_a() * line->get_a() + line->get_b() * line->get_b());
	e.second = -line->get_a() / sqrt(line->get_a() * line->get_a() + line->get_b() * line->get_b());
	//那一小段的长度
	double base = sqrt(r * r - distance * distance);
	//得出两个交点
	intersect.first.first = foot.first + e.first * base;
	intersect.first.second = foot.second + e.second * base;
	intersect.second.first = foot.first - e.first * base;
	intersect.second.second = foot.second - e.second * base;
	return intersect;
}

pair<pair<double, double>, pair<double, double>>
Circle::get_circle_circle_intersect(Circle* circle) {
	pair<pair<double, double>, pair<double, double>> intersect;
	double x1 = circle->get_x();
	double y1 = circle->get_y();
	double r1 = circle->get_r();
	Line* temp = new Line(2 * x1 - 2 * x, 2 * y1 - 2 * y,
		x * x - x1 * x1 + y * y - y1 * y1 + r1 * r1 - r * r);
	double distance = fabs(temp->get_a() * x1 + temp->get_b() * y1 + temp->get_c())
		/ sqrt(temp->get_a() * temp->get_a() + temp->get_b() * temp->get_b());
	intersect = temp->get_line_circle_intersect(circle, distance);
	return intersect;
}

void Intersect::add_line(int x, int y, int xx, int yy) {
	Line* new_line = new Line(x, y, xx, yy);
	set<Line>::iterator line_iter;
	for (line_iter = lines.begin(); line_iter != lines.end(); ++line_iter) {
		//判断平行
		if (fabs(line_iter->get_a() * new_line->get_b()
			- new_line->get_a() * line_iter->get_b()) < eps) {
			continue;
		}
		pair<double, double> intersect = new_line->get_line_line_intersect((Line*)&*line_iter);
		intersects.insert(Point(intersect.first, intersect.second));
	}
	set<Circle>::iterator circle_iter;
	for (circle_iter = circles.begin(); circle_iter != circles.end(); ++circle_iter) {
		//判断位置关系
		double distance = fabs(new_line->get_a() * circle_iter->get_x()
			+ new_line->get_b() * circle_iter->get_y() + new_line->get_c())
			/ sqrt(new_line->get_a() * new_line->get_a() + new_line->get_b() * new_line->get_b());
		//相离
		if (distance - circle_iter->get_r() > eps) {
			continue;
		}
		pair<pair<double, double>, pair<double, double>> intersect =
			new_line->get_line_circle_intersect((Circle*)&*circle_iter, distance);
		intersects.insert(Point(intersect.first.first, intersect.first.second));
		intersects.insert(Point(intersect.second.first, intersect.second.second));
	}
	lines.insert(*new_line);
}

void Intersect::add_circle(int x, int y, int r) {
	Circle* new_circle = new Circle(x, y, r);
	set<Line>::iterator line_iter;
	for (line_iter = lines.begin(); line_iter != lines.end(); ++line_iter) {
		//判断位置关系
		double distance = fabs(line_iter->get_a() * new_circle->get_x()
			+ line_iter->get_b() * new_circle->get_y() + line_iter->get_c())
			/ sqrt(line_iter->get_a() * line_iter->get_a() + line_iter->get_b() * line_iter->get_b());
		//相离
		if (distance - new_circle->get_r() > eps) {
			continue;
		}
		pair<pair<double, double>, pair<double, double>> intersect =
			new_circle->get_circle_line_intersect((Line*)&*line_iter, distance);
		intersects.insert(Point(intersect.first.first, intersect.first.second));
		intersects.insert(Point(intersect.second.first, intersect.second.second));
	}
	set<Circle>::iterator circle_iter;
	for (circle_iter = circles.begin(); circle_iter != circles.end(); ++circle_iter) {
		//判断位置关系
		double x1 = circle_iter->get_x();
		double y1 = circle_iter->get_y();
		double r1 = circle_iter->get_r();
		double distance = sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
		if (distance - r - r1 > eps || distance < fabs(r - r1)) {
			continue;
		}
		pair<pair<double, double>, pair<double, double>> intersect =
			new_circle->get_circle_circle_intersect((Circle*)&*circle_iter);
		intersects.insert(Point(intersect.first.first, intersect.first.second));
		intersects.insert(Point(intersect.second.first, intersect.second.second));
	}
	circles.insert(*new_circle);
}

int Intersect::get_result() {
	return intersects.size();
}

int main() {
	int n, x, y, xx, yy, r;
	char type;
	Intersect* field = new Intersect();
	cin >> n;
	while (n--) {
		cin >> type;
		if (type == 'L') {
			cin >> x >> y >> xx >> yy;
			field->add_line(x, y, xx, yy);
		}
		if (type == 'C') {
			cin >> x >> y >> r;
			field->add_circle(x, y, r);
		}
	}
	cout << field->get_result() << endl;
	return 0;
}
