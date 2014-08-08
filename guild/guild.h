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
#include <etcdcpp/libetcdcpp.cpp>

using namespace std;
using namespace etcdcpp;

namespace modus {

class actor_info {
public:
  actor_info(string host, short port){
    this -> host = host;
    this -> port = port;
  }
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

  /*
  {"action":"get","node":
  {"key":"/message/b","dir":true,"nodes":
    [
      {"key":"/message/b/24","value":"dah","modifiedIndex":24,"createdIndex":24},
      {"key":"/message/b/27","value":"dah","modifiedIndex":27,"createdIndex":27},
      {"key":"/message/b/30","value":"dah","modifiedIndex":30,"createdIndex":30},
      {"key":"/message/b/34","value":"dah","modifiedIndex":34,"createdIndex":34},
      {"key":"/message/b/38","value":"dah","modifiedIndex":38,"createdIndex":38},
      {"key":"/message/b/42","value":"dah","modifiedIndex":42,"createdIndex":42},
      {"key":"/message/b/47","value":"dah","modifiedIndex":47,"createdIndex":47},
      {"key":"/message/b/51","value":"dah","modifiedIndex":51,"createdIndex":51}
    ],"modifiedIndex":24,"createdIndex":24}}
  */
  vector<actor_info> search_actors(string actor_name){
    string path_to_actor_list = base_path + "/" + actor_name;
    Document * results = session->get(path_to_actor_list);
    //parse results
    Value& node = (*results)["node"];
    Value& key = node["key"];	
    cout << key.GetString();
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
