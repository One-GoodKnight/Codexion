*This project has been created as part of the 42 curriculum by [aginiaux](https://github.com/One-GoodKnight).*

# Description

This project consists of creating a system to make multiple coders share a quantum compiler  
on different thread without corrupting the data of the system.  
  
There is as usb dongle between each coder and a coder needs 2 to compile it's program  
on the quantum compiler.  
After compiling, the coder puts back the dongles and starts debugging and refactoring.  
Other coders can pickup the dongles after Xms (set by a parameter to send to the program).  
  
The program either results in the burnout of a coder because of lack of compiling,  
or every coder compiled to code enough times for the simulation to end.  

The goal is to create a system robust enough to run simulations without deadlocks, dataraces  
and that is able to print coherent messages give the parameters given.  

# Instructions
  
## Compilation
```bash
make
make clean
make fclean
make re
```
  
## Execution
```bash
./codexion x x x x x x x x
- number_of_coders
- time_to_burnout
- time_to_compile
- time_to_debug
- time_to_refactor
- number_of_compiles_required
- dongle_cooldown
- scheduler (fifo or edf)
```
  
```bash
./codexion 3 1000 100 100 100 3 50 fifo
```

# Resources
  
Peers
[CodeVault's serie on threads](https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)  
[Binary / Fibo heaps](https://www.youtube.com/watch?v=6JxvKfSV9Ns)  
Man pages  
  
AI was used to explain concepts about threads and help debugging some deadlocks.  

# Blocking cases handled
  
## Deadlocks / Coffman's conditions
To prevent deadlocks, each coder with an even id first tries to take the dongle  
to it's left, and then to their right. Opposite for coders with an odd id.  
This prevents the situation where every coder holds a dongle in their left  
hand for example and waits for the right one to be available.  

A condition is used to make threads wait for the dongle they are trying to get  
This conditions unlocks the mutex so that the monitor can make a broadcast  
and let the coder check if he's the owner of the dongle.  

Edges cases like 0 coder, 0 compiles required are hardcoded.  
Same for the 1 coder situation since a coder can't compute with a single dongle.  
  
## Starvation prevention
A queue has been implemented to prioritize coders either using the time they  
asked the dongle, or their burnout time.  
FIFO - First In First Out  
EDF - Earliest Deadline First  
  
![Min Heap](https://media.geeksforgeeks.org/wp-content/uploads/20201106115157/MinHeap.jpg)
The queue is implemented as a binary tree min heap, it handles insertion and  
extraction while keeping it ordered (even tho there are only 2 coders max  
per queue in this context).  
  
A tie breaker rule is implemented in case the value used to compare is equal  
for the two coders. The id of the coders are use as the tie breaker.  
  
## Cooldown handling
After completing a compilation, the coder releases the dongles by setting  
their owner ids to -1 and also sets the time at when the dongle will  
be available (current time + cooldown delay).  
  
The monitor script checks if their is no owner and if the current time  
is over the time set at the end of the compilation by the previous coder.  

## Burnout detection
An important part of the project is to detect a burnout in less than 10ms.
A bool is used in the main struct (codexion) of the project and every  
thread checks it at critical sections.  
A custom sleep has been implemented to avoid over sleeping, which happens  
either:  
with usleep sleeping too much - avoided by doing small usleep calls and  
checking the current time stop if we slept enough).
sleeping too long without checking the bool that tells us the simulation  
is over - avoided by stoping the sleep if the bool end is true.  
  
## Log serialization
``A mutex is used to prevent two threads from writing at the same time and  
cutting eachother message.  

## Burnout log order
The print for the burnout message is called in the main thread once all  
threads have been joined. This assures it appear after every other  
message of other threads.  

# Thread synchronization mechanisms
  
Mutexes used to avoid race conditions:
- comp_start_or_count_lock
- print_lock
- end_lock
- owner_id_lock
- when_available_lock
- lock (for the queue)

mutexes are used when a value can be {read / write to} from multiple threads  
to avoid race conditions.
An example is comp_start_or_count_lock. If a coder increments  
compilation_count and the monitor reads it at the same time, it's an  
undefined behavior and the program might not act as intended.
So both the coder and the monitor lock the mutex, read / write to the value  
and unlock the mutex.
  
As little code as possible should be between a lock and an unlock to avoid  
unnecessary deadlocks.
  
Condition used to make a coder check if he's the owner of the dongle:
- owner_cond

When a coder requests a dongle, the request is inserted in the queue,  
then it locks the mutex owner_id_lock and starts the condition owner_cond  
in a while loop, this unlocks the mutex until the monitors broadcasts on it.  
  
The monitor checks every dongle and if there is no owner (owner id to -1)  
and the current time is over the when_available time of the dongle (for cd).  
If the dongle is available, it pulls a coder from the queue, if it succeeds,
the id of the owner inside the dongle is set the the monitor broadcasts.

The coder gets out of the condition and checks the while condition, if he is  
the one who has the dongle, it continues. Else it waits for the next broadcast.
This is useful because the broadcast can be made to either 1 or 2 coders since  
up to two coders can be stuck on the same condition of a dongle.  

After compilation, the coders set the vars of the dongle owner_id back to -1  
and when_available to it's appropriate value.
