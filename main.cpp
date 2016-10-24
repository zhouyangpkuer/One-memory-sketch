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
#include "cusketch_plus.h"
#include "cbsketch.h"
#include "filter.h"
#include "params.h"

using namespace std;

// #define UNIFORM

// #define CM
#define CU
// #define CML
// #define C
// #define PF
// #define CU_PLUS
#define CB

#ifdef UNIFORM
const char * filename_FlowTraffic = "../insert_uni_filted.txt";
const char * filename_FlowTraffic2 = "../FlowTraffic_uniform.txt";
#else 
const char * filename_FlowTraffic = "../insert_zipf_filted.txt";
const char * filename_FlowTraffic2 = "../FlowTraffic_zipfian.txt";
#endif

string filename_result_CM = "../result/resCM";
string filename_result_CU = "../result/resCU";
string filename_result_CML = "../result/resCML";
string filename_result_C = "../result/resC";
string filename_result_PF = "../result/resPF";
string filename_result_CU_plus = "../result/resCU_plus";
string filename_result_CB = "../result/resCB";

string mkname(string str, int sum_m, int w, int c, int hw, int hc)
{
    char buf[1000];
    
    str += "_pm_";
    sprintf(buf, "%d", sum_m);
    str += buf;
        
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
string mkname2(string str, int sum_m, int term, int cnt1, int cnt2, int size_1, int size_2, int k)
{
    char buf[1000];

    str += "_pm_";
    sprintf(buf, "%d", sum_m);
    str += buf;
    
    str += "_term_";
    sprintf(buf, "%d", term);
    str += buf;

    str +="_cnt1_";
    sprintf(buf, "%d", cnt1);
    str += buf;

    str +="_cnt2_";
    sprintf(buf, "%d", cnt2);
    str += buf;
    
    str +="_size1_";
    sprintf(buf, "%d", size_1);
    str += buf;
    
    str +="_size2_";
    sprintf(buf, "%d", size_2);
    str += buf;
    
    str +="_k_";
    sprintf(buf, "%d", k);
    str += buf;
    
    str += ".txt";
    return str;
}

int main(int argc, char ** argv)
{
    if(argc != 1)
    {
        int w = atoi(argv[1]);
        int c = atoi(argv[2]);
        int hw = atoi(argv[3]);
        int hc = atoi(argv[4]);
    
        cout << "w=" << w << " " << "c=" << c << " " 
        << "hw=" << hw << " " << "hc=" << hc << endl;
    }
    // // filter();
    FILE *file_FlowTraffic = fopen(filename_FlowTraffic2, "r");
    string file_name;
    char str[1000];
    // cout << "fasfd" << endl;

    int w = (int)(pm * 1024 * 1024 * 8 / (COUNTER_SIZE * COUNTER_PER_WORD));
    int c = COUNTER_PER_WORD;
    int hw = HASH_WORD;
    int hc = HASH_COUNTER;
    
#ifdef CM    

    file_name = mkname(filename_result_CM, pm, w, c, hw, hc);
    strcpy(str, file_name.c_str());
    // cout << str << endl;
    FILE *file_result_CM = fopen((const char *)str, "w");
    NCMSketch cmsketch(w, c, hw, hc);
#endif

#ifdef CU
    file_name = mkname(filename_result_CU, pm, w, c, hw, hc);
    strcpy(str, file_name.c_str());
    FILE *file_result_CU = fopen((const char *)str, "w");
    NCUSketch cusketch(w, c, hw, hc);
#endif

#ifdef CML
    file_name = mkname(filename_result_CML, pm, w, c, hw, hc);
    strcpy(str, file_name.c_str());
    FILE *file_result_CML = fopen((const char *)str, "w");
    NCMLSketch cmlsketch(w, c, hw, hc);
#endif

#ifdef C
    file_name = mkname(filename_result_C, pm, w, c, hw, hc);
    strcpy(str, file_name.c_str());
    FILE *file_result_C = fopen((const char *)str, "w");
	NCSketch csketch(w, c, hw, hc);
#endif 

#ifdef PF
    file_name = mkname(filename_result_PF, pm, w, c, hw, hc);
    strcpy(str, file_name.c_str());
    FILE *file_result_PF = fopen((const char *)str, "w");
	PFSketch_cu pfsketch(w, c, hw, hc);
#endif

#ifdef CU_PLUS
    file_name = mkname(filename_result_CU_plus, pm, w, c, hw, hc);
    strcpy(str, file_name.c_str());
    FILE *file_result_CU_plus = fopen((const char *)str, "w");
    CUSketch_plus cusketch_plus(w, c, hw, hc);
#endif

#ifdef CB

    int cnt2 = (int)(pm * 1024 * 1024 * 8 / (counter_ratio * (size1 + 1) + size2)); // (1+8)*10 + 56;
    int cnt1 = counter_ratio * cnt2;

    file_name = mkname2(filename_result_CB, pm, max_term, cnt1, cnt2, size1, size2, hash_num_cb);
    strcpy(str, file_name.c_str());
    FILE *file_result_CB = fopen((const char *)str, "w");
    CBSketch *cbsketch = new CBSketch(cnt1, cnt2, size1, size2, hash_num_cb);

#endif

    // char str[1000];
    // char temp[1000];
    int ip_s, ip_d;

    int val, valCM, valCU, valCML, valC, valPF, valCU_plus, valCB;

    double sumCM = 0, sumCU = 0, sumCML = 0, sumC = 0, sumPF = 0, sumCU_plus = 0, sumCB = 0;
    double rsumCM = 0, rsumCU = 0, rsumCML = 0, rsumC = 0, rsumPF = 0, rsumCU_plus = 0, rsumCB = 0;

    double resCM = 0, resCU = 0, resCML = 0, resC = 0, resPF = 0, resCU_plus = 0, resCB = 0;
    for(int i = 0; i < N_QUERY; i++)
    {
        // fscanf(file_FlowTraffic, "%s %d", str, &val);
        fscanf(file_FlowTraffic, "%u %u %d", &ip_s, &ip_d, &val);
        sprintf(str,"%u%u", ip_s, ip_d);

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

            #ifdef CU_PLUS
            cusketch_plus.Insert((const char *)str);
            #endif

            #ifdef CB
            cbsketch->Insert(i, ip_d, 1);
            #endif
        }
    }
    rewind(file_FlowTraffic);

    #ifdef CB
    cbsketch->carrier();
    cbsketch->decode(max_term, N_QUERY);
    int *est_rlt = cbsketch->get_est_rlt();
    #endif

    int zero = 0;
	for(int i = 0; i < N_QUERY; i++)
    {
        // fscanf(file_FlowTraffic, "%s %d", str, &val);
        fscanf(file_FlowTraffic, "%u %u %d", &ip_s, &ip_d, &val);
        sprintf(str,"%u%u", ip_s, ip_d);

        if(val == 0)
            zero++;

        #ifdef CM   
        valCM = cmsketch.Query((const char *)str);
        sumCM += fabs((double)(valCM - val)) / N_QUERY;
        if(val != 0)
            rsumCM += fabs((double)(valCM - val)) / val;
        
        fprintf(file_result_CM, "%d\t%d\n", val, valCM);
        #endif

        #ifdef CU
        valCU = cusketch.Query((const char *)str);
        sumCU += fabs((double)(valCU - val)) / N_QUERY;
        if(val != 0)
            rsumCU += fabs((double)(valCU - val)) / val;
        
        fprintf(file_result_CU, "%d\t%d\n", val, valCU);
        #endif 

        #ifdef CML
        valCML = cmlsketch.Query((const char *)str);
        sumCML += fabs((double)(valCML - val)) / N_QUERY;
        if(val != 0)
            rsumCML += fabs((double)(valCML - val)) / val;
        
        fprintf(file_result_CML, "%d\t%d\n", val, valCML);
        #endif

        #ifdef C
        valC = csketch.Query((const char *)str);
        sumC += fabs((double)(valC - val)) / N_QUERY;
        if(val != 0)
            rsumC += fabs((double)(valC - val)) / val;
        
        fprintf(file_result_C, "%d\t%d\n", val, valC);
        #endif

        #ifdef PF
        valPF = pfsketch.Query((const char *)str);
        sumPF += fabs((double)(valPF - val)) / N_QUERY;
        if(val != 0)
            rsumPF += fabs((double)(valPF - val)) / val;
        
        fprintf(file_result_PF, "%d\t%d\n", val, valPF);
        #endif

        #ifdef CU_PLUS
        valCU_plus = cusketch_plus.Query((const char *)str);
        sumCU_plus += fabs((double)(valCU_plus - val)) / N_QUERY;
        if(val != 0)
            rsumCU_plus += fabs((double)(valCU_plus - val)) / val;
        
        fprintf(file_result_CU_plus, "%d\t%d\n", val, valCU_plus);
        #endif

        #ifdef CB   
        // valCM = cmsketch.Query((const char *)str);
        valCB = est_rlt[i];
        sumCB += fabs((double)(valCB - val)) / N_QUERY;
        if(val != 0)
            rsumCB += fabs((double)(valCB - val)) / val;
        
        fprintf(file_result_CB, "%d\t%d\n", val, valCB);
        #endif

    }

#ifdef CM
    fclose(file_result_CM);
    printf("DE_CM\t\t%lf\t\tRE_CM\t\t%lf\n", sumCM, rsumCM / (N_QUERY - zero));
#endif

#ifdef CU
    fclose(file_result_CU);
    printf("%-*s%-*lf%-*s%-*lf\n",
         15, "DE_CU", 15, sumCU, 15, "RE_CU", 15, rsumCU / (N_QUERY - zero));

#endif

#ifdef CML
    fclose(file_result_CML);
    printf("DE_CML\t\t%lf\t\tRE_CML\t\t%lf\n", sumCML, rsumCML / (N_QUERY - zero));

#endif

#ifdef C
    fclose(file_result_C);
    printf("DE_C\t\t%lf\t\tRE_C\t\t%lf\n", sumC, rsumC / (N_QUERY - zero));

#endif 

#ifdef PF
    fclose(file_result_PF);
    printf("DE_PF\t\t%lf\t\tRE_PF\t\t%lf\n", sumPF, rsumPF / (N_QUERY - zero));
 
#endif

#ifdef CU_PLUS
    fclose(file_result_CU_plus);
    printf("%-*s%-*lf%-*s%-*lf\n",
         15, "DE_CU_plus", 15, sumCU_plus, 15, "RE_CU_plus", 15, rsumCU_plus / (N_QUERY - zero));
#endif


#ifdef CB
    fclose(file_result_CB);
    printf("%-*s%-*lf%-*s%-*lf\n",
         15, "DE_CB", 15, sumCB, 15, "RE_CB", 15, rsumCB / (N_QUERY - zero));

#endif

    printf("\n");
	return 0;
}