#include <iostream>
#include "header.h"

using namespace std;

//first come first serve: non preemptive and arrival time based
void fcfs(int process_count, int *arrival_array, int *burst_array, int *completion_array){

  bool process_done[process_count];
  for(int i = 0; i < process_count; i++){
    process_done[i] = false;
  }

  int total_time = 0;
  for(int i = 0; i < process_count; i++){
    bool found = false;
    for(int j = 0; j < process_count; j++){
      int min_arr = min_value(process_count, arrival_array, arrival_array, process_done, total_time);

      if(arrival_array[j] <= total_time && arrival_array[j] == min_arr){
        total_time += burst_array[j];
        completion_array[j] = total_time;
        process_done[j] = true;
        found = true;
      }
    }
    bool done = done_checker(process_count, process_done); 

    if(!found && !done){ 
      total_time = idle_calc(process_count, arrival_array, process_done, total_time);
      if(total_time == -1)
        continue;
      i--;
    }
  }
}


//shortest job first: non preemptive and burst time based
void sjf(int process_count, int *arrival_array, int *burst_array, int *completion_array){

  bool process_done[process_count];
  for(int i = 0; i < process_count; i++){
    process_done[i] = false;
  }

  int total_time = 0;
  int min_arr = min_value(process_count, arrival_array, arrival_array, process_done, total_time);
  if(min_arr != 0){
    min_arr = idle_calc(process_count, arrival_array, process_done, total_time);
    total_time += min_arr;
    
  }
  for(int i = 0; i < process_count; i++){
    bool found = false;
    for(int j = 0; j < process_count; j++){

      int min_burst = min_value(process_count, burst_array, arrival_array, process_done, total_time); 
      if(arrival_array[j] <= total_time && burst_array[j] == min_burst){
        total_time += burst_array[j];
        completion_array[j] = total_time;
        process_done[j] = true;
        found = true;
      }
    }
    bool done = done_checker(process_count, process_done); 

    if(!found && !done){ 
      total_time = idle_calc(process_count, arrival_array, process_done, total_time);
      if(total_time == -1)
        continue;
      i--;
    }
  }
}

//shortest remaining time first aka preemptive shortest job first
//preemptive and burst time based
void srtf(int process_count, int *arrival_array, int *burst_array, int *completion_array, int *starting_array){
 
  bool process_done[process_count], process_started[process_count];
  int temp_burst[process_count];
  for(int i = 0; i < process_count; i++){
    process_done[i] = false;
    process_started[i] = false;
    temp_burst[i] = burst_array[i]; 
  }
  
  int total_time = 0;
  for(int i = 0; i < process_count; i++){
    bool found = false;
    for(int j = 0; j < process_count; j++){

      int min_burst = min_value(process_count, temp_burst, arrival_array, process_done, total_time); //fetching process with the smallest burst time
      if(arrival_array[j] <= total_time && process_done[j] == false && temp_burst[j] == min_burst){        
        if(process_started[j] == false){
          starting_array[j] = total_time;
          process_started[j] = true;
        }
        
        total_time += 1;
        temp_burst[j] -= 1;
        
        if(temp_burst[j] == 0){
          process_done[j] = true;
          completion_array[j] = total_time;
        }

        found = true;
        j = -1;
      } 
    }
    bool done = done_checker(process_count, process_done); 

    if(!found && !done){ 
      total_time = idle_calc(process_count, arrival_array, process_done, total_time);
      if(total_time == -1)
        continue;
      i--;
    }
  }
}

