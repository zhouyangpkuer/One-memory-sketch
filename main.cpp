#include <iostream>
#include <fstream>
#include <map>
#include <stdio.h>
#include <string>
#include "cmsketch.h"
#include "csketch.h"
#include "cusketch.h"
#include "cmlsketch.h"
#include "cmsketch_nonconflict.h"
#include "csketch_nonconflict.h"
#include "cusketch_nonconflict.h"
#include "cmlsketch_nonconflict.h"
#include "pfsketch_cu.h"
#include "filter.h"
using namespace std;




// #define UNIFORM
#define CM
#define CU
#define CML
#define C
// #define PF




#ifdef UNIFORM
const char * filename_FlowTraffic = "../insert_uni_filted.txt";
#else 
const char * filename_FlowTraffic = "../insert_zipf_filted.txt";
#endif

string filename_result_CM = "../result/resCM";
string filename_result_CU = "../result/resCU";
string filename_result_CML = "../result/resCML";
string filename_result_C = "../result/resC";
string filename_result_PF = "../result/resPF";

string mkname(string str, int w, int c, int hw, int hc)
{
    char buf[1000];
    
    str +="_w_";
    sprintf(buf, "%d", w);
    str += buf;

    str +="_c_";
    sprintf(buf, "%d", c);
    str += buf;
    
    str +="_hw_";
    sprintf(buf, "%d", hw);
    str += buf;
    
    str +="_hc_";
    sprintf(buf, "%d", hc);
    str += buf;
    
    str += ".txt";
    return str;
}
int main(int argc, char ** argv)
{
    int w = atoi(argv[1]);
    int c = atoi(argv[2]);
    int hw = atoi(argv[3]);
    int hc = atoi(argv[4]);
    // cout << w << " " << c << " " << hw << " " << hc << endl;
    // filter();
    FILE *file_FlowTraffic = fopen(filename_FlowTraffic, "r");
    string file_name;
    char str[1000];

#ifdef CM    
    file_name = mkname(filename_result_CM, w, c, hw, hc);
    strcpy(str, file_name.c_str());
    // cout << str << endl;
    FILE *file_result_CM = fopen((const char *)str, "w");
    NCMSketch cmsketch(w, c, hw, hc);
#endif

#ifdef CU
    file_name = mkname(filename_result_CU, w, c, hw, hc);
    strcpy(str, file_name.c_str());
    FILE *file_result_CU = fopen((const char *)str, "w");
    NCUSketch cusketch(w, c, hw, hc);
#endif

#ifdef CML
    file_name = mkname(filename_result_CML, w, c, hw, hc);
    strcpy(str, file_name.c_str());
    FILE *file_result_CML = fopen((const char *)str, "w");
    NCMLSketch cmlsketch(w, c, hw, hc);
#endif

#ifdef C
    file_name = mkname(filename_result_C, w, c, hw, hc);
    strcpy(str, file_name.c_str());
    FILE *file_result_C = fopen((const char *)str, "w");
	NCSketch csketch(w, c, hw, hc);
#endif 

#ifdef PF
    file_name = mkname(filename_result_PF, w, c, hw, hc);
    strcpy(str, file_name.c_str());
    FILE *file_result_PF = fopen((const char *)str, "w");
	PFSketch_cu pfsketch(w, c, hw, hc);
#endif

    // char str[1000];
    int val, valCM, valCU, valCML, valC, valPF;

    double sumCM = 0, sumCU = 0, sumCML = 0, sumC = 0, sumPF = 0;
    double resCM = 0, resCU = 0, resCML = 0, resC = 0, resPF = 0;
    for(int i = 0; i < N_QUERY; i++)
    {
        fscanf(file_FlowTraffic, "%s %d", str, &val);
        for(int j = 0; j < val; j++)
        {
            #ifdef CM
            cmsketch.Insert((const char *)str);
            #endif 

            #ifdef CU
            cusketch.Insert((const char *)str);
            #endif

            #ifdef CML
            cmlsketch.Insert((const char *)str);
            #endif

            #ifdef C
            csketch.Insert((const char *)str);
            #endif

            #ifdef PF
            pfsketch.Insert((const char *)str);
            #endif
        }
    }
    rewind(file_FlowTraffic);

	for(int i = 0; i < N_QUERY; i++)
    {
        fscanf(file_FlowTraffic, "%s %d", str, &val);
        #ifdef CM   
        valCM = cmsketch.Query((const char *)str);
        sumCM += fabs((double)(valCM - val)) / N_QUERY;
        
        fprintf(file_result_CM, "%d\t%d\n", val, valCM);
        #endif

        #ifdef CU
        valCU = cusketch.Query((const char *)str);
        sumCU += fabs((double)(valCU - val)) / N_QUERY;

        fprintf(file_result_CU, "%d\t%d\n", val, valCU);
        #endif 

        #ifdef CML
        valCML = cmlsketch.Query((const char *)str);
        sumCML += fabs((double)(valCML - val)) / N_QUERY;
        
        fprintf(file_result_CML, "%d\t%d\n", val, valCML);
        #endif

        #ifdef C
        valC = csketch.Query((const char *)str);
        sumC += fabs((double)(valC - val)) / N_QUERY;
        
        fprintf(file_result_C, "%d\t%d\n", val, valC);
        #endif

        #ifdef PF
        valPF = pfsketch.Query((const char *)str);
        sumPF += fabs((double)(valPF - val)) / N_QUERY;
        
        fprintf(file_result_PF, "%d\t%d\n", val, valPF);
        #endif
    }

#ifdef CM
    fclose(file_result_CM);
    printf("DE_CM\t%lf\n", sumCM);

#endif

#ifdef CU
    fclose(file_result_CU);
    printf("DE_CU\t%lf\n", sumCU);

#endif

#ifdef CML
    fclose(file_result_CML);
    printf("DE_CML\t%lf\n", sumCML);

#endif

#ifdef C
    fclose(file_result_C);
    printf("DE_C\t%lf\n", sumC);

#endif 

#ifdef PF
    fclose(file_result_PF);
    printf("DE_PF\t%lf\n", sumPF);

#endif

	return 0;
}