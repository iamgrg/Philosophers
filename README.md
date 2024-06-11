![Church 1871](https://github.com/iamgrg/Philosophers/assets/80717523/dae639d0-3fd0-49df-90a1-f9b1b544ac1c)
# Philosophers

## Overview

In the "Philosophers" project, we learned about threading processes, mutexes, and semaphore management. This project simulates the classic dining philosophers problem to explore process synchronization and avoid deadlock conditions while managing shared resources (forks).

## Objectives

- Understand threading and process synchronization.
- Learn how to use mutexes.
- Avoid deadlocks and manage resource allocation.

## Build Instructions

Compile the project using the provided Makefile:
```bash
make all
```

## Usage
Run the program specifying the number of philosophers, time to die, time to eat, time to sleep, and optionally, the number of times each philosopher must eat:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

## Example
```bash
./philo 5 800 200 200 7
```
This command starts a simulation with 5 philosophers where:

time_to_die is 800ms: A philosopher dies if they haven't started eating within 800ms since their last meal.
time_to_eat is 200ms: It takes 200ms for a philosopher to eat.
time_to_sleep is 200ms: A philosopher sleeps for 200ms.
number_of_times_each_philosopher_must_eated is 7: Simulation stops if all philosophers eat at least 7 times.

## Global Rules

Philosophers alternate between eating, thinking, and sleeping.
Each philosopher needs two forks to eat.
Philosophers must not talk to each other or know about the death of others.
The simulation ends if any philosopher dies.

## Mandatory Part

Philosophers are implemented as threads with forks represented as mutexes to manage access.

## Logs

Each state change of a philosopher is logged:

timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died

## Contributors

- @iamgrg

## License

![MIT License](https://img.shields.io/badge/license-MIT-green)
Distributed under the MIT License.
