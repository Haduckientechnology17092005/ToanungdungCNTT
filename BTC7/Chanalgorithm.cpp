#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm> 
#include <utility>   
#include <set>
#include <cmath>
#include <limits>
#include <ctime> 
#define RIGHT_TURN -1  
#define LEFT_TURN 1  
#define COLLINEAR 0  
using namespace std;

class Point{
    public:
    int x;
    int y;
    Point (int newx=0,int newy=0){
        x=newx;
        y=newy;
    }
    friend bool operator== (const Point& p1,const Point& p2){
        return (p1.x==p2.x && p1.y==p2.y);
    }
    friend bool operator!= (const Point& p1,const Point& p2){
        return (!(p1.x==p2.x && p1.y==p2.y));
    }
    friend ostream& operator<<(ostream& output,const Point& p){
        output<<"("<<p.x<<","<<p.y<<")";
        return output;
    }
} p0;

int orientation(Point p, Point q, Point r){
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;
    return (val > 0)? -1: 1;
}
double dist(Point p1, Point p2){
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
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
int compare(const void *vp1, const void *vp2){
    Point *p1 = (Point *)vp1;
    Point *p2 = (Point *)vp2;
    int orient = orientation(p0, *p1, *p2);
    if (orient == 0)
        return (dist(p0, *p2) >= dist(p0, *p1))? -1 : 1;
    return (orient == 1)? -1: 1;
}
int tangent(vector<Point> v,Point p){
    int l=0;
    int r= v.size();
    int l_before = orientation(p, v[0], v[v.size()-1]);
    int l_after = orientation(p, v[0], v[(l + 1) % v.size()]);
    while (l < r){
        int c = ((l + r)>>1);
        int c_before = orientation(p, v[c], v[(c - 1) % v.size()]);
        int c_after = orientation(p, v[c], v[(c + 1) % v.size()]);
        int c_side = orientation(p, v[l], v[c]);
        if ((c_before != RIGHT_TURN) && (c_after != RIGHT_TURN))
        return c;
        else if ((c_side == LEFT_TURN) && (l_after == RIGHT_TURN || l_before == l_after) || (c_side == RIGHT_TURN && c_before == RIGHT_TURN))
        r = c;
        else
        l = c + 1 ;
        l_before = -c_after; 
        l_after = orientation(p, v[l], v[(l + 1) % v.size()]);
    }
    return l;
}
pair<int,int> extreme_hullpt_pair(vector<vector<Point> >& hulls){
    int h= 0,p= 0;
    for (int i=0; i<hulls.size(); ++i){
        int min_index=0, min_y = hulls[i][0].y;
        for(int j=1; j< hulls[i].size(); ++j){
        if(hulls[i][j].y < min_y){
            min_y=hulls[i][j].y;
            min_index=j;
        }
        }
        if(hulls[i][min_index].y < hulls[h][p].y){
        h=i;
        p=min_index;
        }   
    }
    return make_pair(h,p);
}
pair<int,int> next_hullpt_pair(vector<vector<Point> >& hulls, pair<int,int> lPoint){
    Point p = hulls[lPoint.first][lPoint.second];
    pair<int,int> next = make_pair(lPoint.first, (lPoint.second + 1) % hulls[lPoint.first].size());
    for (int h=0; h< hulls.size(); h++){
        if(h != lPoint.first){
        int s= tangent(hulls[h],p);
        Point q= hulls[next.first][next.second];
        Point r= hulls[h][s];
        int t= orientation(p,q,r);
        if( t== RIGHT_TURN || (t==COLLINEAR) && dist(p,r)>dist(p,q))
            next = make_pair(h,s);
        }
    }
    return next;
}    
vector<Point> keep_left (vector<Point>& v,Point p){
    while(v.size()>1 && orientation(v[v.size()-2],v[v.size()-1],p) != LEFT_TURN)
        v.pop_back();
    if(!v.size() || v[v.size()-1] != p)
        v.push_back(p);
    return v;
}
vector<Point> GrahamScan(vector<Point>& Points) {
    if (Points.size() <= 1) 
        return Points;
    qsort(&Points[0], Points.size(), sizeof(Point), compare);
    vector<Point> lower_hull;
    for (const auto& p : Points)
        lower_hull = keep_left(lower_hull, p);
    reverse(Points.begin(), Points.end());
    vector<Point> upper_hull;
    for (const auto& p : Points)
        upper_hull = keep_left(upper_hull, p);
    lower_hull.insert(lower_hull.end(), upper_hull.begin() + 1, upper_hull.end());
    return lower_hull;
}
vector<Point> chansalgorithm(vector<Point> v) {
    for(int t = 0; t < v.size(); ++t) {
        for(int m = 1; m < (1 << (1 << t)); ++m) {
            vector<vector<Point>> hulls;
            for(int i = 0; i < v.size(); i += m) {
                vector<Point> chunk;
                if(v.begin() + i + m <= v.end())
                    chunk.assign(v.begin() + i, v.begin() + i + m);
                else
                    chunk.assign(v.begin() + i, v.end());
                hulls.push_back(GrahamScan(chunk)); 
            }
            vector<pair<int, int>> hull;
            hull.push_back(extreme_hullpt_pair(hulls)); 
            for(int i = 0; i < m; ++i) {
                pair<int, int> p = next_hullpt_pair(hulls, hull[hull.size() - 1]); 
                vector<Point> output;
                if(p == hull[0]) {
                    for(int j = 0; j < hull.size(); ++j) {
                        output.push_back(hulls[hull[j].first][hull[j].second]);
                    }
                    // output.pop_back();
                    return output; 
                }
                hull.push_back(p);
            }
        }
    }
    return {};
}
vector<Point> generateRandomPoints(int numberOfPoints, int maxRange) {
    vector<Point> Points;
    srand(time(nullptr));
    set<int> existingYValues;
    while (Points.size() < numberOfPoints) {
        int x = rand() % maxRange;
        int y;
        do {
            y = rand() % maxRange; 
        } while (existingYValues.find(y) != existingYValues.end()); 
        existingYValues.insert(y);
        Points.push_back(Point{x, y});
    }
    return Points;
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
bool is_Point_in_convex_hull(const vector<Point>& hull, const Point& p) {
    int n = hull.size();
    if (n < 3) return false;
    for (int i = 0; i < n; ++i) {
        int next = (i + 1) % n; 
        int orient = orientation(hull[i], hull[next], p);
        if (orient == RIGHT_TURN) {
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
int main(){
    srand(time(0));
    int n = 15;
    int max_range = 20;
    vector<Point> v = {{6,2}, {8,3}, {4,10}, {3,5}, {16,5}, {9,7}, {11,6}, {10, 12}, {8,9}, {7,6}};
    cout << "Original Points: \n";
    for (auto p : v) cout << p << "\t";
    cout << endl;
    vector<Point> output = chansalgorithm(v);
    cout << "Convex hull: \n";
    for(auto p : output) cout << p << "\t";
    cout << "\n";
    cout << "Polygon area: " << poly_area(output) << endl;
    pair<Point, Point> min_edge = find_min_edge(output);
    cout << "Shortest edge in Convex Hull: (" << min_edge.first.x << ", " << min_edge.first.y << ") and (" 
         << min_edge.second.x << ", " << min_edge.second.y << ")\n";
    cout << "Length of shortest edge: " << dist(min_edge.first, min_edge.second) << endl;
    pair<Point, Point> closet_points = find_closet_points(v, v.size()-1);
    cout << "Closest points in Convex Hull: (" << closet_points.first.x << ", " << closet_points.first.y << ") and (" 
         << closet_points.second.x << ", " << closet_points.second.y << ")\n";
    cout << "Length of closest edge: " << dist(closet_points.first, closet_points.second) << endl;
    cout << "Points inside Convex Hull: \n";
    vector<Point> points_inside = elements_In_A_And_Not_In_B(v, output);
    for (auto p : points_inside) cout << p << "\t";
    cout << endl;
    int m = 1;
    vector<Point> testPoint = {{7, 8}};
    if (is_Point_in_convex_hull(output, testPoint[0])) {
        cout << "Point " << testPoint[0] << " is in the convex hull." << endl;
    } else {
        cout << "Point " << testPoint[0] << " is not in the convex hull." << endl;
    }
    return 0;
}
