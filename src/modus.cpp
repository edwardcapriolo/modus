//============================================================================
// Name        : modus.cpp
// Author      : Edward Capriolo
// Version     :
// Copyright   : Apache V2
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#include "cppa/cow_tuple.hpp"
#include "cppa/cppa.hpp"

#include "guild.h"


using namespace cppa;

int main() {
	cout << "!!!Hello modus!!!" << endl; // prints !!!Hello modus!!!
	auto x1 = make_cow_tuple(1, 2, 3);
	cow_tuple<int,int,int> x2 = make_cow_tuple(1, 2, 3);
	cow_tuple<int,string,int> x3 = make_cow_tuple(1, "hi", 3);
	//char            *servers        = getenv("ETCD_SERVERS");
	guild g ("127.0.0.1:4001", 200);
	g.register_actor("bob","127.0.0.1", 6000);
	return 0;

}

/*
char            *servers        = "127.0.0.1:4001";
etcd_session sess;
sess = etcd_open_str (strdup(servers));
if (!sess) {
	fprintf(stderr, "etcd_open failed\n");
	return !0;
}
char * key = "/actors/a";
char * me = "bla";

etcd_result  r =   etcd_set (sess, key, me, NULL, 200);
if (!r){
	fprintf(stderr, "nor\n");
	return !0;
}
*/
