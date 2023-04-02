#ifndef FIO_H
#define FIO_H
#include <stdio.h>
#include <stdlib.h>


FILE* createXml();
FILE* createPipe();
FILE* plotgnu(FILE* results);




FILE* createXml() {
    FILE* f = fopen("newxml.xml", "w");
    fprintf(f, "4,1");
    fprintf(f, "25,200");
    
    fclose(f);
    return f;
}


FILE* createPipe(FILE* results)  {
    FILE* pipe = popen("echo hello", "w");

    pclose(pipe);
    return pipe; 
}

FILE* plotgnu(FILE* results) {

    char* buf = malloc(sizeof(char)*10);
    results = fopen("newxml.xml", "r");

    while (!feof(results)) {
        fscanf(results, "%s\n", buf)
    }
    

    if (results == NULL) {
        printf("%s", "Going to return NULL");
        return NULL;
    }


    else {
        FILE* pipe = popen("gnuplot -persist", "w");

                     fprintf(pipe, "set terminal dumb\n");
                     fprintf(pipe, "set datafile sep \',\'\n");
                     fprintf(pipe, "set xrange [%s]\n", "0:50");
                     fprintf(pipe, "set yrange [%s]\n", "0:500");
                     fprintf(pipe, "plot \"newxml.xml\" using %s with lines\n", "2:1");
                     fprintf(pipe, "exit\n");
                pclose(pipe);
    }



//    fscanf(results, "%s", buf);
    //printf("\n%s\n", buf);
    //fclose(results);
    //free(buf);

}


#endif