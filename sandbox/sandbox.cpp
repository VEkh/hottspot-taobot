#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include "ml/five_min_predict/five_min_predict.cpp" // ML::FiveMinPredict
#include <list>                                     // std::list
#include <map>                                      // std::map
#include <time.h>                                   // time

int main(int argc, char *argv[]) {
  Pg conn((std::map<std::string, std::string>){
      {"env", "production"},
  });
  conn.connect();

  ML::FiveMinPredict five_min_predict(conn, "AMZN");

  printf("should predict: %i\n",
         (int)five_min_predict.should_predict("live-alpha"));

  conn.disconnect();
}
