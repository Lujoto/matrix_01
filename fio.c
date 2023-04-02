#include "fio.h"


int main() {
    FILE* f = createXml();
    FILE* pipe = createPipe(f);

    plotgnu(f);


    
    fprintf(pipe, "ls\n" );



    //fprintf(f, "4,1");
    //fclose(f);
   // pclose(pipe);
   
}