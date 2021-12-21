//////////////
//  All credits to Richard Peng
//  C++ geometry routines
//
//
/*************************** GEO *************************/
#define PI M_PI
const double EPS = 1e-9;
bool EQ(double a, double b){return abs(a-b) < EPS;}
double SQ(double d){return d*d;}
double normang(double t){ return fmod(fmod(t, 2*PI) + 2*PI, 2*PI); }//tested
double angdiff(double t1, double t2){ return normang(t1 - t2 + PI) - PI; }//tested

template<class T>
vector<T> makeVec(T a, T b){
  vector<T> ans(2);
  ans[0] = a, ans[1] = b;
  return ans;
}

struct Point{
  double x, y;
  Point(double tx, double ty) : x(tx), y(ty) {}
  Point() {}
  Point add(Point p) {return Point(x+p.x, y+p.y);}
  Point sub(Point p) {return Point(x-p.x, y-p.y);}
  Point mult(double d) {return Point(x*d, y*d);}
  double dot(Point p) {return x*p.x+ y*p.y;}
  double cross(Point p) {return x*p.y - y*p.x;}
  double len() {return hypot(x, y);}
  Point scale(double d) {return mult(d/len());}
  double dist(Point p) {return sub(p).len();
  double ang(){return atan2(y, x);}
  static Point polar(double r, double theta) {
    return Point(r*cos(theta), r*sin(theta));}
  Point rot(double theta) {
    return Point(x*cos(theta)-y*sin(theta),x*sin(theta)+y*cos(theta));
  Point perp() {return Point(-y, x);}
  bool operator==(const Point& p) {return abs(dist(p)) < EPS;}
  double norm() {return dot(*this);}
  string toString(){
    char buf[100];
    sprintf(buf, "(%f, %f)", x, y);
    return buf;
  }
};
Point null(2093841.129801, 42390841.21948021);

struct Line{
  Point a, b, along; //along only used by upperhull
  Line(Point ta, Point tb) : a(ta), b(tb) {}
  string toString(){
    char buf[100];
    sprintf(buf, "{%s -> %s}", a.toString().c_str(), b.toString().c_str());
    return buf;
  }
};

double ccw(Point p1, Point p2, Point p3){ //left is 1, right is -1
  return p2.sub(p1).cross(p3.sub(p1));
}

Point lineline(Line a, Line b){
  double d = a.b.sub(a.a).cross(b.b.sub(b.a));
  if(EQ(d, 0)) return null;
  return a.a.add((a.b.sub(a.a)).mult(b.b.sub(b.a).cross(a.a.sub(b.a))/d));
}

bool online(Line l, Point p){ //tested
  return EQ(ccw(l.a, l.b, p), 0);
}

bool onseg(Line l, Point p){ //tested
  Point delta = l.b.sub(l.a);
  return online(l, p) && delta.dot(l.a)-EPS<= delta.dot(p)
    && delta.dot(p) <= delta.dot(l.b) + EPS;
}

Point segline(Line a, Line b){
  Point inter = lineline(a, b);
  if(inter == null || !onseg(a, inter))
    return null;
  return inter;
}

Point segseg(Line a, Line b){//tested
  Point inter = lineline(a, b);
  if(inter == null || !onseg(a, inter) || !onseg(b, inter))
   return null;
  return inter;
}

Point pointline(Point p, Line l){
  Point v = l.b.sub(l.a).scale(1);
  double dot = p.sub(l.a).dot(v);
  return l.a.add(v.mult(dot));
}

Point pointseg(Point p, Line l){
  Point v = l.b.sub(l.a).scale(1);
  double dot = p.sub(l.a).dot(v);
  dot = max(dot, 0.0);
  dot = min(dot, l.b.dist(l.a));
  return l.a.add(v.mult(dot));
}

double pointsegdist(Point p, Line l){
  return pointseg(p, l).dist(p);
}

double pointlinedist(Point p, Line l){
  return pointline(p, l).dist(p);
}

double polyarea(vector<Point> poly){
  double area = 0;
  rep(i, sz(poly))
  area += poly[i].cross(poly[(i+1)%sz(poly)]);
  return abs(area)/2.0;
}

int pointinpoly(Point p, vector<Point> poly){ //tested
  double ang = 0.0;
  rep(i, sz(poly)){
    Point a = poly[i];
    Point b = poly[(i+1)%sz(poly)];
    if(onseg(Line(a, b), p))
      return 0;
    ang += angdiff(a.sub(p).ang(), b.sub(p).ang());
  }
   return EQ(ang, 0) ? -1 : 1; //-1 outside, 1 inside
}
 
struct Circle{
  Point p;double r;
  Circle(Point tp, double tr) : p(tp), r(tr) {}
  Circle(Point a, Point b, Point c){
    Point p1 = a.add(b).mult(0.5);
    Line l1 = Line(p1, p1.add(a.sub(b).perp()));
    Point p2 = b.add(c).mult(0.5);
    Line l2 = Line(p2, p2.add(b.sub(c).perp()));
    p = lineline(l1, l2);
assert(!(p == null));
    r = p.dist(a);
  }
};

//////////////////////////////////////////
//Richard's convex hull routine
//Attempt at minimum number of points on hull
//In high precision setting this might not fully give it
//It doesn't like points with same x value
//So if unsure, preturb by rotating by rand (adding rand is riskier)
//Duplicates in hull can only be first/last point
//of upper/lower, shared when left/rightmost are unique
//
bool convexHullComp(Point a, Point b){
  return a.x < b.x;
}

vector<Point> convexHull(vector<Point> P){
  v0 = null;
  sort(P.begin(), P.end(), convexHullComp);
  vector<Point> ch;
  foreach(p, P) {
    if(ch.size() >= 1 && EQ(ch[sz(ch) - 1].x, p -> x)) {
      if(p -> y > ch[sz(ch) - 1].y) {
        ch.pop_back();
      } else {
        continue;
      }
    } 
    while(ch.size() >= 2 && ccw(ch[sz(ch)-2], ch[sz(ch)-1], *p) > -EPS)
      ch.pop_back();
    ch.pb(*p);
  } //ch contains upper hull at this point
  vector<Point> lh;
  foreach(p, P) {
    if(lh.size() >= 1 && EQ(lh[sz(lh) - 1].x, p -> x)) {
      if(p -> y < lh[sz(lh) - 1].y) {
        lh.pop_back();
      } else {
        continue;
      }
    } 
    while(lh.size() >= 2 && ccw(lh[sz(lh)-2], lh[sz(lh)-1], *p) < EPS)
      lh.pop_back();
    lh.pb(*p);
  }

  for(int i = lh.size() - 1; i >= 0; --i) { //concat up/low
    ch.pb(lh[i]);
  }
  return ch;
}

Point ORIGIN(0.0, 0.0);
bool upperHullComp(Line a, Line b) {
  double hit = ccw(ORIGIN, a.along, b.along);
  if(!EQ(hit, 0))
    return hit > 0;
  return ccw(a.a, a.b, b.a) > 0;
}

vector<Line> upperHull(vector<Line> L){//tested
  foreach(l, L)
    l->along = l->b.sub(l->a);
  vector<Line> ch;
  foreach(l, L){
    while(sz(ch) >= 1){
      Point inter = lineline(ch.back(), *l);
      if(inter == null){
        ch.pop_back();
      } else if(ch.size() >= 2){
        Line A = ch[sz(ch)-2];
        if(ccw(A.a, A.b, inter) < EPS)
          ch.pop_back();
        else break;
      } else{
        break;
      }
    }
    ch.pb(*l);
  }
  return ch;
}

 //circle
vector<Point> circline(Circle c, Line l){//tested
  Point x = pointline(c.p, l);
  double d = x.dist(c.p);
  if(d > c.r + EPS) return vector<Point>();
  double h = sqrt(max(0.0, SQ(c.r) - SQ(d)));
  Point perp = l.a.sub(l.b);
  return makeVec(x.add(perp.scale(h)), x.add(perp.scale(-h)));
}

vector<Point> circcirc(Circle a, Circle b){//tested
  double d = a.p.dist(b.p);
  if(d > a.r + b.r + EPS) return vector<Point>();
  if(d < abs(a.r - b.r) - EPS) return vector<Point>();
  double x = (SQ(d) - SQ(b.r) + SQ(a.r)) / (2*d);
  double y = sqrt(max(0.0,SQ(a.r) - SQ(x)));
  Point v = b.p.sub(a.p);
  return makeVec(a.p.add(v.scale(x)).add(v.perp().scale(y)),
    a.p.add(v.scale(x)).add(v.perp().scale(-y)));
}

vector<Line> circcirctan(Circle a, Circle b){//tested
  if(a.r < b.r)
    return circcirctan(b, a);
  vector<Line> res;
  double d = a.p.dist(b.p);
  double d1 = a.r*d/(a.r + b.r);
  double t = acos(a.r/d1);
  Point v = b.p.sub(a.p);//crossing
  res.pb(Line(a.p.add(v.scale(a.r).rot(t)), b.p.add(v.scale(-b.r).rot(t))));
  res.pb(Line(a.p.add(v.scale(a.r).rot(-t)), b.p.add(v.scale(-b.r).rot(-t))));
  t = asin((a.r-b.r)/d)+PI/2;
  v = a.p.sub(b.p);//same side
  res.pb(Line(a.p.add(v.scale(a.r).rot(t)), b.p.add(v.scale(b.r).rot(t))));
  res.pb(Line(a.p.add(v.scale(a.r).rot(-t)), b.p.add(v.scale(b.r).rot(-t))));
  return res;
}

struct Point3{
  double x, y, z;
  Point3(double tx, double ty, double tz): x(tx), y(ty), z(tz) {}
  static Point3 sphere(double theta, double phi, double r){
    return Point3(r*cos(theta)*sin(phi),r*sin(theta)*sin(phi),r*cos(theta));
  }
  vector<double> ang(){ return makeVec(atan(y/x), acos(z/len())); }
  Point proj(){ return Point(x, y); }
  Point3 add(Point3 p){ return Point3(x+p.x, y+p.y, z+p.z); }
  Point3 sub(Point3 p){ return Point3(x-p.x, y-p.y, z-p.z); }
  double dot(Point3 p){ return x*p.x+ y*p.y+ z*p.z; }
  Point3 cross(Point3 p){ return Point3(y*p.z-p.y*z, z*p.x-p.z*x, x*p.y-p.x*y);}

  Point3 mult(double d){ return Point3(x*d, y*d, z*d); }
  double len(){ return sqrt(x*x+y*y+z*z); }
  Point3 scale(double d){ return mult(d/len()); }
  double dist(Point3 p){ return sub(p).len(); }
  bool equals(Point3 p){ return EQ(dist(p), 0); }
};

vector<Point3> getbasis(Point3 z){
  z = z.scale(1);
  Point3 t = Point3(1, 0, 0);
  Point3 y = z.cross(t);
  if(EQ(y.len(), 0)){
    t = Point3(0, 1, 0);
    y = z.cross(t);
  }
  Point3 x = y.cross(z);
  y = y.scale(1); x = x.scale(1); //put these 2 if need orthonormal
  assert(x.cross(y).equals(z));
  vector<Point3> res;
  res.pb(x); res.pb(y); res.pb(z);
  return res;
}

Point3 trans(vector<Point3> B, Point3 p){
  return Point3(B[0].dot(p), B[1].dot(p), B[2].dot(p));
}

Point3 invtrans(vector<Point3> B, Point3 p){
  return B[0].mult(p.x).add(B[1].mult(p.y)).add(B[2].mult(p.z));
}
