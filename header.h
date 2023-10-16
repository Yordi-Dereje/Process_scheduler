#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

using namespace std;
#include <string>

/** 
 * struct readyQueue - queue
 * @at: arrival time
 * @bt: burst time
 */
struct readyQueue{
  int at, bt;
  readyQueue *next;
}*fr = NULL, *re = NULL;

//primary inputs
int input_scheduler_choice();
int input_process_count();

//input times
void arrival_input(int process_count, int *arrival_array);
void burst_input(int process_count, int *burst_array);
void priority_input(int process_count, int *priority_array);
int quantum_input();

//schedulers
void fcfs(int process_count, int *arrival_array, int *burst_array, int *completion_array);
void sjf(int process_count, int *arrival_array, int *burst_array, int *completion_array);
void srtf(int process_count, int *arrival_array, int *burst_array, int *completion_array, int *starting_array);
void rr(int process_count, int quantum_number, int *arrival_array, int *burst_array, int *completion_array, int *starting_array);
void nps(int process_count, int *arrival_array, int *burst_array, int *priority_array, int *completion_array);
void pps(int process_count, int *arrival_array, int *burst_array, int *priority_array, int *completion_array, int *starting_array);

//final output
void output(int process_count, int *arrival_array, int *burst_array, int *completion_array, int *turnround_array, int *waiting_array, int *response_array);
void output_p(int process_count, int *priority_array, int *arrival_array, int *burst_array, int *completion_array, int *turnround_array, int *waiting_array, int *response_array);

//calculating times
void calc_turnround(int *turnround_array, int process_count, int *arrival_array, int *completion_array);
void calc_waiting(int *waiting_array, int process_count, int *burst_array, int *turnround_array);
void calc_response(int *response_array, bool preemptive, int process_count, int *waiting_array, int *arrival_array, int *starting_array);

//extras
bool done_checker(int process_count, bool *process_done);
int idle_calc(int process_count, int *arrival_array, bool *process_done, int total_time);
int min_value(int process_count, int *array, int *array2, bool *process_done, int total_time);
int max_value(int process_count, int *array);
double avg_value(int process_count, int *array);

#endif // HEADER_H_INCLUDED
