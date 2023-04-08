#ifndef FIO_H
#define FIO_H
#include <stdio.h>
#include <stdlib.h>


FILE* createXml();
FILE* createPipe();
void plotgnu();




FILE* createXml() {
    FILE* f = fopen("newxml.xml", "w");
    fprintf(f, "4,1\n");
    fprintf(f, "25,200");
    
    fclose(f);
    return f;
}


FILE* createPipe(FILE* results)  {
    FILE* pipe = popen("echo hello", "w");

    pclose(pipe);
    return pipe; 
}

void plotgnu() {
    FILE* res = fopen("bTreeResults.csv", "r");
    FILE* temp = fopen("temp.csv", "w");

    char* buf = malloc(sizeof(*buf)*124);

    while(!feof(res)) {
        fscanf(res, "%s\n", buf);
        printf("%s", buf);
    }
    rewind(res);

    while(!feof(res)) {
        fprintf(temp, "%s\n", buf);
    }

    rewind(res);

    fclose(res); 
    fclose(temp);

    free(buf);

}    




//FILE* plotgnu(FILE* results) {

    //char* buf = malloc(sizeof(char)*10);
    //results = fopen("newxml.xml", "r");

    //while (!feof(results)) {
        //fscanf(results, "%s\n", buf);
    //}
    

    //if (results == NULL) {
        //printf("%s", "Results file is NULL");
        //return NULL;
    //}


    //else {
        //printf("\n%s\n", buf);


        //FILE* pipe = popen("gnuplot -persist", "w");
                //fprintf(pipe, "set terminal dumb\n");
                //fprintf(pipe, "set datafile sep \',\'\n");
                //fprintf(pipe, "set xrange [%s]\n", "0:50");
                //fprintf(pipe, "set yrange [%s]\n", "0:500");
                ////fprintf(pipe, "plot \"newxml.xml\" using %s with lines\n", "2:1");
                //fprintf(pipe, "plot  \"< /home/joto/source/matrix_01/bTreeResults.csv\" using %s with lines\n", "2:1");
                //fprintf(pipe, "exit\n");
                //pclose(pipe);
    //}



////    fscanf(results, "%s", buf);
    ////printf("\n%s\n", buf);
    ////fclose(results);
    //free(buf);

//}


#endif