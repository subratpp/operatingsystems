//Subrat Prasad Panda, CS1913
//Assignment 1


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printCPU()
{
    printf("CPU Information :\n");

    //use linux commands
    system("grep -m1 'cpu cores' /proc/cpuinfo");

    //read from the proc file and use string functions
    FILE *fp;
    fp = fopen("/proc/cpuinfo", "r");

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, fp)) != -1)
    {
        if (strstr(line, "cpu MHz") != NULL)
            printf("%s", line);
    }

    fclose(fp);
}

void printVersion()
{
    printf("Version Information :\n");

    //read from the proc file and use string functions
    FILE *fp;
    fp = fopen("/proc/version", "r");
    
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    read = getline(&line, &len, fp);
    printf("%s", line);
    
    free(line);
    fclose(fp);
}

void printUptime()
{
    printf("System Uptime :\n");

    //read from the proc file and use string functions
    FILE *fp;
    fp = fopen("/proc/uptime", "r");
    
    int n;
    fscanf(fp, "%d", &n);

    int day = n / (24 * 3600);
    n = n % (24 * 3600);
    int hour = n / 3600;
    n %= 3600;
    int minutes = n / 60;
    n %= 60;
    int seconds = n;

    printf("%d days: %2d hrs : %2d min: %2d sec", day, hour, minutes, seconds);
    fclose(fp);
}

void printLoadavg()
{
    printf("Load Average in 15mins :\n");

    //read from the proc file and use string functions
    FILE *fp;
    fp = fopen("/proc/loadavg", "r");

    char r;
    fscanf(fp, "%*s%*s"); //skip first 2 entries
    getc(fp); // eat away space character
    while ((r = getc(fp)) != ' ')
        printf("%c", r);
    printf("seconds \n");

    fclose(fp);
}

void printMeminfo()
{
    printf("Memory Information :\n");

    //read from the proc file and use string functions
    FILE *fp;
    fp = fopen("/proc/meminfo", "r");

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, fp)) != -1)
        if (strstr(line, "Mem") != NULL)
            printf("%s", line);

    free(line);        
    fclose(fp);
}

void printSwapmem()
{
    printf("Swap Memory Information :\n");

    //read from the proc file and use string functions
    FILE *fp;
    fp = fopen("/proc/meminfo", "r");

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, fp)) != -1)
    {
        if ( (strstr(line, "SwapTotal") != NULL) || (strstr(line, "SwapFree") != NULL) )
            printf("%s", line);
    }

    fclose(fp);
}

void printSwapinfo()
{
    printf("Swap Parition Information :\n");

    //read from the proc file and use string functions
    FILE *fp;
    fp = fopen("/proc/swaps", "r");

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, fp)) != -1)
        printf("%s", line);

    fclose(fp);
}

void printModeinfo()
{
    printf("User Mode and Kernel Mode Processor Information :\n");

    //read from the proc file and use string functions
    FILE *fp;
    fp = fopen("/proc/stat", "r");

    long int user, kernel;
    fscanf(fp, "%*[^ ]%ld %*[^ ]%ld", &user, &kernel);
    printf("User Mode: %ld centiseconds \nKernel Mode: %ld centiseconds\n", user, kernel);
    
    fclose(fp);
}

void printContextswitch()
{
    printf("Context Switch :\n");

    //read from the proc file and use string functions
    FILE *fp;
    fp = fopen("/proc/stat", "r");

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, fp)) != -1)
    {
        if (strstr(line, "ctxt") != NULL)
            {
                printf("%s", line);
                break;
            }
    }

    fclose(fp);
}

void printIntr()
{
    printf("Total Interrupts :\n");

    //read from the proc file and use string functions
    FILE *fp;
    fp = fopen("/proc/stat", "r");

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, fp)) != -1)
    {
        if (strstr(line, "intr") != NULL)
        {
            long int intr;
            sscanf(line, "%*s %ld", &intr);
            printf("Interrupts: %ld \n", intr);
            break;
        }
    }

    fclose(fp);
}

int main(int argc, char const *argv[])
{
    int choice = 0;

    while (1)
    {
        printf("\nEnter your choice :\n");
        printf("1. CPU Information\n");
        printf("2. Linux Kernel Version\n");
        printf("3. Time Since Last Boot\n");
        printf("4. Average Load on System last 15 mins\n");
        printf("5. Memory Information :\n");
        printf("6. Swap SpaceInformation\n");
        printf("7. Swap Partition Information\n");
        printf("8. CPU time Kernel and User Mode\n");
        printf("9. Number of Context Switches\n");
        printf("10. Number of Interrupts\n");
        printf("11. All Information\n");
        printf("12. Exit\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printCPU();
            break;

        case 2:
            printVersion();
            break;

        case 3:
            printUptime();
            break;

        case 4:
            printLoadavg();
            break;

        case 5:
            printMeminfo();
            break;

        case 6:
            printSwapmem();
            break;

        case 7:
            printSwapinfo();
            break;

        case 8:
            printModeinfo();
            break;

        case 9:
            printContextswitch();
            break;

        case 10:
            printIntr();
            break;

        case 11:
            printCPU();
            printVersion();
            printUptime();
            printLoadavg();
            printMeminfo();
            printSwapmem();
            printSwapinfo();
            printModeinfo();
            printContextswitch();
            printIntr();
            break;

        case 12:
            exit(0);
            break;

        default:
            printf("Invalid Choice!");
            break;
        }
    }

    return 0;
}