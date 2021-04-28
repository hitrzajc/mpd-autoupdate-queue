#include <random>
#include <chrono>
#define ll long long
using namespace std;

//64bit
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
//32bit
//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll range(ll a,ll b){ //interval [a,b]
    return uniform_int_distribution<ll>(a,b)(rng);
}