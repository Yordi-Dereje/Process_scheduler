#include <iostream>
#include "header.h"
#include "input.cpp"
#include "schedulers.cpp"
#include "utils.cpp"
#include "output.cpp"

using namespace std;

int main(){
  bool preemptive = false;
  int schedule_choice = input_scheduler_choice(), process_count = input_process_count(), quantum_number;
  int arrival_array[process_count], burst_array[process_count], priority_array[process_count];
  int completion_array[process_count], starting_array[process_count];
  int turnround_array[process_count], waiting_array[process_count], response_array[process_count];

  if(schedule_choice == 1){
    arrival_input(process_count, arrival_array);
    burst_input(process_count, burst_array);
    cout << endl << "\tProcess scheduling using First Come First Serve (FCFS)" << endl;
    fcfs(process_count, arrival_array, burst_array, completion_array);
  }

  else if(schedule_choice == 2){
    arrival_input(process_count, arrival_array);
    burst_input(process_count, burst_array);
    cout << endl << "\tProcess scheduling using Shortest Job First (SJF)" << endl;
    sjf(process_count, arrival_array, burst_array, completion_array);
  }

  else if(schedule_choice == 3){
    preemptive = true;
    arrival_input(process_count, arrival_array);
    burst_input(process_count, burst_array);
    cout << endl << "\tProcess scheduling using Shortest Remaining Time First (SRTF)" << endl;
    srtf(process_count, arrival_array, burst_array, completion_array, starting_array);
  }

  else if(schedule_choice == 4){
    preemptive = true;
    arrival_input(process_count, arrival_array);
    burst_input(process_count, burst_array);
    quantum_number = quantum_input();
    cout << endl << "\tProcess scheduling using Round Robin (RR)" << endl;
    rr(process_count, quantum_number, arrival_array, burst_array, completion_array, starting_array);
  }

  else if(schedule_choice == 5){
    preemptive = true;
    priority_input(process_count, priority_array);  
    arrival_input(process_count, arrival_array);
    burst_input(process_count, burst_array);
    cout << endl << "\tProcess scheduling using Preemptive Priority scheduling (PPS)" << endl;
    pps(process_count, arrival_array, burst_array, priority_array, completion_array, starting_array);
  }

  else if(schedule_choice == 6){
    priority_input(process_count, priority_array);  
    arrival_input(process_count, arrival_array);
    burst_input(process_count, burst_array);
    cout << endl << "\tProcess scheduling using Non preemptive Priority scheduling (NPS)" << endl;
    nps(process_count, arrival_array, burst_array, priority_array, completion_array);
}

  
 //calculations
  calc_turnround(turnround_array, process_count, arrival_array, completion_array);
  calc_waiting(waiting_array, process_count, burst_array, turnround_array);
  calc_response(response_array, preemptive, process_count, waiting_array, arrival_array, starting_array);

  if(schedule_choice <= 4)
    output(process_count, arrival_array, burst_array, completion_array, turnround_array, waiting_array, response_array);
  else
    output_p(process_count, priority_array, arrival_array, burst_array, completion_array, turnround_array, waiting_array, response_array);

  
  return 0;
}

