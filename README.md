# Message-Passing-Threads-C--lpthread-Programming
The purpose of this assignment is to gain some familiarity with using pthreads, and to implement a message 
passing mechanism between threads. You should create a process with two threads - one thread will be the sender
and the other thread will be the receiver. The message should consist of a character string, passed as a pointer
to the receiving thread. This string should be input via the sending thread, placed in a buffer that is accessible
to both threads, and then retrieved by the receiving thread and printed. The sending and receiving processes should
protect the buffer operations with semaphores, to provide the necessary synchronization to avoid any race conditions.
