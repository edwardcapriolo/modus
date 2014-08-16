#include "guild.h"
#include "guild_reporter.cpp"
#include <iostream>
#include <etcdcpp/libetcdcpp.cpp>
#include <vector>
#include <chrono>
#include <thread>

#include "caf/all.hpp"
#include "caf/io/all.hpp"

using namespace std;
using namespace caf;
using namespace modus;

void calculator(event_based_actor* self) {
  self->become (
    on(atom("plus"), arg_match) >> [](int a, int b) -> message {
      return make_message(atom("result"), a + b);
    },
    on(atom("minus"), arg_match) >> [](int a, int b) -> message {
      return make_message(atom("result"), a - b);
    },
    on(atom("quit")) >> [=] {
      self->quit();
    }
  );
}

void client_bhvr(event_based_actor* self, guild_reporter *rep, const actor& server) {
   if (!self->has_sync_failure_handler()) {
    self->on_sync_failure([=] {
      aout(self) << "*** sync_failur connection. Attempt reconnect " << endl;
      client_bhvr(self, rep, invalid_actor);
    });
  }

  if (!server) {
    aout(self) << "*** try to re-connect " << endl;
    try {
      vector<actor_info> a = rep->get_guild()->search_actors("calculator");
      //pick a random one, try them all?
      if (a.size() == 0) {
        throw "No actors found";
      }
      auto new_serv = io::remote_actor(a[0].host,a[0].port);
      self->monitor(new_serv);
      aout(self) << "reconnection succeeded" << endl;
      client_bhvr(self, rep, new_serv);
      return;
    }
    catch (exception&) {
      aout(self) << "connection failed, try again in 3s" << endl;
      self->delayed_send(self, chrono::seconds(3), atom("reconnect"));
    }
  }

  auto pred = [=](atom_value val) -> optional<atom_value> {
    if (server != invalid_actor
        && (val == atom("plus") || val == atom("minus"))) {
      return val;
    }
    return none;
  };

  self->become (
    on(pred, arg_match) >> [=](atom_value op, int lhs, int rhs) {
      self->sync_send_tuple(server, self->last_dequeued()).then(
        on(atom("result"), arg_match) >> [=](int result) {
          aout(self) << lhs << " "
                 << to_string(op) << " "
                 << rhs << " = "
                 << result << endl;
        }
      );
    },
    [=](const down_msg&) {
      aout(self) << "*** server down, try to reconnect ..." << endl;
      client_bhvr(self, rep, invalid_actor);
    }
  );

}

int main (){

  //Create a registry service
  etcd_host h("localhost", 4001);
  vector<etcd_host> host_list;
  host_list.push_back(h);
  etcd_session s(host_list);
  guild g(&s, 20);
  guild_reporter rep(&g, 5);

  // create actor  
  int server_port = 9995;
  io::publish(spawn(calculator), server_port);

  //publish actor to guild manually until we auto-detect
  g.register_actor("calculator", "localhost", server_port);

  auto client = spawn(client_bhvr, &rep, invalid_actor);
  
  //where does this go?
  anon_send(client, atom("plus"), 1, 2);

  await_all_actors_done();
}
