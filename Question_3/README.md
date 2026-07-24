Question 3 Explanation:
To implement the secure file-processing utility, I designed a C program utilizing a fixed-size Employee struct combined with low-level POSIX system calls.
Here is how the system calls contribute to the solution
open(): Used with specific flags (like O_CREAT and O_WRONLY for initialization, and O_RDWR for updating) to request direct file access from the OS kernel, bypassing standard buffered I/O libraries.
write(): Takes the raw binary memory footprint of our C struct and writes it directly to the disk at the current file pointer location
lseek(): This is the core of the in-place update logic. By calculating the exact byte offset of a target record (index * sizeof(Employee)), lseek() repositions the read/write head. This allows the program to jump directly to any record instantly without parsing or rewriting the entire file.
read(): Extracts the exact byte-length of the struct from the location specified by lseek(), bringing the disk data back into active memory for modification.
close(): Safely releases the file descriptor back to the operating system and flushes any remaining kernel buffers to ensure data integrity.
