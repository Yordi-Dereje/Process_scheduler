#include <iostream>
#include "header.h"

using namespace std;

int input_scheduler_choice(){
  int choice;
  cout << "Choose process scheduling algorithm..." << endl;
  cout << "\t1. First come first serve(FCFS)" << endl;
  cout << "\t2. Shortest job first(SJF)" << endl;
  cout << "\t3. Shortest remaining time first(SRTF)" << endl;
  cout << "\t4. Round robin(RR)" << endl;
  cout << "\t5. Preemptive Priority scheduling(PS)" << endl;
  cout << "\t6. Nonpreemptive Priority scheduling(PS)" << endl;
  do{
    cout << "Choice: ";
    cin >> choice;
    if(choice < 1 || choice > 6){
      cout << "Invalid choice. Please enter value from shown list..." << endl;
    }
  }while(choice < 1 || choice > 6);

  return choice;
}

int input_process_count(){
int count;
cout << "Enter your number of processes: ";
  cin >> count;

  return count;
}

void arrival_input(int process_count, int *arrival_array){
  cout << "Enter arrival time for corresponding process" << endl;
  int counter = 0;
  while(counter < process_count)
  {
    cout << "P" << counter << ": ";
    cin >> arrival_array[counter];
    counter++;
  }
}

void burst_input(int process_count, int *burst_array){
  cout << "Enter burst time for corresponding process" << endl;
  int counter = 0;
  while(counter < process_count)
  {
    cout << "P" << counter << ": ";
    cin >> burst_array[counter];
    counter++;
  }

}

void priority_input(int process_count, int *priority_array){
  cout << "Enter priority for corresponding process" << endl;
  int counter = 0;
  while(counter < process_count)
  {
    cout << "P" << counter << ": ";
    cin >> priority_array[counter];
    counter++;
  }

}

int quantum_input(){
  int quan;
  cout << "Enter quantum number: ";
  cin >> quan;

  return quan;
}

