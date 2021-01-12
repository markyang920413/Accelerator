#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
    if(argc<1){
        printf("Usage: ./[Program] [How_many_iteration]");
        exit(1);
    }
    FILE* frp=fopen("./successed.txt","r");
    FILE* fwp=fopen("./convert.txt","w");
    int before_local=0;
    double sum=0;
    double avg_time=0;
    int how_many_iter=atoi(argv[1]);
    while(!feof(frp)){
        double time;
        int global;
        int local;
        fscanf(frp,"%lf",&time);
        fscanf(frp,"%d",&global);
        fscanf(frp,"%d",&local);
        sum+=time;
        if(local!=before_local){
            before_local=local;
            avg_time=sum/how_many_iter;
            fprintf(fwp,"global:%d local:%d avg_time:%f\n", global,local,avg_time);
            sum=0;
        }
    }
    fclose(frp);
    fclose(fwp);
}