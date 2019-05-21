#include <iostream>
#include <cassert>

using namespace mytl;

// TODO I would send this as a tool, but I need a get() function right now in the input
// which would invalidate half of the usages of the function :(
template <typename UnitIn, typename UnitOut>
class Vector {
    std::vector<UnitOut> vec;
public:
    template <typename... Args>
    Vector(UnitIn size, Args... args) :
        vec (size.get(), UnitOut(args...)) { }
    UnitOut& operator[](UnitIn idx) {
        assert(idx.get() >= 0 && idx.get() < (int)vec.size());
        return vec[idx.get()];
    }
    UnitIn size() const { return UnitIn(vec.size()); }
    const UnitOut& operator[](UnitIn idx) const {
        assert(idx.get() >= 0 && idx.get() < (int)vec.size());
        return vec[idx.get()];
    }
    template<typename... Args>
    inline auto getSumRange(UnitIn i1, UnitIn i2, Args... args)
            -> decltype (operator[](0).getSumRange(args...)) {
        --i1;
        return operator[](i2).getSumRange(args...) - operator[](i1).getSumRange(args...);
    }

};

template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const Vector<T,U>& u) {
    os << "\n" << u[0] << "(0) ";
    for (T i(1); i < u.size(); ++i) {
        os << ' ' << u[i] << '(' << i << ") ";
    }
    return os;
}

using Row = Unit<int,0,0,1>;
using Column = Unit<int,0,1,0>;
using Value = Unit<int,1,0,0>;
using Accumulated = Unit<int,1,0,0>;
using Query = Unit<int,1,0,0,0>;

Row operator"" _r(unsigned long long val) { return Row(val); }
Column operator"" _c(unsigned long long val) { return Column(val); }
Value operator"" _v(unsigned long long val) { return Value(val); }
Accumulated operator"" _a(unsigned long long val) { return Accumulated(val); }
Query operator"" _q(unsigned long long val) { return Query(val); }


using RowVector = Vector<Column, Value>;
using Map = Vector<Row, RowVector>;

using RowVectorAcc = Vector<Column, Accumulated>;
using MapAcc = Vector<Row, RowVectorAcc>;
using RowMapAcc = Vector<Column, MapAcc>;
using HyperMap = Vector<Row, RowMapAcc>;

int main() {
    Row N;
    Column M;
    Query Q;
    std::cin >> N >> M >> Q;
    auto T = Map(N+1, M+1, 0);
    for (auto i = 1_r; i <= N; ++i) {
        for (auto j = 1_c; j <= M; ++j) {
            char c = -1;
            while (c <= 32) std::cin >> c;
            assert(c == '0' || c == '1');
            T[i][j] = Value(c-'0')-T.getSumRange(i, i, j, j);
        }
    }
    auto V = HyperMap(N+1, M+1, N+1, M+1, 0);
    for (auto i = 1_r; i <= N; ++i) {
        for (auto j = 1_c; j <= M; ++j) {
            for (auto k = i; k <= N; ++k) {
                for (auto l = j; l <= M; ++l) {
                    Accumulated v = 0_v;
                    if (T.getSumRange(i, k, j, l) == 0_v) {
                        v = 1_v;
                    }
                    V[i][j][k][l] = v;
                }
            }
        }
    }
    for (auto i = 1_r; i <= N; ++i) {
        for (auto j = 1_c; j <= M; ++j) {
            for (auto k = 1_r; k <= N; ++k) {
                for (auto l = 1_c; l <= M; ++l) {
                    Accumulated v = 0_v;
                    if (T.getSumRange(i, k, j, l) == 0_v) {
                        v = 1_v;
                    }
                    V[i][j][k][l] = 2*V[i][j][k][l] - V.getSumRange(i, i,
                            j, j, k, k, l, l);
                }
            }
        }
    }
    for (auto i = 1_q; i <= Q; ++i) {
        Row r1,r2;
        Column c1,c2;
        std::cin >> r1 >> c1 >> r2 >> c2;
        assert(1_r <= r1 && r1 <= N);
        assert(1_c <= c1 && c1 <= M);
        assert(1_r <= r2 && r2 <= N);
        assert(1_c <= c2 && c2 <= M);
        std::cout << V.getSumRange(r1,r2,c1,c2,r1,r2,c1,c2) << std::endl;
    }
}
