#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int main() {
    printf("[Manager] Starting web server worker manager...\n");
    
    // Create a child process
    pid_t worker_pid = fork();
    
    if (worker_pid < 0) {
        perror("[Manager] Critical Error: Fork failed");
        exit(1);
    } 
    else if (worker_pid == 0) {
        // CHILD PROCESS
        printf("[Worker %d] Started processing web requests...\n", getpid());
        
        // Simulate a stuck/unresponsive process using an infinite loop
        while(1) {
            printf("[Worker %d] Processing (simulating heavy load)...\n", getpid());
            sleep(2);
        }
        exit(0); 
    } 
    else {
        // PARENT PROCESS
        int exit_status_code;
        
        printf("[Manager] Monitoring worker process %d for 5 seconds...\n", worker_pid);
        sleep(5); // Wait to see if child finishes gracefully
        
        printf("[Manager] Worker %d is unresponsive. Issuing SIGKILL...\n", worker_pid);
        
        // Terminate the unresponsive child process
        if (kill(worker_pid, SIGKILL) == 0) {
            printf("[Manager] Termination signal sent successfully.\n");
        } else {
            perror("[Manager] Failed to send termination signal");
        }
        
        // Reap the child to prevent a zombie process
        pid_t reaped_pid = waitpid(worker_pid, &exit_status_code, 0);
        
        if (reaped_pid == worker_pid) {
            printf("[Manager] Successfully reaped worker %d. Zombie prevented.\n", reaped_pid);
            if (WIFSIGNALED(exit_status_code)) {
                printf("[Manager] Verified: Worker terminated by signal %d.\n", WTERMSIG(exit_status_code));
            }
        }
        
        printf("[Manager] Server monitoring cycle complete.\n");
    }
    return 0;
}
