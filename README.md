# Process Scheduling Simulator

## Overview
A C++ simulator for four classic CPU scheduling algorithms:

- **FCFS** (First-Come, First-Served)
- **SJF** (Shortest Job First) – preemptive and non-preemptive
- **Priority** (non-preemptive)
- **Round Robin**

## Project Structure

- `main.cpp`: Core implementation using a `Process` class and individual scheduling functions.
- `Process` class fields:
  - `pid`       : unique process identifier
  - `arrival`   : arrival time in time units
  - `burst`     : total CPU time required
  - `remaining` : remaining CPU time (for preemptive modes)
  - `priority`  : scheduling priority (lower value = higher priority)

## Building

```bash
    make
```

or

```bash
    g++ -std=c++11 -O2 main.cpp -o scheduler
```

## Usage

```bash
    ./scheduler
```

Interactive prompts:

1. Select algorithm (1-5).
2. Enter number of processes.
3. For each process, input `arrival` and `burst`.
4. If Priority algorithm, input `priority`.
5. If Round Robin algorithm, input time `quantum`.

## Example Session

```
Select algorithm:
1.FCFS 
2.SJF NP 
3.SJF P 
4.Priority 
5.RR
>5
Number of processes:
>3
Process 1 arrival burst: 0 5
Process 2 arrival burst: 2 3
Process 3 arrival burst: 4 1
Quantum:
>2
... (simulation logs)
```

## Log States

* `idle`     : CPU idle
* `start`    : process start (non-preemptive)
* `run`      : execution slice (preemptive)
* `preempt`  : process preempted
* `finish`   : process completion

## License

MIT

