# 42_philosophers
### Multi Threading &amp;&amp; Concurrency in C

In this project, philosophers are seated around a round table with a bowl of spaghetti at its center. They engage in a cyclical routine of eating, thinking, and sleeping. While eating, they use both the left and right forks to handle the spaghetti efficiently. After finishing their meal, they return the forks to the table and sleep, followed by thinking once they wake up. The simulation continues until a philosopher starved to death. The primary goal is to prevent philosophers from dying during the simulation.

- The program(s) accepts the following command-line arguments:
    - `number_of_philosophers`: The number of philosophers and forks.
    - `time_to_die` (in milliseconds): If a philosopher hasn't started eating within this time since their last meal or the simulation's beginning, they die.
    - `time_to_eat` (in milliseconds): The time a philosopher takes to eat, during which they need to hold two forks.
    - `time_to_sleep` (in milliseconds): The time a philosopher spends sleeping.
    - `[number_of_times_each_philosopher_must_eat]` (optional): If specified, the simulation stops when all philosophers have eaten at least this many times; otherwise, it stops when a philosopher dies.
  
```
git clone https://github.com/Kingsolomon445/42_philosophers
make all
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```

