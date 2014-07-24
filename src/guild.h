/*
 * guild.h
 *
 *  Created on: Jul 23, 2014
 *      Author: edward
 */

#ifndef GUILD_H_
#define GUILD_H_
extern "C" {
    #include "etcd-api.h"
}
#include <iostream>

using namespace std;

/*
 * A registry for actors backed by etcd
 */
class guild {

public:
  const string base_path = "/actors";
  guild(char *servers, int expire_in_seconds) {
    sess = etcd_open_str (strdup(servers));
    this->expire_in_seconds = expire_in_seconds;
	if (!sess) {
      fprintf(stderr, "etcd_open failed\n");
	  throw 1;
	}
  }

  void register_actor (char *actor_name, char *actor_host, int actor_port){
    char * path_to_actor_list ;
    path_to_actor_list += base_path + "/" + actor_name + "/" + "actor_host" + ":" + actor_port;
    etcd_result  r =   etcd_set (sess, path_to_actor_list, "", NULL, expire_in_seconds);
	if (!r){
	  fprintf(stderr, "nor\n");
	  throw 2;
	}
  }

private:
  etcd_session sess;
  int expire_in_seconds;
};


#endif /* GUILD_H_ */
