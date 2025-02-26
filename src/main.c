#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_LINE_LENGTH 1024

void extract_logs(const char *log_file, const char *date)
{
    FILE *infile = fopen(log_file, "r");
    if (!infile)
    {
        perror("Error opening log file");
        return;
    }

    char output_file[256];
    snprintf(output_file, sizeof(output_file), "../output/output_%s.txt", date);

    FILE *outfile = fopen(output_file, "w");
    if (!outfile)
    {
        perror("Error creating output file");
        fclose(infile);
        return;
    }

    char line[MAX_LINE_LENGTH];
    int found = 0;

    while (fgets(line, sizeof(line), infile))
    {
        if (strncmp(line, date, 10) == 0)
        {
            fputs(line, outfile);
            found = 1;
        }
        else if (found)
        {
            break;
        }
    }

    fclose(infile);
    fclose(outfile);

    if (!found)
    {
        printf("No logs found for date: %s\n", date);
        remove(output_file);
    }
    else
    {
        printf("Logs extracted to %s\n", output_file);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <log_file> <YYYY-MM-DD>\n", argv[0]);
        return 1;
    }

    extract_logs(argv[1], argv[2]);
    return 0;
}
