#include "guild.h"
#include "guild_reporter.cpp"
#include <iostream>
#include <etcdcpp/libetcdcpp.cpp>
#include <vector>

using namespace std;
using namespace etcdcpp;
using namespace modus;

int main () {
  etcd_host h("localhost", 4001);
  vector<etcd_host> host_list;
  host_list.push_back(h);
  etcd_session s(host_list);
  guild g(&s,20);
  guild_reporter rep(&g,5); 
  g.register_actor("myactor", "localhost", 8808);
  g.register_actor("myactor", "mocalhost", 8809);

  sleep(15);
  vector<actor_info> a = g.search_actors("myactor");
  cout << "found actors" << a.size() << endl;
  //await_all_actors_done();

}
