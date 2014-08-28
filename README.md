Modus
========

An actor registry and discovery service for libcaf https://github.com/actor-framework/actor-framework

Modus is a library that helps network actors communicate host port information so other actors can discover them.

Building
======
You will need https://github.com/edwardcapriolo/etcdcpp checked out at the same folder level as modus. curl and simplejson are other dependencies.

Guild reporter
======

An actor that registers with etcd by sending periodic messages
  
    //create a guild. A guild is a registry of actors in etcd
    etcd_session s(etcd_host("localhost", 4001));
    guild g(&s, 20);
  
    //create a network based actor
    int server_port = 9995;  
    auto netcalc = spawn(calculator);
    io::publish(netcalc, server_port);
      
    //create a guild reporter and link it to the calculator actor
    guild_reporter rep(&g, 5, "calculator", "localhost", server_port);
    rep.link_to(netcalc);
    
Client reporter
======

An actor that records information about which clients are connected to what actors.

    vector<actor_info> a = guild->search_actors("calculator");
    //pick a random one, try them all?
    if (a.size() == 0) {
      throw "No actors found";
    }
    auto new_serv = io::remote_actor(a[0].host, a[0].port);
    self->monitor(new_serv);
      
    string my_id = "42";
    client_reporter cli(guild, 5, "calculator", a[0].host, a[0].port, my_id );
    cli.link_to(new_serv);

See netdemo.cpp for the full source code.

Storage in etcd
======

The guild and client reporters store information in etcd. It looks like this:

    {"action":"get","node":{"key":"/","dir":true,"nodes":[
      {"key":"/actors","dir":true,"nodes":[
        {"key":"/actors/calculator","dir":true,"nodes":[
          {"key":"/actors/calculator/17","value":"localhost:9995","expiration":"2014-08-25T19:23:56.028685548-04:00","ttl":54,"modifiedIndex":17,"createdIndex":17}],"modifiedIndex":3,"createdIndex":3}],"modifiedIndex":3,"createdIndex":3},
    {"key":"/actor_client","dir":true,"nodes":[
      {"key":"/actor_client/calculator","dir":true,"nodes":[
        {"key":"/actor_client/calculator/18","value":"localhost:9995@42","expiration":"2014-08-25T19:23:56.035186558-04:00","ttl":54,"modifiedIndex":18,"createdIndex":18}],"modifiedIndex":8,"createdIndex":8}],"modifiedIndex":8,"createdIndex":8}]}}

These entries are TTL based. It is important to note that this means that this informtion is not 'atomic'. An actor could die after creating a record. It is up to the client to poll and retry. This design was for general purpose use, future enhancements could create more fine grained networks.
