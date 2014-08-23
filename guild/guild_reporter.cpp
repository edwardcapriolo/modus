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
#include "guild.h"
#include <iostream>
#include "caf/all.hpp"

using namespace caf;
using namespace std;

namespace modus {

void register_actor(event_based_actor* self, guild * guild, int report_seconds, 
                    string actor_name, string addr, int port);

class guild_reporter {
public:
  guild_reporter(guild * guild_member, int report_seconds, string actor_name,
                 string addr, int port){
    x = spawn(register_actor, guild_member, report_seconds, actor_name, addr, port);
    myguild = guild_member;
  }
  guild * get_guild(){
    return myguild;
  }
  void link_to(actor a){
    a->link_to(x);
  }
private:
  actor x;
  guild * myguild;
};

void register_actor(event_based_actor* self, guild * guild, int report_seconds,
                    string actor_name, string addr, int port){
  self->send(self, atom("modus-tick"));
  self->become (
    on(atom("modus-tick")) >> [=] () {
      guild->register_actor(actor_name, addr, port);
      self->delayed_send(self, 
        std::chrono::milliseconds(report_seconds * 1000L), atom("modus-tick") );
    }
  );
} //end reporter

} //end namespace

#endif /* GUILD_REPORTER_H_ */

