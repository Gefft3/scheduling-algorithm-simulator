# **Explanation**


### Common Concepts

* **Process**: A program in execution, identified by `pid`.
* **Arrival Time** (`arrival`): When the process enters the ready queue.
* **Burst Time** (`burst`): Total CPU time the process needs.
* **Remaining Time** (`remaining`): How much CPU time is left (used in preemptive algorithms).
* **Priority** (`priority`): A number; smaller means more important (used in the Priority algorithm).
* **Clock** (`t`): A simple counter that moves forward in time steps.

Logs show what’s happening:

* **idle**: CPU has nothing to run.
* **start**: A process begins running (non-preemptive).
* **run**: A process runs for a time slice (preemptive).
* **preempt**: A running process is paused and sent back to the ready queue.
* **finish**: A process completes its CPU burst.

---

### 1. FCFS (First-Come, First-Served)

1. **Sort** all processes by arrival time.
2. Initialize clock `t = 0`.
3. For each process in order:

   * If `t < arrival`, log `idle` until `arrival`, then set `t = arrival`.
   * Log `start`, set `t += burst`, then log `finish`.
4. No interruptions—each process runs to completion.

---

### 2. SJF Non-Preemptive (Shortest Job First)

1. Keep track of which processes are done.
2. At each step:

   * From all arrived and not-yet-run processes, pick the one with the smallest `burst`.
   * If none have arrived, log `idle` and do `t++`.
   * Otherwise, log `start`, run it fully (`t += burst`), log `finish`, and mark it done.

---

### 3. SJF Preemptive (Shortest Remaining Time First)

1. At time `t = 0`, set each `remaining = burst`.
2. Repeat until all processes finish:

   * Among arrived processes with `remaining > 0`, pick the one with the smallest `remaining`.
   * If none available, log `idle`, `t++`.
   * Else, log `run`, do one unit (`remaining--`, `t++`).
   * If a process’s `remaining` hits zero, log `finish`.

---

### 4. Priority Scheduling (Non-Preemptive)

1. Similar to SJF NP, but choose by smallest `priority` instead of `burst`.
2. Among arrived, unused processes, pick lowest `priority`.
3. If none arrived, log `idle`, `t++`; else log `start`, run fully, log `finish`.

---

### 5. Round Robin

1. Set `remaining = burst` for each process.
2. Maintain a queue of ready process indices.
3. At each loop:

   * Enqueue any newly arrived processes.
   * If queue empty, log `idle`, `t++`.
   * Else, dequeue one, log `run`, let it run up to the quantum `q` or until it finishes:

     * `dt = min(q, remaining)`
     * `remaining -= dt`, `t += dt`
   * During that slice, enqueue any processes that arrive.
   * If `remaining > 0`, re-enqueue it and log `preempt`; else log `finish`.

Round Robin ensures each process gets fair time slices.
