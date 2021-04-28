#include <mpd/client.h>
#include <iostream>
#include <string.h>
#include <set>
#include <vector>

#define ll long long
#define endl "\n"
#define IOS cin.tie(0);cout.tie(0);ios::sync_with_stdio(0);
using namespace std;

mpd_connection *conn;
mpd_song *song;
set<string> songs;
vector<mpd_song*> queue;

bool addsongs();
bool getsongs();
bool connect();
void readqueue();

ll range(ll a,ll b);
