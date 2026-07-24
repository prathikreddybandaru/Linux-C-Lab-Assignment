#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

// Using a fixed-size struct allows us to calculate exact byte offsets
typedef struct {
    int emp_id;
    char name[32];
    double salary;
} Employee;

int main() {
    int fd;
    Employee emp;
    const char *db_file = "company_records.dat";

    printf("[System] Initializing Secure File Processing Utility...\n");

    // 1. Create the file and write initial records using O_CREAT and O_WRONLY
    fd = open(db_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) { perror("Error opening file"); exit(1); }

    Employee e1 = {1, "Alice Smith", 55000.0};
    Employee e2 = {2, "Bob Jones", 62000.0};
    Employee e3 = {3, "Charlie Brown", 71000.0};

    write(fd, &e1, sizeof(Employee));
    write(fd, &e2, sizeof(Employee));
    write(fd, &e3, sizeof(Employee));
    close(fd);
    
    printf("[+] Database created. 3 employee records securely written.\n");

    // 2. Update a specific record (Bob's salary) without rewriting the file
    // Open in Read/Write mode
    fd = open(db_file, O_RDWR);
    if (fd < 0) { perror("Error opening file for update"); exit(1); }

    int target_id = 2; // We want to update the 2nd record
    
    // Calculate exact byte location using sizeof()
    off_t record_offset = (target_id - 1) * sizeof(Employee);

    // Retrieve the record
    lseek(fd, record_offset, SEEK_SET);
    read(fd, &emp, sizeof(Employee));
    printf("[*] Retrieved Record -> ID: %d | Name: %s | Salary: $%.2f\n", emp.emp_id, emp.name, emp.salary);

    // Modify the data in memory
    emp.salary += 4500.0; 
    printf("[*] Processing raise for %s to $%.2f...\n", emp.name, emp.salary);

    // Seek back to the exact same offset to overwrite the old record
    lseek(fd, record_offset, SEEK_SET);
    write(fd, &emp, sizeof(Employee));
    printf("[+] Record successfully updated in-place via lseek().\n");

    // 3. Retrieve and print all records to verify
    printf("\n--- Final Database State ---\n");
    
    // Move pointer back to the very beginning of the file
    lseek(fd, 0, SEEK_SET);
    
    // Read sequentially until EOF
    while (read(fd, &emp, sizeof(Employee)) == sizeof(Employee)) {
        printf("ID: %d | Name: %-15s | Salary: $%.2f\n", emp.emp_id, emp.name, emp.salary);
    }

    close(fd);
    printf("[System] Operations complete. File descriptor safely closed.\n");
    return 0;
}
