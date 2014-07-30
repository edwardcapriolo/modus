/*
 * guild_reporter.h
 *
 *  Created on: Jul 28, 2014
 *      Author: edward
 */

#ifndef GUILD_REPORTER_H_
#define GUILD_REPORTER_H_
#include <chrono>
#include <vector>
#include <string>
#include "cppa/cppa.hpp"
#include "guild.h"
#include "cppa/actor.hpp"
#include "cppa/spawn.hpp"
#include <iostream>

using namespace cppa;
using namespace std;

namespace modus {

//Put this here so it is free fx

void register_actor(event_based_actor * );
class guild_reporter {

public:
  guild_reporter(guild * guild_member, int report_seconds, string report_host, int report_port){
    this->guild_member = guild_member;
    this->report_seconds = report_seconds;
    this->host = report_host;
    this->port = report_port;
     x = spawn(register_actor);
  }

  void register_actor_instance(actor a, string name){
	this->actors.push_back(a);
    this->names.push_back(name);
  }


private:

  vector<actor> actors;
  vector<string> names;
  guild * guild_member;
  string host;
  int port;
  int report_seconds;
  actor x;
};

void register_actor(event_based_actor* self){
	  self->send(self, atom("modus-tick"));
	  self->become (
		on(atom("modus-tick")) >> [=] () {
		  cout << "!!!tic!!!" << endl; // prints !!!Hello modus!!!
		  self->delayed_send(self, std::chrono::milliseconds(5000), atom("modus-tick") );
		 }
	   );
	 }

}



#endif /* GUILD_REPORTER_H_ */

/*
char* c = new char[name.length() + 1];
strcpy(c, name.c_str());
guild_member->register_actor(c, strdup("127.0.0.01"), 7777);
	*/
