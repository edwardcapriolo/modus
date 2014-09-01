/* 
 * File:   feed_def.h
 * Author: edward
 *
 * Created on August 31, 2014, 9:05 PM
 */

#ifndef FEED_DEF_H
#define	FEED_DEF_H
#include <iostream>
#include <sstream>
using namespace std;

template <class T>
class feed_def {
  public:
    feed_def(){
            
    }
};

template<class T>
class file_feed_def : public feed_def<T> {
public:
  file_feed_def(string filename){
    this->filename = filename;
  }
private:
  string filename;  
};




#endif	/* FEED_DEF_H */

