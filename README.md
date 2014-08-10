Modus
========

An actor registry and discovery service for libcaf https://github.com/actor-framework/actor-framework

Modus runs a threaded actor as a service that (will soon) automatically register TTL records in https://github.com/coreos/etcd . For now users can manually register actors in the guild and ask the guild which actors are running where.

Example
======

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
      sleep(15);
      vector<actor_info> a = g.search_actors("myactor");
      cout << "found actors" << a.size() << endl;
    }
