/*
 * guild_reporter.h
 *
 *  Created on: Jul 28, 2014
 *      Author: edward
 */

#include "guild_reporter.h"
#include "caf/all.hpp"

using namespace caf;
using namespace std;

namespace modus {

guild_reporter::guild_reporter(guild * guild_member, int report_seconds, string actor_name, string addr, int port){
  if (report_seconds > guild_member->get_expire_in_seconds()) {
    throw "report_seconds must be greater than expire_seconds ";
  }  
  x = spawn(register_actor, guild_member, report_seconds, actor_name, addr, port);
  myguild = guild_member;
}

void guild_reporter::link_to(actor a) {
  a->link_to(x);
}

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

