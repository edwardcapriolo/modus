/*
 * guild.h
 *
 *  Created on: Jul 23, 2014
 *      Author: edward
 */

#include "guild.h"
#include <string>
#include <iostream>
#include <sstream>
#include <etcdcpp/libetcdcpp.h>
#include <set>

using namespace std;
using namespace etcdcpp;

namespace modus {
 
const string guild::base_path = "/actors";

const string guild::actor_client_base = "/actor_client";

void guild::register_actor (string actor_name, string actor_host, int actor_port) {
  string path_to_actor_list = base_path + "/" + actor_name ;
  ostringstream value_stream;
  value_stream << actor_host << ":" << actor_port;
  string value = value_stream.str();
  std::unique_ptr<Document> result = session->set(path_to_actor_list, value, expire_in_seconds);
  //detect error
}

/*
 Register a ttl record to signify a client is connected 
 */
void guild::client_connect(string actor_name, string actor_host, int actor_port, string client_id) {
  string path_to_actor_list = actor_client_base + "/" + actor_name;
  ostringstream value_stream;
  value_stream << actor_host << ":" << actor_port << "@" << client_id;
  string value = value_stream.str();
  std::unique_ptr<Document> result = session->set(path_to_actor_list, value, expire_in_seconds);
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
vector<actor_info> guild::search_actors(string actor_name) {
  string path_to_actor_list = base_path + "/" + actor_name;
  std::unique_ptr<Document> results = session->get(path_to_actor_list);
  set<string> values;
  vector <actor_info> res;
  if ((!results->HasMember("errorCode")) && results->HasMember("action")) {
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

  for (auto it : values) {
    size_t index = it.find(":");
    string host = it.substr(0,index);
    int port = atoi(it.substr(index+1).c_str()) ;
    actor_info a(host,port);
    res.push_back(a);
  }
  return res;
}

} //end modus namespace

