# Railway Reservation System (C++)

A menu-driven mini project for the Data Structures assignment. It demonstrates arrays, pointers, dynamic memory allocation, and a singly linked list.

## Features

- Book a ticket and assign the first available seat
- Cancel a ticket using its seat number
- View the status of all 30 seats
- View passenger records
- Release allocated memory on exit
- Passenger names are stored using `std::string`

## Data structures and memory

- **Dynamic array:** `malloc()` allocates space for 30 seat-status integers. `0` means Available and `1` means Booked. The array is released with `free()`.
- **Singly linked list:** Each passenger is a node containing seat number, name, age, gender, and a pointer to the next node. Nodes are created with `new` and released with `delete`. This is important because `std::string` needs its constructor and destructor to run correctly.

## Compile and run

### Using g++

```bash
g++ main.cpp -o railway
./railway
```

On Windows:

```bash
g++ main.cpp -o railway.exe
railway.exe
```

## Menu

1. Book Ticket
2. Cancel Ticket
3. View Train Status
4. View Passenger List
5. Exit

## Testing checklist

- Book multiple tickets and check the seat numbers
- View train status after booking
- View passenger list after booking
- Cancel a booked seat and confirm it becomes Available
- Try cancelling an already available seat
- Try booking until all 30 seats are full
- Exit and confirm the program reports that memory was released

## Assignment

Mini Project – Railway Reservation System  
Subject: Data Structures (Arrays, Pointers, Dynamic Memory, Linked List)
