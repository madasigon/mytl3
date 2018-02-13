#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#ifndef GEOM_CPP
#define GEOM_CPP

//STARTCOPY
namespace mytl{

struct Point{
    ll x, y;

    Point(ll x, ll y) : x{x}, y{y} {};
    Point(pair<ll,ll> initPair) : x{initPair.first}, y{initPair.second} {};

    pair<ll,ll> getPair(){//not introducing type cast operator for safety
        return {x,y};
    }

    //Unary operators
    Point operator-() const{
        return {-x, -y};
    }
    Point operator+() const{
        return {x,y};
    }

    static ll sgn(ll x){
        return (x > 0) - (x < 0);
    }

    //Binary operators on ordinary numbers
    Point operator*(const ll& operand) const{
        return {x*operand, y*operand};
    }

    //Binary operators on Point itself
    Point operator+(const Point& operand) const{
        return {x+operand.x, y+operand.y};
    }
    Point operator-(const Point& operand) const{
        return {x-operand.x, y-operand.y};
    }

    ll operator*(const Point& operand){ //vectorial product
        return x*operand.y - y*operand.x;
    }

    ll direction(const Point& a, const Point& b) const{
        return sgn((a - *this) * (b - *this));
    };
};

typedef vector<Point> Poly;

bool inside(const Poly& poly, const Point& point, bool strict){
    set<int> dirs;
    for(int i=0; i<poly.size(); i++){
        int nexdindex = (i+1)%poly.size();
        int dir = poly[i].direction(poly[nexdindex], point);
        if(dir == 0){
            if(strict) return false;
        }
        else{
            dirs.insert(dir);
            if(dirs.size() > 1) return false;
        }

    }
    return true;
}

}
//ENDCOPY

#endif
