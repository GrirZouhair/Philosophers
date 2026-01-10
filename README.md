# 🍝 Philosophers

A multithreading simulation of the classic **Dining Philosophers Problem** — part of the 42/1337 curriculum.

[![Language](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![42](https://img.shields.io/badge/School-42-black.svg)](https://42.fr)

## 📖 Description

The **Dining Philosophers Problem** is a classic synchronization problem in computer science. It illustrates challenges of resource allocation and deadlock prevention in concurrent programming.

This project teaches:
- Thread creation and management
- Mutex locks for resource protection
- Race condition prevention
- Deadlock avoidance strategies
- Time management in concurrent systems

## 🎭 The Problem

Five philosophers sit at a round table with a bowl of spaghetti. Between each pair of adjacent philosophers is a single fork (5 forks total). A philosopher needs **both** the left and right forks to eat.

```
           🧠 Philosopher 1
              🍴     🍴
     🧠 Philo 5         🧠 Philo 2
           🍴    🍝    🍴
     🧠 Philo 4         🧠 Philo 3
              🍴     🍴
```

Each philosopher alternates between three states:
1. **🍝 Eating** — needs both forks
2. **💭 Thinking** — doesn't need forks
3. **😴 Sleeping** — doesn't need forks

**The challenge**: Prevent deadlock (all philosophers grab one fork and wait forever) and starvation (a philosopher never gets to eat).

## 🔄 Lifecycle

```
┌─────────────────────────────────────────────────────────┐
│                                                         │
│    ┌──────────┐     ┌──────────┐     ┌──────────┐      │
│    │          │     │          │     │          │      │
└───►│ THINKING │────►│  EATING  │────►│ SLEEPING │──────┘
     │          │     │          │     │          │
     └──────────┘     └──────────┘     └──────────┘
           │               │                 │
           │          (has 2 forks)          │
           │                                 │
           └─────── DEATH if time_to_die ────┘
                    exceeded since last meal
```

## 📋 Arguments

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

| Argument | Description |
|----------|-------------|
| `number_of_philosophers` | Number of philosophers (and forks) |
| `time_to_die` (ms) | Time from start of last meal until death |
| `time_to_eat` (ms) | Time it takes to eat (holding 2 forks) |
| `time_to_sleep` (ms) | Time spent sleeping |
| `number_of_times_each_philosopher_must_eat` | (Optional) Simulation stops when all philosophers have eaten this many times |

## 📊 Output Format

Each state change is logged with a timestamp:

```
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
```

**Example output:**
```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
0 3 has taken a fork
0 3 has taken a fork
0 3 is eating
200 1 is sleeping
200 3 is sleeping
200 2 has taken a fork
...
```

## 🛠️ Installation

```bash
# Clone the repository
git clone https://github.com/GrirZouhair/Philosophers.git
cd Philosophers

# Compile
make

# Clean object files
make clean

# Full clean
make fclean

# Recompile
make re
```

## 🚀 Usage

### Basic Examples

```bash
# 5 philosophers, dies after 800ms, eats for 200ms, sleeps for 200ms
./philo 5 800 200 200

# Same but stops after each philosopher eats 7 times
./philo 5 800 200 200 7

# 4 philosophers - no one should die
./philo 4 410 200 200

# 1 philosopher - should die (can't grab 2 forks)
./philo 1 800 200 200
```

### Test Cases

```bash
# ✅ No one dies
./philo 5 800 200 200      # Should run indefinitely
./philo 4 410 200 200      # Should run indefinitely
./philo 2 800 200 200      # Should run indefinitely

# 💀 Philosopher dies
./philo 1 800 200 200      # Dies at ~800ms (only 1 fork)
./philo 4 310 200 100      # Dies (time_to_die too short)
./philo 5 300 100 100      # Dies quickly

# 🏁 Stops after eating N times
./philo 5 800 200 200 7    # Stops after 35 meals total
./philo 4 410 200 200 10   # Stops after 40 meals total
```

## 📁 Project Structure

```
Philosophers/
├── Makefile
├── MANDATORY/
│   └── ... (mandatory source files)
└── philo/
    ├── philo.h
    ├── main.c
    ├── init.c
    ├── parsing.c
    ├── routine.c
    ├── actions.c
    ├── monitor.c
    ├── time.c
    └── utils.c
```

## 🔧 Technical Implementation

### Data Structures

```c
typedef struct s_philo
{
    int             id;
    int             meals_eaten;
    long            last_meal_time;
    pthread_t       thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    struct s_data   *data;
}   t_philo;

typedef struct s_data
{
    int             num_philos;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             must_eat;
    int             dead;
    long            start_time;
    pthread_mutex_t *forks;
    pthread_mutex_t print_lock;
    pthread_mutex_t death_lock;
    t_philo         *philos;
}   t_data;
```

### Key Concepts

| Concept | Implementation |
|---------|----------------|
| **Threads** | One thread per philosopher using `pthread_create` |
| **Mutexes** | One mutex per fork + print lock + death lock |
| **Deadlock Prevention** | Odd philosophers pick left fork first, even pick right first |
| **Race Conditions** | All shared data access protected by mutexes |
| **Death Detection** | Monitor thread continuously checks `last_meal_time` |

### Deadlock Prevention Strategy

```c
// Even philosophers: pick right fork first
if (philo->id % 2 == 0)
{
    pthread_mutex_lock(philo->right_fork);
    pthread_mutex_lock(philo->left_fork);
}
// Odd philosophers: pick left fork first
else
{
    pthread_mutex_lock(philo->left_fork);
    pthread_mutex_lock(philo->right_fork);
}
```

## ⚠️ Common Issues

| Issue | Cause | Solution |
|-------|-------|----------|
| Data race | Unprotected shared variable | Add mutex locks |
| Deadlock | Circular wait for forks | Asymmetric fork picking |
| Philosopher dies unexpectedly | `usleep` drift | Use precise time checking |
| Delayed death message | Slow death detection | Reduce monitor sleep time |
| Memory leaks | Missing cleanup | Properly destroy mutexes and free memory |

## 🧪 Testing Tools

### Valgrind (Memory + Thread check)

```bash
valgrind --tool=helgrind ./philo 5 800 200 200
valgrind --leak-check=full ./philo 5 800 200 200 7
```

### Thread Sanitizer

```bash
# Compile with sanitizer
gcc -fsanitize=thread -g *.c -lpthread -o philo_test
./philo_test 5 800 200 200
```

### Philosophers Tester

```bash
# External testers available online
# Check timing accuracy and death detection
```

## 📚 Allowed Functions

| Function | Description |
|----------|-------------|
| `pthread_create` | Create a new thread |
| `pthread_join` | Wait for thread termination |
| `pthread_mutex_init` | Initialize a mutex |
| `pthread_mutex_destroy` | Destroy a mutex |
| `pthread_mutex_lock` | Lock a mutex |
| `pthread_mutex_unlock` | Unlock a mutex |
| `usleep` | Suspend execution (microseconds) |
| `gettimeofday` | Get current time |
| `malloc` / `free` | Memory allocation |
| `printf` / `write` | Output |

## 📖 The Original Problem

The Dining Philosophers Problem was formulated by **Edsger Dijkstra** in 1965 to illustrate synchronization issues and techniques for resolving them in concurrent programming.

## 👤 Author

**Zouhair Grir**
- GitHub: [@GrirZouhair](https://github.com/GrirZouhair)
- 42 Intra: zogrir

## 📄 License

This project is part of the 42 school curriculum.

---

*Made with ❤️ at 42/1337*
