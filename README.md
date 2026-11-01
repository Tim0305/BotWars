# BotWars

A C++17 program that reads access logs, sorts them, searches by date or IP,
and shows reports about the IPs with the most accesses.

## Build and run

You need a C++17 compiler and make. From the project folder, run:

```sh
make
./bin/main
```

If you change a header file, run `make clean` and then `make` to build again.

## Input file

Enter the filename when the program starts, or press Enter to use `bitacora.txt`.
Each line must follow this format:

```text
Month Day HH:MM:SS IP:Port Domain Message
Sep 10 08:29:25 203.0.113.143:6747 vpn.nube-sur.example Failed password for root
```

Use English month abbreviations such as `Jan`, `Feb` and `Sep`.
Dates do not include a year, and February has 28 days.
Each number in an IP address must have one to three digits and be between 0 and 255.
Do not include blank lines. If the file cannot be loaded, the program shows an error and exits.

## Menu

- **1. Sort bitacora:** Sort by date or IP, then choose whether to save the result.
  The default output filename is `bitacora_ordenada.txt`.
- **2. Search by date:** Enter a start and end date. Results are shown and saved
  in `filtered_logs_date.txt`.
- **3. Search by IP:** Enter a start and end IP. Results are shown and saved
  in `filtered_logs_ip.txt`.
- **4. Monitor:** Count accesses by IP and show the reports described below.
- **5. Monitor Test:** Choose ascending, descending or shuffled order and enter
  the number of records to insert. Shows the time taken and the tree height.
- **0. Exit:** Close the program.

Searches include both ends of the range. The logs do not need to be sorted for
these searches. A start value greater than the end value gives no results.
Saving a file replaces its previous contents, even when there are no results.

## Monitor

Use a file with at least one log, sorted by date. You can load
`bitacora_ordenada_date.txt`, or sort by date with option 1 before using the monitor.

At the end of each month, the monitor shows the number of different IPs,
the average accesses per IP and the top 5 IPs. These reports include all accesses
read so far, including earlier months. The counts are not reset between months.

After reading all logs, it shows the top 15 IPs with their total accesses,
successful accesses and success percentage. An access is successful when its
message starts with the word `Accepted`. IPs with equal access counts are listed
in ascending IP order.

The monitor also asks for an IP range. Finally, it searches the block of the most
accessed IP. This block keeps the first three numbers and uses 0 to 255 for the
last number. For example, `192.168.1.5` gives the range `192.168.1.0` to
`192.168.1.255`. The method is named `queryMostAccessedIpBlock()`.

Reports are shown on screen and saved in `output.txt`, replacing its previous contents.

## Monitor Test

Enter a record count of zero or greater. The time is shown in microseconds.
For ascending and descending order, the measured time includes creating the
records. For shuffled order, creating and shuffling them happens before timing.

## Notes

- Comparisons between logs use the selected date or IP field, not the whole log.
- The IP constructor that receives four numbers does not check their values.
- The date and port readers do not check every detail of the text format.
- Enter valid menu choices and record counts; the program does not handle all input mistakes.
