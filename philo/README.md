*This project has been created as part of the 42 curriculum by eskomo*

---
# Structure
	philo/
	├── Makefile
	├── Philo.h
	├── README.md
	└── src/
		├── main.c
		├── init.c
		├── thread.c
		├── checker.c
		├── monitoring.c
		├── threads_utilis.c
		└── utilis.c
	
---
# Description

This project is an introduction to the basics of threading and process management. It tackles the classic **Dining Philosophers Problem**, a well-known concurrency problem that demonstrate synchronization issues and techniques for resolving them.

---
## Dining Philosophers Problem

One or more philosophers sit at a round table, with a large bowl of spaghetti in the middle of the table.
There are as many philosophers as **forks** on the table. Between every two philosophers there is **one fork**.

The philosophers are taking turns: eating, sleeping, and thinking:
- While eating: they are not sleeping nor thinking.
- While sleeping: they are not eating nor thinking.
- While thinking: they are not eating nor sleeping.

To be able to eat, a philosopher must pick up both forks: the one on the right and the one on the left.
While a philosopher is eating and holding both forks, the **two philosophers next to him cannot eat** and must wait for their turn, because they also need two forks.
When a philosopher finished eating, he puts the forks back on the table and starts sleeping. After waking up, he starts thinking, and the cycle continues. The simulation ends when a philosopher starves (dies).

---
## The chalange:
- Philosophers must not starve (die of hunger).
- No two philosophers can hold the same fork simultaneously.
- There must be no **deadlocks** or **data races**.


---
### Deadlocks
Definition: a deadlock is a situation in computing where two or more processes (programs) are **stuck forever** because each is waiting for the other to release a resource.
It is a permanent **frozen** state where no progress can be made.

### Data races
Definition: a data race happens when two or more threads (separate worker in a program) try to access the same piece of data at the exact same time and trying to change/read it.

### Threads
Definition: a thread is a single "worker" or a "path of execution" inside a program. 
While a process is the entire container for a running program, threads are the smaller units inside that process that actually do the work.

### Mutex

Definition: a mutex (short for mutual exclusion) is a **"lock"** used to **prevent data races**. It makes sure that only one thread can access a specific piece of data or section of code at a time.

---
## Rules
- Each philosopher is a **thread**.
- Each fork is protected by a **mutex**.
- A philosopher loops between three states: **eating**, **sleeping**, and **thinking**.
- A philosopher dies if he haven't started eating within `time_to_die` milliseconds of their last meal (or the simulation starttime).
- The simulation stops as soon as **one philosopher dies** or **all philosophers have eaten** the required number of meals.
- Philosophers do not know if another philosopher is about to die.
- Philosophers do not comunicate with each other.
- State changes must be logged with a timestamp:
```bash
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
```
- Messages should not overlop with each other.
- Death message must be displayed within 10ms of the actual death.
- Each philosopher has a number ranging from 1 to number_of_philosophers. Philosopher number 1 sits next to philosopher number number_of_philosophers. Any other philosopher, numbered N, sits between philosopher N - 1 and philosopher N + 1.
- **No global variables**

---
## Command line arguments
```bash
./philo num_of_philos time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
|Argumant|Meaning|
|--------|-------|
|num_of_philos | The number of philosophers and also the number of forks|
|time_to_die | If a philosopher has not started eating within time_to_die milliseconds since the start of their last meal or the start of the simulation, they die.|
|time_to_eat | The time it takes for a philosopher to eat.|
|time_to_sleep | The time a philosopher will spend sleeping.|
|number_of_times_each_philosopher_must_eat (Optional) | If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops.|

All arguments must be positive integers.

---
# Instructions

## run
after clone:
```bash
	cd philo
	make
	./philo num_of_philos time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

```bash
# 5 philosophers, should never die
./philo 5 800 200 200
 
# 5 philosophers, each eats 7 times then simulation ends
./philo 5 800 200 200 7
 
# 4 philosophers, should never die
./philo 4 410 200 200
 
# 1 philosopher, will die (only one fork available)
./philo 1 800 200 200
 
# One philo should die, time_to_die too short
./philo 5 400 200 200
```

### Clean
```
	make clean	remove objects files
	make fclean	//remove objects and binary
	make re		//rebuild everything
```