//round robin: preemptive and burst time based which requires quantum time
void rr(int process_count, int quantum_number, int *arrival_array, int *burst_array, int *completion_array, int *starting_array){
  
  bool process_done[process_count], process_started[process_count],inQueue[process_count], done = false;
  int temp_burst[process_count];
  for(int i = 0; i < process_count; i++){
    process_done[i] = false;
    process_started[i] = false;
    temp_burst[i] = burst_array[i];
    inQueue[i] = false;
  }

  int total_time = 0;
  int min_arr = min_value(process_count, arrival_array, arrival_array, process_done, total_time);
  if(min_arr != 0){
    min_arr = idle_calc(process_count, arrival_array, process_done, total_time);
    total_time += min_arr;
  }

  for(int j = 0; j < process_count; j++){
      if(arrival_array[j] == total_time){
        inQueue[j] = true;
        readyQueue *r = new readyQueue();
        r->at = arrival_array[j];
        r->bt = burst_array[j];
        r->next = NULL;

        if(!fr)
          fr = re = r;
        else{
          re->next = r;
          re = r;
        } 
      }
  }
 
  while(done == false){
  readyQueue *x = fr;
  if(fr){ 
    int array_val;
    for(int i = 0; i < process_count; i++){
      if(arrival_array[i] == fr->at && burst_array[i] == fr->bt)
        array_val = i;
    }
    if(process_started[array_val] == false){
      starting_array[array_val] = total_time;
      process_started[array_val] = true;
    }
    int old_total = total_time;
    if(process_done[array_val] == false && temp_burst[array_val] >= quantum_number){
      total_time += quantum_number;
      temp_burst[array_val] -= quantum_number;
    }
    else if(process_done[array_val] == false && temp_burst[array_val] < quantum_number){
      total_time += temp_burst[array_val];
      temp_burst[array_val] = 0;
    }
    if(temp_burst[array_val] == 0){
      process_done[array_val] = true;
      completion_array[array_val] = total_time;
    }
    
    for(int i = old_total; i <= total_time; i++){
      for(int j = 0; j < process_count; j++){
        if(arrival_array[j] == i && inQueue[j] == false){
          inQueue[j] = true;
          readyQueue *r = new readyQueue();
          r->at = arrival_array[j];
          r->bt = burst_array[j];
          r->next = NULL;

          if(!fr)
            fr = re = r;
          else{
            re->next = r;
            re = r;
          }
        }
      }
    }

    if(process_done[array_val] == false){
      inQueue[array_val] = true;
      readyQueue *r = new readyQueue();
      r->at = arrival_array[array_val];
      r->bt = burst_array[array_val];
      r->next = NULL;

      if(!fr)
        fr = re = r;
      else{
        re->next = r;
        re = r;
      }
    }

    fr = fr->next;
    delete x;
  }
  else
    done = true;
  }
}

//non preemptive priority scheduler
void nps(int process_count, int *arrival_array, int *burst_array, int *priority_array, int *completion_array){
  
  bool process_done[process_count];
  for(int i = 0; i < process_count; i++){
    process_done[i] = false;
  }

  int total_time = 0;
  for(int i = 0; i < process_count; i++){
    bool found = false;
    for(int j = 0; j < process_count; j++){
      int high_pr = min_value(process_count, priority_array, arrival_array, process_done, total_time); //finding process with highest priority

      if(arrival_array[j] <= total_time && process_done[j] == false && priority_array[j] == high_pr){
        total_time += burst_array[j];
        completion_array[j] = total_time;
        process_done[j] = true;
        found = true;
      }        }
    bool done = done_checker(process_count, process_done);

    if(!found && !done){ 
      total_time = idle_calc(process_count, arrival_array, process_done, total_time);
      if(total_time == -1)
        continue;
      i--;
    }
  }
}


//preemptive priority scheduler
void pps(int process_count, int *arrival_array, int *burst_array, int *priority_array, int *completion_array, int *starting_array){

  bool process_done[process_count], process_started[process_count];
  int temp_burst[process_count];
  for(int i = 0; i < process_count; i++){
    process_done[i] = false;
    process_started[i] = false;
    temp_burst[i] = burst_array[i]; 
  }

  int total_time = 0;
  for(int i = 0; i < process_count; i++){
    bool found = false;
    for(int j = 0; j < process_count; j++){
      int high_pr = min_value(process_count, priority_array, arrival_array, process_done, total_time); 
      
      if(arrival_array[j] <= total_time && process_done[j] == false && priority_array[j] == high_pr){        
        if(process_started[j] == false){
          starting_array[j] = total_time;
          process_started[j] = true;
        }
        
        total_time += 1;
        temp_burst[j] -= 1;
        
        if(temp_burst[j] == 0){
          process_done[j] = true;
          completion_array[j] = total_time;
        }

        found = true;
        j = -1;
      } 
    }
    bool done = done_checker(process_count, process_done); 

    if(!found && !done){ 
      total_time = idle_calc(process_count, arrival_array, process_done, total_time);
      if(total_time == -1)
        continue;
      i--;
    }
  }
}
