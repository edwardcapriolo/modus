/*
 * guild_reporter.h
 *
 *  Created on: Jul 28, 2014
 *      Author: edward
 */

#ifndef CLIENT_REPORTER_H_
#define CLIENT_REPORTER_H_
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

class client_reporter {
public:
  client_reporter(guild * guild_member, int report_seconds, string actor_name,
                 string addr, int port, string client_id){
    x = spawn(register_client, guild_member, report_seconds, actor_name, addr, port, client_id);
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
} //end reporter

} //end namespace

#endif /* CLIENT_REPORTER_H_ */

