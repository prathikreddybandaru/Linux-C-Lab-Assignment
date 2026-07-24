#!/bin/bash

# Route all standard error output to a dedicated log file
exec 2> script_errors.log

total_files_scanned=0
duplicate_count=0
saved_unique_count=0

mkdir -p unique_backups
declare -A content_tracker

for current_file in submissions/*; do
    if [[ -f "$current_file" ]]; then
        ((total_files_scanned++))
        
        file_checksum=$(sha256sum "$current_file" | awk '{print $1}')
        
        if [[ -n "${content_tracker[$file_checksum]}" ]]; then
            echo "Notice: Duplicate detected -> $current_file"
            ((duplicate_count++))
        else
            content_tracker[$file_checksum]=$current_file
            cp "$current_file" unique_backups/
            ((saved_unique_count++))
        fi
    fi
done

report_file="execution_summary.txt"
echo "--- Submission Processing Summary ---" > "$report_file"
echo "Total submissions scanned: $total_files_scanned" >> "$report_file"
echo "Total duplicates found: $duplicate_count" >> "$report_file"
echo "Total unique backups created: $saved_unique_count" >> "$report_file"

echo "Processing finished! Review $report_file and script_errors.log."
cat "$report_file"
