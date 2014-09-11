/*
 * guild_reporter.h
 *
 *  Created on: Jul 28, 2014
 *      Author: edward
 */

#include "client_reporter.h"
#include <chrono>
#include <vector>
#include <string>
#include "guild.h"
#include <iostream>
#include "caf/all.hpp"

using namespace caf;
using namespace std;

namespace modus {

void register_client(event_based_actor* self, guild * guild, int report_seconds, 
                    string actor_name, string addr, short unsigned int port, string client_id);

client_reporter::client_reporter(guild * guild_member, int report_seconds, string actor_name,
                                 string addr, int port, string client_id){
  x = spawn(register_client, guild_member, report_seconds, actor_name, addr, port, client_id);
  myguild = guild_member;
}

void client_reporter::link_to(actor a){
  a->link_to(x);
}

void register_client(event_based_actor* self, guild * guild, int report_seconds,
                    string actor_name, string addr, short unsigned int port, string client_id){
  self->send(self, atom("modus-tick"));
  self->become (
    on(atom("modus-tick")) >> [=] () {
        guild->client_connect(actor_name, addr, port, client_id);
      self->delayed_send(self, 
        std::chrono::milliseconds(report_seconds * 1000L), atom("modus-tick") );
    }
  );
} 

} //end namespace

