/* 
 * File:   uds_def.h
 * Author: edward
 *
 * Created on August 31, 2014, 9:03 PM
 */

#ifndef UDS_DEF_H
#define	UDS_DEF_H
#include "feed_def.h"

template <class Return, class Takes>
class Fx {
    
};
template <class Returns, class Takes>
class uds_map_def;

template <class Returns, class Takes>
class uds_reduce_def;

template <class MyType>
class uds_def {
public:
  uds_def(){
        
  }
  void set_feed(feed_def<MyType> aDef){
    feed = aDef;    
  }
  
  template<class Returns>
  uds_def<Returns> map( Fx<Returns,MyType> fx){
    uds_map_def<Returns, MyType> result;
    result.parent = this;
    result.mapFx = fx;
    return result;
  }
  
  template<class  Returns>
  uds_def<Returns> reduce  (Fx<Returns,MyType> fx){
    uds_reduce_def<Returns,MyType> result;
    result.parent = this;
    result.reduceFx = fx;
    return result;
  }
  uds_def* parent;
private:
  feed_def<MyType> feed;
};

template <class Returns, class Takes>
class uds_map_def : public uds_def<Returns> {
public:
  uds_map_def(){
  }
  Fx <Returns, Takes> mapFx;
  uds_def<Takes>* parent;
private:       
};

template <class Returns, class Takes>
class uds_reduce_def : public uds_def<Returns> {
public:    
  uds_reduce_def(){
        
  }
  Fx <Returns, Takes> reduceFx;
  uds_def<Takes>* parent;
};

#endif	/* UDS_DEF_H */
