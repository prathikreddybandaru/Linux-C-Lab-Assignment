Question 5 Explanation:
To address the scenario of a system crash while editing a critical configuration file, I evaluated vi's recovery mechanisms.
Undo history and registers are immediately disqualified as they are stored in volatile RAM and do not survive a system crash.
Backup files are insufficient because they only represent the file state prior to the editing session, meaning all new configurations would be lost.
The most reliable strategy is Swap File Recovery (vi -r <filename>).
