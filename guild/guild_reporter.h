/*
 * guild_reporter.h
 *
 *  Created on: Jul 28, 2014
 *      Author: edward
 */

#ifndef GUILD_REPORTER_H_
#define GUILD_REPORTER_H_

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
    guild_reporter(guild * guild_member, int report_seconds, string actor_name, string addr, int port);

    guild * get_guild(){ return myguild; }

    void link_to(actor a);

  private:
    actor x;
    guild * myguild;
};

void register_actor(event_based_actor* self, guild * guild, int report_seconds, string actor_name, string addr, int port);

} //end namespace

#endif /* GUILD_REPORTER_H_ */

