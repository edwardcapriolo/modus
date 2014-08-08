/*
 * guild.h
 *
 *  Created on: Jul 23, 2014
 *      Author: edward
 */

#ifndef GUILD_H_
#define GUILD_H_
#include <iostream>
#include <sstream>
#include <etcdcpp/libetcdcpp.cxx>

using namespace std;
using namespace etcdcpp;

namespace modus {

class actor_info {
public:
  string host;
  unsigned short port;
};


/*
 * A registry for actors backed by etcd
 */
class guild {

public:
  const string base_path = "/actors";

  guild(etcd_session * session, int expire_in_seconds) {
    this->expire_in_seconds = expire_in_seconds;
    this->session = session;
  }

  void register_actor (string actor_name, string actor_host, int actor_port){
    string path_to_actor_list = base_path + "/" + actor_name + "/" + actor_host + ":" +
    (static_cast<ostringstream*>( &(ostringstream() << actor_port) )->str());
    Document * result = session->set(path_to_actor_list, "", expire_in_seconds);
    //detect error
    delete result;
  }

  vector<actor_info> search_actors(string actor_name){
    string path_to_actor_list = base_path + "/" + actor_name;
    Document * results = session->get(path_to_actor_list);
    //parse results
    delete results;
    vector <actor_info> res;
    return res;
  }

protected:
  etcd_session * session;
  int expire_in_seconds;
};

} //end modus namespace
#endif /* GUILD_H_ */
