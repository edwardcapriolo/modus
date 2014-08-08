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
void register_actor(event_based_actor* self, guild * guild, int report_seconds);

class guild_reporter {
public:
  guild_reporter(guild * guild_member, int report_seconds){
    x = spawn(register_actor, guild_member, report_seconds);
  }
private:
  actor x;
};

void register_actor(event_based_actor* self, guild * guild, int report_seconds){
  self->send(self, atom("modus-tick"));
  self->become (
    on(atom("modus-tick")) >> [=] () {
      cout << "!!!tic!!!" << endl; // prints !!!Hello modus!!!
      //get list of local actors
      //guild.register
      //TODO DEBUG REMOVE
      guild->register_actor("myactor", "localhost", 8808);
      self->delayed_send(self, 
        std::chrono::milliseconds(report_seconds * 1000L), atom("modus-tick") );
    }
  );
} //end reporter

} //end namespace

#endif /* GUILD_REPORTER_H_ */

