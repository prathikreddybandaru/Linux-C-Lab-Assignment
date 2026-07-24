Question 2 Explanation:
To solve the unresponsive web server issue, I implemented a custom C program utilizing a parent-manager and child-worker architecture.
Process Creation: The parent process uses fork() to generate a child (worker_pid). The child simulates an unresponsive web server process by entering an infinite loop of work requests.
Signal Handling: The parent monitors the child for a designated period (5 seconds). Upon realizing the child is unresponsive, the parent utilizes the kill() system call to send a precise SIGKILL signal, forcefully terminating the stuck process.
Zombie Prevention (Waiting): Finally, I utilized waitpid() to explicitly wait for the terminated child's state change. This is crucial because it allows the operating system to release the child's process control block (PCB), ensuring the terminated process doesn't linger as a resource-draining "zombie."
