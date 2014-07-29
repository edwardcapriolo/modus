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

using namespace cppa;
using namespace std;

namespace modus {
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

class guild_reporter {

public:
  guild_reporter(guild * guild_member, int report_seconds){
    this->guild_member = guild_member;
    this->report_seconds = report_seconds;
     x = spawn(modus::register_actor);
  }

  void register_actor_instance(){

  }


private:

  vector<actor> actors;
  vector<string> names;
  guild * guild_member;
  int report_seconds;
  actor x;
};


#endif /* GUILD_REPORTER_H_ */

