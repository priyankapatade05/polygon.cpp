#include <iostream> 
using namespace std; 
#define INF 100 

struct Point 
{ 
	double x=0 ,y=0;
}; 

bool onSegment(Point p, Point q, Point r) 
{ 
	if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && 
			q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y)) 
		return true; 
	return false; 
} 

int orientation(Point p, Point q, Point r) 
{ 
	int value = (q.y - p.y) * (r.x - q.x) - 
			(q.x - p.x) * (r.y - q.y); 

	if (value == 0) return 0; 
	return (value > 0)? 1: 2;  
} 

bool doIntersect(Point p, Point q, Point r, Point s) 
{ 
	int o1 = orientation(p,q,r); 
	int o2 = orientation(p,q,s); 
	int o3 = orientation(r,s,p); 
	int o4 = orientation(r,s,q); 

	if (o1 != o2 && o3 != o4) 
		return true; 

	if (o1 == 0 && onSegment(p,r,q)) return true; 

	if (o2 == 0 && onSegment(p,s,q)) return true; 

	if (o3 == 0 && onSegment(r,p,s)) return true; 

	if (o4 == 0 && onSegment(r,q,s)) return true; 

	return false;  
} 

bool isInside(Point polygon[], int n, Point p) 
{ 
	if (n < 3) return false; 

	Point extreme = {INF, p.y}; 

	int count = 0, i = 0; 
	do
	{ 
		int next = (i+1)%n; 

		if (doIntersect(polygon[i], polygon[next], p, extreme)) 
		{ 
			if (orientation(polygon[i], p, polygon[next]) == 0) 
			return onSegment(polygon[i], p, polygon[next]); 

			count++; 
		} 
		i = next; 
	} while (i != 0); 
    
	return count&1; 
} 


int main() 
{ 
    Point polygon[] = {{1,0}, {8,-3}, {8,8}, {-1,-5}}; 
	int n = sizeof(polygon)/sizeof(polygon[0]); 

    Point p = {8,5}; 
	isInside(polygon, n, p)? cout << "TRUE\n": cout << "FALSE\n"; 


	Point polygon1[] = {{-3,2}, {2,-0.8}, {0,1.2}, {2.2,0},{2,4.5}}; 
	int n1 = sizeof(polygon1)/sizeof(polygon1[0]); 

    Point p1 = {8,5}; 
	isInside(polygon1, n1, p1)? cout << "TRUE\n": cout << "FALSE\n"; 

	return 0; 
}
