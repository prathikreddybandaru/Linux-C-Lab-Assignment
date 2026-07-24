Question 4 Explanation:
To solve the requirement for a real-time log monitoring utility, I designed the following command pipeline:
tail -f system.log 2>/dev/null | grep --line-buffered "ERROR" | tee -a error_report.log
Here is how each component contributes to system efficiency:
tail -f: Reads the log file continuously in real-time, outputting new appended data immediately rather than requiring the file to be reopened.
2>/dev/null (Redirection to null): Acts as a black hole for standard error (file descriptor 2). It efficiently suppresses unnecessary output, such as permission warnings or file truncation errors, keeping the console clean.
| (Pipes): Efficiently passes the standard output of one command directly into the standard input of the next in RAM, avoiding the slow process of writing temporary intermediate files to the disk.
grep: Acts as the real-time filter, aggressively scanning the piped stream and allowing only lines containing "ERROR" to pass through.
tee -a (Redirection to file): Solves the dual-requirement of displaying output and saving it. It duplicates the stream, printing the error to the live console while simultaneously appending (-a) it to error_report.log.
