#ifndef UDS_H
#define	UDS_H

#include <vector>
#include <map>
#include <string>
#include <iostream>

#include "guild.h"
#include "modus_context.h"


#include <cassert>
#include <utility>
#include <iostream>

#include "caf/all.hpp"
#include "caf/binary_serializer.hpp"
#include "caf/binary_deserializer.hpp"

using namespace std;
using namespace modus;
using namespace caf;

namespace modus {
    
class obj {
public:
    int x;
    int y;
    char * g;
};

class from {
public:
  int id;    
};

template <class c>
class iter {
  c next();
  bool has_next();
};
    
template <class Ts>
class uds {
public:
    
  uds(modus_context c, int number_of_partitions, string partition_strategy, 
      map<string,string> fields, vector<string> unique_key,
      vector<string> order_fields, vector<string> partition_fields){
     this->number_of_partitions = number_of_partitions;
     this->partition_strategy = partition_strategy;
     this->fields = fields;
     this->unique_key = unique_key;
     this->order_fields = order_fields;
     this->partition_fields = partition_fields;
  }
    
  /* inserts data, if unique_key is defined exception will be 
   * thrown if constraint is violated */
  void insert(Ts &t, from& from);
  /* if unique_key is defined update, else insert
   */
  void upsert (Ts &t, from& from);
  /*using the unique_key remove this object*/
  void remove (Ts &t, from& from);
  
  /* We have reached a checkpoint or can safely remove all the output from from*/
  void remove (from& from);
  
  /*
   * using the unique_key fields attempt to find this data
   */
  Ts find (Ts &f);
  iter<Ts> scan (Ts &start);
  iter<Ts> scan (Ts &start, Ts &end);
private:
  int number_of_partitions;
  string partition_strategy;
  map<string,string> fields;
  vector<string> unique_key;
  vector<string> order_fields;
  vector<string> partition_fields;
};
     

//obj to_insert; from f;
struct insert_request { obj t; from f; };
struct find_request { obj to_insert; from f; };

bool operator==(const insert_request& lhs, const insert_request& rhs) {
  return false;
}

bool operator==(const find_request& lhs, const find_request& rhs) {
  return false;
}
    

using uds_actor_type = typed_actor< 
        replies_to<insert_request>::with<void>,
        replies_to<find_request>::with<void>>;


class uds_actor : public uds_actor_type::base {
private:

public:

protected:
  behavior_type make_behavior() override {
    return {
      [=](const insert_request& pr) {
        cout << "inserting" << endl;
        
      },
      [=](const find_request& pr) {
        //return pr.a - pr.b;
      }
    };
  }
};

}
#endif	/* UDS_H */

