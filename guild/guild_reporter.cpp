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
void register_actor(event_based_actor* self, guild_reporter * guild_reporter);

class guild_reporter {

public:
  guild_reporter(guild * guild_member, int report_seconds){
    this->guild_member = guild_member;
    x = spawn(register_actor, this&);
  }

  void register_actor_instance(actor a, string name){
  }

  int get_report_seconds(){
    return report_seconds;
  }
private:

  guild * guild_member;
  int report_seconds;
  actor x;
};

void register_actor(event_based_actor* self, guild_reporter * guild_reporter){
  self->send(self, atom("modus-tick"));
  self->become (
    on(atom("modus-tick")) >> [=] () {
      cout << "!!!tic!!!" << endl; // prints !!!Hello modus!!!
      //reporter send list of local actors
      self->delayed_send(self, 
        std::chrono::milliseconds(guild_reporter->get_report_seconds()*1000L), atom("modus-tick") );
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
