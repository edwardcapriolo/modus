/*
 * guild.h
 *
 *  Created on: Jul 23, 2014
 *      Author: edward
 */

#ifndef GUILD_H_
#define GUILD_H_

#include <etcdcpp/etcdcpp.h>

using namespace std;
using namespace etcdcpp;

namespace modus {

class actor_info {
  public:
    actor_info(string host, short port): host(host), port(port) {}

    string get_host() { return host; }    

    unsigned short get_port() { return port; }

  private:
    string host;
    unsigned short port;
};


/*
 * A registry for actors backed by etcd
 */
class guild {

public:
  static const string base_path;
  static const string actor_client_base;

  guild(etcd_session * session, int expire_in_seconds): expire_in_seconds(expire_in_seconds), session(session) {}

  void register_actor (string actor_name, string actor_host, int actor_port);

  /*
   Register a ttl record to signify a client is connected 
   */
  void client_connect(string actor_name, string actor_host, int actor_port, string client_id);

  /*
  {"action":"get","node":
   {"key":"/actors/myactor","dir":true,"nodes":
     [{"key":"/actors/myactor/3","value":"localhost:8808","expiration":"2014-08-09T17:55:26.211706122-04:00","ttl":52,"modifiedIndex":3,"createdIndex":3},
      {"key":"/actors/myactor/4","value":"mocalhost:8809","expiration":"2014-08-09T17:55:26.214349689-04:00","ttl":52,"modifiedIndex":4,"createdIndex":4},
      {"key":"/actors/myactor/5","value":"localhost:8808","expiration":"2014-08-09T17:55:31.222940547-04:00","ttl":57,"modifiedIndex":5,"createdIndex":5},
      {"key":"/actors/myactor/6","value":"mocalhost:8809","expiration":"2014-08-09T17:55:31.224809533-04:00","ttl":57,"modifiedIndex":6,"createdIndex":6}
     ],"modifiedIndex":3,"createdIndex":3
   }
}
  */
  vector<actor_info> search_actors(string actor_name);

  int get_expire_in_seconds(){ return expire_in_seconds; }  
  
protected:
  etcd_session * session;
  int expire_in_seconds;
};

} //end modus namespace
#endif /* GUILD_H_ */

