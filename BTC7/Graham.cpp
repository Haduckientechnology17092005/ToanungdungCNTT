#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <set>

using namespace std;

struct Point {
    int x, y;
    bool operator<(const Point& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};
double dist(Point p1, Point p2){
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}
pair<Point, Point> find_min_edge(vector<Point> v){
    double min_dist = numeric_limits<double>::max();
    int n = v.size();
    pair<Point, Point> res;
    for (int i = 0; i < n; i++){
        int j = (i + 1) % n;
        double distance = dist(v[i], v[j]);
        if(distance < min_dist){
            min_dist = distance;
            res = {v[i], v[j]};
        }
    }
    return res;
}
pair<Point, Point> find_closet_points(vector<Point> v, int n){
    double min_dist = numeric_limits<double>::max();
    pair<Point, Point> closet_pair;
    for (int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            double distance = dist(v[i], v[j]);
            if(distance < min_dist){
                min_dist = distance;
                closet_pair = {v[i], v[j]};
            }
        }
    }
    return closet_pair;
}
vector<Point> generateRandomPoints(int numberOfPoints, int maxRange) {
    vector<Point> points;
    srand(time(nullptr));
    set<int> existingYValues;
    while (points.size() < numberOfPoints) {
        int x = rand() % maxRange;
        int y;
        do {
            y = rand() % maxRange; 
        } while (existingYValues.find(y) != existingYValues.end()); 
        existingYValues.insert(y);
        points.push_back(Point{x, y});
    }
    return points;
}

double angleToPoint(const Point& pt1, const Point& pt2) {
    return atan2(pt1.y - pt2.y, pt2.x - pt1.x);
}

double getAngleBetween3Points(const Point& pt1, const Point& pt2, const Point& pt3) {
    double ab = sqrt(pow(pt2.x - pt1.x, 2) + pow(pt2.y - pt1.y, 2));
    double bc = sqrt(pow(pt2.x - pt3.x, 2) + pow(pt2.y - pt3.y, 2));
    double ac = sqrt(pow(pt3.x - pt1.x, 2) + pow(pt3.y - pt1.y, 2));
    return acos((bc * bc + ab * ab - ac * ac) / (2 * bc * ab));
}

double getAreaBetween3Points(const Point& pt1, const Point& pt2, const Point& pt3) {
    return (pt2.x - pt1.x) * (pt1.y - pt3.y) - (pt3.x - pt1.x) * (pt1.y - pt2.y);
}

bool checkIfLeftTurn(const Point& pt1, const Point& pt2, const Point& pt3) {
    return getAreaBetween3Points(pt1, pt2, pt3) > 0;
}

bool isSamePoint(const Point& p1, const Point& p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

vector<Point> grahamScan(vector<Point>& points) {
    Point v_lowest = points[0];
    
    for (size_t i = 1; i < points.size(); i++) {
        if (points[i].y > v_lowest.y || (points[i].y == v_lowest.y && points[i].x < v_lowest.x)) {
            v_lowest = points[i];
        }
    }
    
    sort(points.begin(), points.end(), [&v_lowest](const Point& a, const Point& b) {
        double ang_a = angleToPoint(v_lowest, a);
        double ang_b = angleToPoint(v_lowest, b);
        return ang_a < ang_b;
    });

    vector<Point> stack;
    if (points.size() < 4) return points;

    stack.push_back(points[0]);
    stack.push_back(points[1]);

    size_t index = 2;
    while (index < points.size()) {
        size_t stacklen = stack.size();
        if (stacklen > 1 && checkIfLeftTurn(stack[stacklen - 2], stack[stacklen - 1], points[index])) {
            stack.push_back(points[index]);
            index++;
        } else {
            stack.pop_back();
        }
    }
    
    return stack;
}

double calculateHullArea(const vector<Point>& hull) {
    double area = 0.0;
    int n = hull.size();
    
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += hull[i].x * hull[j].y - hull[i].y * hull[j].x;
    }
    
    return abs(area) / 2.0;
}
bool isPointInHull(const vector<Point>& hull, const Point& p) {
    int n = hull.size();
    for (int i = 0; i < n; i++) {
        const Point& pt1 = hull[i];
        const Point& pt2 = hull[(i + 1) % n];
        if (checkIfLeftTurn(pt1, pt2, p)) {
            return false;
        }
    }
    return true;
}
bool is_In_Vector(const vector<Point>& v, const Point& p) {
    int n = v.size();
    for (int i = 0; i < n; i++) {
        if (v[i] == p) {
            return true;
        }
    }
    return false;
}
vector<Point> elements_In_A_And_Not_In_B(const vector<Point>& A, const vector<Point>& B) {
    vector<Point> result;
    for (const auto& point : A) {
        if(!is_In_Vector(B,point)){
            result.push_back(point);
        }
    }
    return result;
}
int main() {
    int n = 15;
    int maxRange = 20;
    vector<Point> points = {{6,2}, {8,3}, {4,10}, {3,5}, {16,5}, {9,7}, {11,6}, {10, 12}, {8,9}, {7,6}};
    cout<<"Random points:\n";
    for (const auto& point : points) {
        cout << "(" << point.x << ", " << point.y << ") ";
    }
    cout<<"\n";
    auto hull = grahamScan(points);
    cout << "Convex Hull points:\n";
    for (const auto& point : hull) {
        cout << "(" << point.x << ", " << point.y << ")" << endl;
    }
    double hullArea = calculateHullArea(hull);
    cout << "Convex Hull Area: " << hullArea << endl;
    pair<Point, Point> minEdge = find_min_edge(hull);
    cout << "Shortest edge in Convex Hull: (" << minEdge.first.x << ", " << minEdge.first.y << ") and (" 
         << minEdge.second.x << ", " << minEdge.second.y << ")\n";
    cout << "Length of shortest edge: " << dist(minEdge.first, minEdge.second) << endl;
    pair<Point, Point> closestPoints = find_closet_points(points, points.size() - 1);
    cout << "Closest points: (" << closestPoints.first.x << ", " << closestPoints.first.y << ") and (" 
         << closestPoints.second.x << ", " << closestPoints.second.y << ")\n";
    cout << "Distance between closest points: " << dist(closestPoints.first, closestPoints.second) << endl;
    vector<Point> points_inside = elements_In_A_And_Not_In_B(points, hull);
    cout << "Points inside the Convex Hull:\n";
    for (const auto& point : points_inside) {
        cout << "(" << point.x << ", " << point.y << ")" << endl;
    }
    int m = 1;
    vector<Point> testPoints = generateRandomPoints(m, maxRange);
    cout << "Random points:\n";
    for (const auto& point : testPoints) {
        cout << "(" << point.x << ", " << point.y << ")" << endl;
    }
    if (isPointInHull(hull, testPoints[0])) {
        cout << "Point " << testPoints[0].x << ", " << testPoints[0].y << " is in the convex hull." << endl;
    } else {
        cout << "Point " << testPoints[0].x << ", " << testPoints[0].y << " is not in the convex hull." << endl;
    }
    return 0;
}
