#include <stdio.h>
#include <string.h>

void p1_RAM(){
    //cat /proc/meminfo
    printf("MEMORIA: \n");
    FILE *informacion=fopen("/proc/meminfo", "rb");
    char line[1024];
    while(fgets(line,1024,informacion))
    {
        if(strstr(line,"MemTotal"))
        {
            puts(line);
            break;
        }
    }
    fclose(informacion);
}

int main()
{
    p1_RAM();
}