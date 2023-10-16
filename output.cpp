#include <iostream>
#include "header.h"

using namespace std;

void output(int process_count, int *arrival_array, int *burst_array, int *completion_array, int *turnround_array, int *waiting_array, int *response_array){
  cout << "PID\t\tAT\tBT\tCT\tTRT\tWT\tRT" << endl;
  int counter = 0;
  while(counter < process_count){
    cout << "P" << counter << "\t\t" << arrival_array[counter] << "\t" << burst_array[counter] << "\t" << completion_array[counter];
    cout << "\t" << turnround_array[counter] << "\t" << waiting_array[counter] << "\t" << response_array[counter] << endl;
    counter++;
  }

  cout << endl;
  cout << "* Average turnround time: " << avg_value(process_count, turnround_array) << endl;
  cout << "* Average waiting time: " << avg_value(process_count, waiting_array) << endl;
  cout << "* Average response time: " << avg_value(process_count, response_array) << endl;
  cout << "* Total completion time: " << max_value(process_count, completion_array) << endl;
}

void output_p(int process_count, int *priority_array, int *arrival_array, int *burst_array, int *completion_array, int *turnround_array, int *waiting_array, int *response_array){
  cout << "PID\t\tPT\tAT\tBT\tCT\tTRT\tWT\tRT" << endl;
  int counter = 0;
  while(counter < process_count){
    cout << "P" << counter << "\t\t" << priority_array[counter] << "\t" << arrival_array[counter] << "\t" << burst_array[counter] << "\t" << completion_array[counter];
    cout << "\t" << turnround_array[counter] << "\t" << waiting_array[counter] << "\t" << response_array[counter] << endl;
    counter++;
  }
  
  cout << endl;
  cout << "* Average turnround time: " << avg_value(process_count, turnround_array) << endl;
  cout << "* Average waiting time: " << avg_value(process_count, waiting_array) << endl;
  cout << "* Average response time: " << avg_value(process_count, response_array) << endl;
  cout << "* Total completion time: " << max_value(process_count, completion_array) << endl;
}


