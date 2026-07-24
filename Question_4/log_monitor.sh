#!/bin/bash
echo "[System] Initializing background log generator..."
touch system.log

# 1. Simulate a live system generating logs in the background
(
    sleep 1; echo "[INFO] Service started successfully" 
    sleep 1; echo "[ERROR] Database timeout on port 5432" 
    sleep 1; echo "[WARNING] High CPU usage detected" 
    sleep 1; echo "[ERROR] Disk space critical on /var/log" 
    sleep 1; echo "[INFO] User authenticated"
) >> system.log &

echo "[System] Executing monitoring pipeline..."
echo "Command: tail -f system.log 2>/dev/null | grep --line-buffered \"ERROR\" | tee -a error_report.log"
echo "--- REAL-TIME ERROR LOGS ---"

# 2. The Command Pipeline
# Runs for 6 seconds so it auto-exits cleanly for your screenshot
timeout 6 tail -f system.log 2>/dev/null | grep --line-buffered "ERROR" | tee -a error_report.log

echo "----------------------------"
echo "[System] Monitoring complete. Report saved to error_report.log."
