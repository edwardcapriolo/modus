//============================================================================
// Name        : modus.cpp
// Author      : Edward Capriolo
// Version     :
// Copyright   : Apache V2
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <chrono>
#include <iostream>
#include <algorithm>
#include "cppa/cow_tuple.hpp"
#include "cppa/cppa.hpp"
#include "guild.h"
#include "cppa/event_based_actor.hpp"
#include "cppa/local_actor.hpp"
#include "cppa/atom.hpp"
#include "guild_reporter.h"


using namespace cppa;
using namespace std;
using namespace modus;

int main() {
	cout << "!!!Hello modus!!!" << endl; // prints !!!Hello modus!!!
	auto x1 = make_cow_tuple(1, 2, 3);
	cow_tuple<int,int,int> x2 = make_cow_tuple(1, 2, 3);
	cow_tuple<int,string,int> x3 = make_cow_tuple(1, "hi", 3);
	//char            *servers        = getenv("ETCD_SERVERS");
	guild g (strdup("127.0.0.1:4001"), 200);
	guild_reporter reporter( &g , 5, "127.0.0.1", 9999);
	cout << "!!!Hello modus!!!" << endl; // prints !!!Hello modus!!!
	await_all_actors_done();
	return 0;

}

/*
 * void register_actor(event_based_actor* self){
  self->send(self, atom("modus-tick"));
  self->become (
	on(atom("modus-tick")) >> [=] () {
	  cout << "!!!tic!!!" << endl; // prints !!!Hello modus!!!
	  self->delayed_send(self, std::chrono::milliseconds(5000), atom("modus-tick") );
  	 }
  );
}
 */

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
