#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <cmath>
#include <limits>
#include <ctime> 
#define Max 1000000000
using namespace std;

struct Point {
	double x, y;
	bool operator <(const Point &p) const
	{
		return x < p.x || (x == p.x && y < p.y);
	}
};
double cross(const Point &O, const Point &A, const Point &B) 
{
	return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}
double distance(const Point &A, const Point &B)
{
	return sqrt((A.x - B.x) * (A.x - B.x) + (A.y- B.y) * (A.y- B.y));
}
pair<Point, Point> find_min_dist_recursive(vector<Point> &Px, vector<Point> &Py) {
    int n = Px.size();
    if (n <= 3) {
        double min_dist = Max;
        pair<Point, Point> res;
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                double d = distance(Px[i], Px[j]);
                if (d < min_dist) {
                    min_dist = d;
                    res = {Px[i], Px[j]};
                }
            }
        }
        return res;
    }
    
    int mid = n / 2;
    Point mid_point = Px[mid];    
    vector<Point> Pxl(Px.begin(), Px.begin() + mid);
    vector<Point> Pxr(Px.begin() + mid, Px.end());
    vector<Point> Pyl, Pyr;
    for (auto &p : Py) {
        if (p.x <= mid_point.x) Pyl.push_back(p);
        else Pyr.push_back(p);
    }
    auto d_left = find_min_dist_recursive(Pxl, Pyl);
    auto d_right = find_min_dist_recursive(Pxr, Pyr);
    double min_dist = min(distance(d_left.first, d_left.second), distance(d_right.first, d_right.second));
    pair<Point, Point> res = (distance(d_left.first, d_left.second) < distance(d_right.first, d_right.second)) ? d_left : d_right;
    vector<Point> strip;
    for (auto &p : Py) {
        if (abs(p.x - mid_point.x) < min_dist) strip.push_back(p);
    }
    int m = strip.size();
    for (int i = 0; i < m; ++i) {
        for (int j = i + 1; j < m && (strip[j].y - strip[i].y) < min_dist; ++j) {
            double d = distance(strip[i], strip[j]);
            if (d < min_dist) {
                min_dist = d;
                res = {strip[i], strip[j]};
            }
        }
    }
    
    return res;
}
pair<Point, Point> find_min_dist(vector<Point> &P) {
    vector<Point> Px = P, Py = P;
    sort(Px.begin(), Px.end(), [](const Point &a, const Point &b) { return a.x < b.x; });
    sort(Py.begin(), Py.end(), [](const Point &a, const Point &b) { return a.y < b.y; });
    
    return find_min_dist_recursive(Px, Py);
}

pair<Point, Point> find_min_edge(const vector<Point> &P)
{
	double min_dist = Max;
	pair<Point, Point> res;
	int n = P.size();
	for (int i = 0; i < n ; i++) 
	{
		int j = (i + 1) % n;
		double d = distance(P[i], P[j]);
		if (d < min_dist)  {
			min_dist = d;
			res = {P[i], P[j]};
		}
	}
	return res;
}

vector<Point> generate_unique_points(int n, int max_range) 
{
	set<pair<double, double>> points_set;
	vector<Point> points;
	
	while (points.size() < n) 
	{
		double x = rand() % max_range;
		double y = rand() % max_range;
		
		if (points_set.find(make_pair(x, y)) == points_set.end()) {
			points_set.insert(make_pair(x, y));
			Point P;
			P.x = x;
			P.y = y;
			points.push_back(P);
		}	
	} 	
	return points;
} 
vector<Point> convex_hull(vector<Point> P) 
{
	int n =  P.size(), k = 0;
	if (n <= 3) return P; 
	vector<Point> res(2*n);
	
	sort(P.begin(), P.end());
	
	for (int i = 0; i < n; ++i) 
	{
		while (k >= 2 && cross(res[k-2], res[k-1], P[i]) <= 0) k--;
		res[k++] = P[i];
	}
	
	for (int i = n-1, t = k+1; i > 0; --i) 
	{
		while (k >= t && cross(res[k-2], res[k-1], P[i-1]) <=0 ) k--;
		res[k++] = P[i-1];	
	}
	res.resize(k-1);
	return res;
}
double poly_area(const vector<Point> &P) 
{
	int n = P.size();
	double area = 0;
	for (int i = 0; i < n; i++) 
	{
		int j = (i + 1) % n;
		area += P[i].x* P[j].y - P[i].y * P[j].x;
	}
	return abs(area) / 2.0;
}
int orientation(pair<int, int> a, pair<int, int> b, pair<int, int> c) {
    int res = (b.second - a.second) * (c.first - b.first) -
              (c.second - b.second) * (b.first - a.first);

    if (res == 0)
        return 0;
    if (res > 0)
        return 1;
    return -1;
}
bool pointInConvexHull(const vector<pair<int, int>>& hull, pair<int, int> point) {
    int n = hull.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        if (orientation(hull[i], hull[j], point) < 0)
            return false; 
    }
    return true;
}

int main() 
{
    srand(time(0));
    int n = 15;
    int max_range = 10;
    vector<Point> P = generate_unique_points(n, max_range);
    cout << "Danh sach cac diem dau vao: \n";
    for (auto &p : P) cout << "(" << p.x << ", " << p.y << ")\t";
    cout << endl;
    
    vector<Point> res = convex_hull(P);
    cout << "Bao Loi la \n";
    for (auto &p : res) cout << "(" << p.x << ", " << p.y << ")\n";
    
    cout << "dien tich cua Bao Loi la: " << poly_area(res) << endl;
    
    pair<Point, Point> res_min_dist = find_min_dist(P);
    cout << "2 diem co khoang cach ngan nhat la ";
    cout << "(" << res_min_dist.first.x << ", " << res_min_dist.first.y << ") va "
         << "(" << res_min_dist.second.x << ", " << res_min_dist.second.y << ")\n";
    cout << "Voi khoang cach la: " << distance(res_min_dist.first, res_min_dist.second) << endl;
    
    cout << endl;
    
    pair<Point, Point> res_min_edge = find_min_edge(res);
    cout << "Canh be nhat cua bao loi la ";
    cout << "(" << res_min_edge.first.x << ", " << res_min_edge.first.y << ") va "
         << "(" << res_min_edge.second.x << ", " << res_min_edge.second.y << ")\n";
    cout << "Khoang cach ngan nhat: " << distance(res_min_edge.first, res_min_edge.second) << endl;
    vector<pair<int, int>> convexHullPoints;
    for (auto &p : res) {
        convexHullPoints.push_back({(int)p.x, (int)p.y});
    }
    pair<int, int> randomPoint = {2, 0}; 
    if (pointInConvexHull(convexHullPoints, randomPoint)) {
        cout << "Point (" << randomPoint.first << ", " << randomPoint.second << ") is inside the convex hull.\n";
    } else {
        cout << "Point (" << randomPoint.first << ", " << randomPoint.second << ") is outside the convex hull.\n";
    }
    
    return 0;
}

