#include <iostream>
#include "header.h"

using namespace std;

void calc_turnround(int *turnround_array, int process_count, int *arrival_array, int *completion_array){
  int i = 0;
  while(i < process_count){
    turnround_array[i] = completion_array[i] - arrival_array[i];
    i++;
  }
}

void calc_waiting(int *waiting_array, int process_count, int *burst_array, int *turnround_array){
  int i = 0;
  while(i < process_count){
    waiting_array[i] = turnround_array[i] - burst_array[i];
    i++;
  }
}

void calc_response(int *response_array, bool preemptive, int process_count, int *waiting_array, int *arrival_array, int *starting_array){
  int i = 0;
  if(preemptive == false){
    while(i < process_count){
      response_array[i] = waiting_array[i];
      i++;
    }
  }
  else{
    while(i < process_count){
      response_array[i] = starting_array[i] - arrival_array[i];
      i++;
    }
  }
}

bool done_checker(int process_count, bool *process_done){
  int count = 0;
  bool done = false;
  for(int k = 0; k < process_count; k++){
    if(process_done[k] == true)
      count++;
  }

  if(count == process_count)
    done = true;

  return done;
}

int idle_calc(int process_count, int *arrival_array, bool *process_done, int total_time){
  int min_arrival = 100000;
  for(int k = 0; k < process_count; k++){
    if(min_arrival > arrival_array[k] && process_done[k] == false)
      min_arrival = arrival_array[k];
  }

  if (min_arrival == 100000)
    return -1;
    
  int diff = min_arrival - total_time;
  total_time += diff;

  return total_time;
}

int min_value(int process_count, int *array, int *array2, bool *process_done, int total_time){
  int min_v = 100000;
  for(int i = 0; i < process_count; i++){
    if(min_v > array[i] && process_done[i] == false && array2[i] <= total_time)
      min_v = array[i];
  }
 
  return min_v;
}

int max_value(int process_count, int *array){
  int max_v = array[0];
  for(int i = 1; i < process_count; i++){
    if(max_v < array[i]){
      max_v = array[i];
    }
  }

  return max_v;
}

double avg_value(int process_count, int *array){
  double sum = 0;
  for(int i = 0; i < process_count; i++){
    sum += array[i];
  }

  sum /= process_count;

  return sum;
}
