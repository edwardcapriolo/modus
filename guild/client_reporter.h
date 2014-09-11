/*
 * guild_reporter.h
 *
 *  Created on: Jul 28, 2014
 *      Author: edward
 */

#ifndef CLIENT_REPORTER_H_
#define CLIENT_REPORTER_H_

//#include <string>
#include "guild.h"
#include "caf/all.hpp"

using namespace caf;
using namespace std;

namespace modus {

class client_reporter {
  public:
    client_reporter(guild * guild_member, int report_seconds, string actor_name, 
                    string addr, int port, string client_id);

    guild * get_guild() { return myguild; }

    void link_to(actor a);

  private:
    actor x;
    guild * myguild;
};

void register_client(event_based_actor* self, guild * guild, int report_seconds, string actor_name, string addr, short unsigned int port, string client_id);

} //end namespace

#endif /* CLIENT_REPORTER_H_ */

