#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;

    bool operator <(const Point &p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
};
int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0; 
    return (val > 0) ? 1 : 2; 
}

vector<Point> convexHull(Point points[], int n) {
    if (n < 3) return {};
    vector<Point> hull;
    int l = 0;
    for (int i = 1; i < n; i++)
        if (points[i].x < points[l].x)
            l = i;
    int p = l, q;
    do {
        hull.push_back(points[p]);
        q = (p + 1) % n;
        for (int i = 0; i < n; i++) {
            if (orientation(points[p], points[i], points[q]) == 2)
                q = i;
        }
        p = q;

    } while (p != l); 
    return hull;
}

double distance(const Point &A, const Point &B) {
    return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

pair<Point, Point> find_min_edge(const vector<Point> &P) {
    double min_dist = DBL_MAX;
    pair<Point, Point> res;
    int n = P.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        double d = distance(P[i], P[j]);
        if (d < min_dist) {
            min_dist = d;
            res = {P[i], P[j]};
        }
    }
    return res;
}
pair<Point, Point> find_closest_points(Point points[], int n) {
    double min_dist = DBL_MAX;
    pair<Point, Point> closest_pair;
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double d = distance(points[i], points[j]);
            if (d < min_dist) {
                min_dist = d;
                closest_pair = {points[i], points[j]};
            }
        }
    }
    
    return closest_pair;
}
double poly_area(const vector<Point> &P) {
    int n = P.size();
    double area = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += P[i].x * P[j].y - P[i].y * P[j].x;
    }
    return abs(area) / 2.0;
}

bool is_inside_hull(const Point &pt, const vector<Point> &hull) {
    int n = hull.size();
    if (n < 3) return false;

    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        if (orientation(hull[i], hull[j], pt) != 2) 
            return false;
    }
    return true;
}
void generate_random_points(Point points[], int n, int max_x, int max_y) {
    srand(time(0)); // Seed cho random
    for (int i = 0; i < n; i++) {
        points[i].x = rand() % max_x;
        points[i].y = rand() % max_y;
    }
}
int main() {
    int n = 10; 
    Point points[n];
    int max_x = 10, max_y = 10; 
    generate_random_points(points, n, max_x, max_y);
    cout << "Generated Random Points:\n";
    for (int i = 0; i < n; i++) {
        cout << "(" << points[i].x << ", " << points[i].y << ")\n";
    }
    vector<Point> hull = convexHull(points, n);
    cout << "\nConvex Hull:\n";
    for (const auto &p : hull)
        cout << "(" << p.x << ", " << p.y << ")\n";
    double area = poly_area(hull);
    cout << "\nArea of Convex Hull: " << area << endl;
    pair<Point, Point> min_edge = find_min_edge(hull);
    cout << "\nShortest edge in Convex Hull: (" << min_edge.first.x << ", " << min_edge.first.y << ") and ("
         << min_edge.second.x << ", " << min_edge.second.y << ")\n";
    cout << "Length of shortest edge: " << distance(min_edge.first, min_edge.second) << endl;
    pair<Point, Point> closest_pair = find_closest_points(points, n);
    cout << "\nClosest points in the set: (" << closest_pair.first.x << ", " << closest_pair.first.y << ") and ("
    << closest_pair.second.x << ", " << closest_pair.second.y << ")\n";
    cout << "Distance between closest points: " << distance(closest_pair.first, closest_pair.second) << endl;
    Point test_point = {1, 2}; 
    if (is_inside_hull(test_point, hull)) {
        cout << "\nPoint (" << test_point.x << ", " << test_point.y << ") is inside the convex hull.\n";
    } else {
        cout << "\nPoint (" << test_point.x << ", " << test_point.y << ") is outside the convex hull.\n";
    }
    return 0;
}
