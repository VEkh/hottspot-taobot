#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include "db/five_min_prediction/five_min_prediction.cpp" // DB::FiveMinPrediction
#include <list>                                           // std::list
#include <map>                                            // std::map
#include <time.h>                                         // time

int main(int argc, char *argv[]) {
  Pg conn((std::map<std::string, std::string>){
      {"env", "production"},
  });
  conn.connect();

  DB::FiveMinPrediction db_five_min_predictor(conn, "AMZN");

  std::list<DB::FiveMinPrediction::prediction_t> predictions =
      db_five_min_predictor.get_fresh_predictions((double)time(nullptr), true);

  printf("predictions count: %i\n", (int)predictions.size());

  conn.disconnect();
}
