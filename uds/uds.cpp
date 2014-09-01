#include "uds.h"
#include "caf/all.hpp"
#include "caf/io/all.hpp"
#include "feed_def.h"
#include "modus_context.h"
using namespace std;
using namespace caf;
using namespace modus;

int main (){
  obj o;
  //cout << o.data.find("stuff")->second << endl;
  announce<insert_request>(&insert_request::t, &insert_request::f);
  scoped_actor self;
  auto et = self->spawn_typed<uds_actor>();
  from f;
  f.id = 4;
  insert_request r;
  r.t = o;
  r.f = f;
  self->send(et, r);
  
  file_feed_def<int> f1 (file_feed_def<int>(string("/tmp/a")));
  modus_context m ;
  uds_def<int> d = m.load(f1);
  Fx<double,int> convert;
  uds_def<double> n = d.map( convert);
  
  
}
