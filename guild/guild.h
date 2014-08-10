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
#include <set>

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
    //string path_to_actor_list = base_path + "/" + actor_name + "/" + actor_host + ":" +
    //(static_cast<ostringstream*>( &(ostringstream() << actor_port) )->str());
    string path_to_actor_list = base_path + "/" + actor_name ;
    Document * result = session->set(path_to_actor_list, actor_host + ":" +
	(static_cast<ostringstream*>( &(ostringstream() << actor_port) )->str())
	, expire_in_seconds);
    //detect error
    delete result;
  }

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
  vector<actor_info> search_actors(string actor_name){
    string path_to_actor_list = base_path + "/" + actor_name;
    Document * results = session->get(path_to_actor_list);
    set<string> values;
    vector <actor_info> res;
    if ( (!results->HasMember("errorCode")) && results->HasMember("action") ){
      Value& node = (*results)["node"];
      if (node.HasMember("nodes")){
        Value& nodes = node["nodes"];	
        assert(nodes.IsArray());
        for (SizeType i = 0; i < nodes.Size(); i++){
          Value& row = nodes[i];
          Value& ikey = row["key"];
          Value& value = row["value"];
          values.insert(value.GetString());
        }
      }
    }
    for ( auto it = values.begin(); it != values.end(); ++it ){
      size_t index = (*it).find(":");
      string host = (*it).substr(0,index);
      int port = atoi((*it).substr(index+1).c_str()) ;
      actor_info a(host,port);
      res.push_back(a);
    }
    delete results;
    return res;
  }

protected:
  etcd_session * session;
  int expire_in_seconds;
};

} //end modus namespace
#endif /* GUILD_H_ */
