#include <iostream>
#include <fstream>
#include <map>
#include <stdio.h>
#include <string>
#include <vector>

// #define CM
// #define CU
// #define CML
#define C
// #define PF
// #define CU_PLUS
// #define CB
// #define UNIFORM

#include "filter.h"
#include "params.h"

#ifdef CM
#include "cmsketch.h"
#include "cmsketch_nonconflict.h"
#endif
#ifdef C
#include "csketch.h"
#include "csketch_nonconflict.h"
#endif
#ifdef CU
#include "cusketch.h"
#include "cusketch_nonconflict.h"
#include "cusketch_plus.h"
#endif
#ifdef CML
#include "cmlsketch.h"
#include "cmlsketch_nonconflict.h"
#endif
#ifdef PF
#include "pfsketch_cu.h"
#include "pfsketch.h"
#endif
#ifdef CB
// #include "cbsketch_term.h"
#include "cbsketch_origin.h"
#include "onememcb.h"
#endif


using namespace std;


vector<double> vec_RECB;
vector<double> vec_RECU_PLUS;
vector<double> vec_RECM;
vector<double> vec_RECML;
vector<double> vec_RECU;
vector<double> vec_REPF;
vector<double> vec_REC;

vector<double> vec_RECB_one;
vector<double> vec_RECU_PLUS_one;
vector<double> vec_RECM_one;
vector<double> vec_RECML_one;
vector<double> vec_RECU_one;
vector<double> vec_REPF_one;
vector<double> vec_REC_one;


#ifdef UNIFORM
const char * filename_FlowTraffic = "../insert_uni_filted.txt";
const char * filename_FlowTraffic2 = "../FlowTraffic_uniform.txt";
#else 
const char * filename_FlowTraffic = "../insert_zipf_filted.txt";
const char * filename_FlowTraffic2 = "../FlowTraffic_zipfian.txt";
#endif

string filename_result_CM = "../result/python_draw/RES/resCM";
string filename_result_CU = "../result/python_draw/RES/resCU";
string filename_result_CML = "../result/python_draw/RES/resCML";
string filename_result_C = "../result/python_draw/RES/resC";
string filename_result_PF = "../result/python_draw/RES/resPF";
string filename_result_CU_plus = "../result/python_draw/RES/resCU_plus";
string filename_result_CB = "../result/python_draw/RES/resCB";

string filename_result_CM_one = "../result/python_draw/RES/resCM_one";
string filename_result_CU_one = "../result/python_draw/RES/resCU_one";
string filename_result_CML_one = "../result/python_draw/RES/resCML_one";
string filename_result_C_one = "../result/python_draw/RES/resC_one";
string filename_result_PF_one = "../result/python_draw/RES/resPF_one";
string filename_result_CU_plus_one = "../result/python_draw/RES/resCU_plus_one";
string filename_result_CB_one = "../result/python_draw/RES/resCB_one";

void mkDrawData(vector<double> vec, vector<double> vec_one, FILE * file_data)
{

    sort(vec.begin(), vec.end());
    sort(vec_one.begin(), vec_one.end());

    double max_re1 = *(vec.end() - 1);
    // cout << max_re1 << endl;
    double delta1 = max_re1 / 30;
    // cout << delta1 << endl;

    double max_re2 = *(vec_one.end() - 1);
    // cout << max_re2 << endl;
    double delta2 = max_re2 / 30;
    // cout << delta2 << endl;

    double max_re, delta;
    if(max_re1 < max_re2)
    {
        max_re = max_re1;
        delta = delta1;
    }
    else
    {
        max_re = max_re2;
        delta = delta2;
    }

    double t1, t2;
    double t3, t4;
    int j1 = 0, j2 = 0;
    double size = vec.size();

    for(int i = 1; i <= 30; i++)
    {
        for(; j1 < size; j1++)
        {  
            if(vec[j1] > i * delta)
                break;
        }
        t1 = j1 + 1;
        t2 = t1 / size;

        for(; j2 < size; j2++)
        {  
            if(vec_one[j2] > i * delta)
                break;
        }

        t3 = j2 + 1;
        t4 = t3 / size;
        
        fprintf(file_data ,"%lf,%lf,%lf\n", i * delta, t2, t4);
    }
    fclose(file_data);
}

string mkname(string str, double sum_m, int w, int c, int hw, int hc)
{
    char buf[1000];
    
    str += "_pm_";
    sprintf(buf, "%lf", sum_m);
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
string mkname2(string str, double sum_m, int term, int cnt1, int cnt2, int size_1, int size_2, int k)
{
    char buf[1000];

    str += "_pm_";
    sprintf(buf, "%lf", sum_m);
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

    file_name = mkname(filename_result_CM, pm, 750000, 8, hw, hc);
    strcpy(str, file_name.c_str());
    FILE *file_result_CM = fopen((const char *)str, "w");
      
    file_name = mkname(filename_result_CM_one, pm, 750000, 8, hw, hc);
    strcpy(str, file_name.c_str());
    FILE *file_result_CM_one = fopen((const char *)str, "w");
    
    NCMSketch cmsketch(750000, 8, 3, 3);
    NCMSketch onemem_cmsketch(750000, 8, 1, 3);

#endif

#ifdef CU
    // file_name = mkname(filename_result_CU, pm, w, c, hw, hc);
    // strcpy(str, file_name.c_str());
    // FILE *file_result_CU = fopen((const char *)str, "w");
    // NCUSketch cusketch(w, c, hw, hc);
    file_name = mkname(filename_result_CU, pm, 750000, 8, hw, hc);
    strcpy(str, file_name.c_str());
    FILE *file_result_CU = fopen((const char *)str, "w");
      
    file_name = mkname(filename_result_CU_one, pm, 750000, 8, hw, hc);
    strcpy(str, file_name.c_str());
    FILE *file_result_CU_one = fopen((const char *)str, "w");
    
    NCUSketch cusketch(750000, 8, 3, 3);
    NCUSketch onemem_cusketch(750000, 8, 1, 3);
#endif

#ifdef CML
    // file_name = mkname(filename_result_CML, pm, w, c, hw, hc);
    // strcpy(str, file_name.c_str());
    // FILE *file_result_CML = fopen((const char *)str, "w");
    // NCMLSketch cmlsketch(w, c, hw, hc);
    file_name = mkname(filename_result_CML, pm, 750000, 8, hw, hc);
    strcpy(str, file_name.c_str());
    FILE *file_result_CML = fopen((const char *)str, "w");
      
    file_name = mkname(filename_result_CML_one, pm, 750000, 8, hw, hc);
    strcpy(str, file_name.c_str());
    FILE *file_result_CML_one = fopen((const char *)str, "w");
    
    NCMLSketch cmlsketch(750000, 8, 3, 3);
    NCMLSketch onemem_cmlsketch(750000, 8, 1, 3);
#endif

#ifdef C
 //    file_name = mkname(filename_result_C, pm, w, c, hw, hc);
 //    strcpy(str, file_name.c_str());
 //    FILE *file_result_C = fopen((const char *)str, "w");
	// NCSketch csketch(w, c, hw, hc); 
    file_name = mkname(filename_result_C, pm, 750000, 8, hw, hc);
    strcpy(str, file_name.c_str());
    FILE *file_result_C = fopen((const char *)str, "w");
      
    file_name = mkname(filename_result_C_one, pm, 750000, 8, hw, hc);
    strcpy(str, file_name.c_str());
    FILE *file_result_C_one = fopen((const char *)str, "w");
    
    NCSketch csketch(750000, 8, 3, 3);
    NCSketch onemem_csketch(750000, 8, 1, 3);
#endif 

#ifdef PF
    file_name = mkname(filename_result_PF, pm, 750000, 8, hw, hc);
    strcpy(str, file_name.c_str());
    FILE *file_result_PF = fopen((const char *)str, "w");
      
    file_name = mkname(filename_result_PF_one, pm, 750000, 8, hw, hc);
    strcpy(str, file_name.c_str());
    FILE *file_result_PF_one = fopen((const char *)str, "w");
    
    PFSketch pfsketch(750000, 8, 3, 3);
    PFSketch onemem_pfsketch(750000, 8, 1, 3);

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


    file_name = mkname2(filename_result_CB_one, pm, max_term, cnt1, cnt2, size1, size2, hash_num_cb);
    strcpy(str, file_name.c_str());
    FILE *file_result_CB_one = fopen((const char *)str, "w");
    CBSketch_one *onemem_cbsketch = new CBSketch_one(cnt1, cnt2, size1, size2, hash_num_cb);
#endif

    // char str[1000];
    // char temp[1000];
    int ip_s, ip_d;

    int val, valCM, valCU, valCML, valC, valPF, valCU_plus, valCB;
    double sumCM = 0, sumCU = 0, sumCML = 0, sumC = 0, sumPF = 0, sumCU_plus = 0, sumCB = 0;
    double rsumCM = 0, rsumCU = 0, rsumCML = 0, rsumC = 0, rsumPF = 0, rsumCU_plus = 0, rsumCB = 0;
    double resCM = 0, resCU = 0, resCML = 0, resC = 0, resPF = 0, resCU_plus = 0, resCB = 0;
    
    int valCM_one, valCU_one, valCML_one, valC_one, valPF_one, valCU_plus_one, valCB_one;
    double sumCM_one = 0, sumCU_one = 0, sumCML_one = 0, sumC_one = 0, sumPF_one = 0, sumCU_plus_one = 0, sumCB_one = 0;
    double rsumCM_one = 0, rsumCU_one = 0, rsumCML_one = 0, rsumC_one = 0, rsumPF_one = 0, rsumCU_plus_one = 0, rsumCB_one = 0;
    double resCM_one = 0, resCU_one = 0, resCML_one = 0, resC_one = 0, resPF_one = 0, resCU_plus_one = 0, resCB_one = 0;

    double temp;
    int max_val = 0;
    for(int i = 0; i < N_QUERY; i++)
    {
        // fscanf(file_FlowTraffic, "%s %d", str, &val);
        fscanf(file_FlowTraffic, "%u %u %d", &ip_s, &ip_d, &val);
        sprintf(str,"%u%u", ip_s, ip_d);
        max_val = max(max_val, val);
        for(int j = 0; j < val; j++)
        {
            #ifdef CM
            cmsketch.Insert((const char *)str);
            onemem_cmsketch.Insert((const char *)str);
            #endif 

            #ifdef CU
            cusketch.Insert((const char *)str);
            onemem_cusketch.Insert((const char *)str);           
            #endif

            #ifdef CML
            cmlsketch.Insert((const char *)str);
            onemem_cmlsketch.Insert((const char *)str);
            #endif

            #ifdef C
            csketch.Insert((const char *)str);
            onemem_csketch.Insert((const char *)str);
            #endif

            #ifdef PF
            pfsketch.Insert((const char *)str);
            onemem_pfsketch.Insert((const char *)str);
            #endif

            #ifdef CU_PLUS
            cusketch_plus.Insert((const char *)str);

            #endif

            #ifdef CB
            cbsketch->Insert(i, ip_d, 1);
            onemem_cbsketch->Insert(i, ip_d, 1);
            #endif
        }
    }
    printf("max_val\t%d\n", max_val);
    rewind(file_FlowTraffic);

    #ifdef CB
    cbsketch->carrier();
    cbsketch->decode(max_term, N_QUERY);
    int *est_rlt = cbsketch->get_est_rlt();
    
    onemem_cbsketch->carrier();
    onemem_cbsketch->decode(max_term, N_QUERY);
    int *onemem_est_rlt = onemem_cbsketch->get_est_rlt();
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
        {
            temp = fabs((double)(valCM - val)) / val;
            rsumCM += temp;
            vec_RECM.push_back(temp);
        }
        fprintf(file_result_CM, "%d\t%d\n", val, valCM);
        

        valCM_one = onemem_cmsketch.Query((const char *)str);
        sumCM_one += fabs((double)(valCM_one - val)) / N_QUERY;
        if(val != 0)
        {
            temp = fabs((double)(valCM_one - val)) / val;
            rsumCM_one += temp;
            // printf("%d ", temp);
            vec_RECM_one.push_back(temp);
        }
        
        fprintf(file_result_CM_one, "%d\t%d\n", val, valCM_one);

        #endif







        #ifdef CU
        valCU = cusketch.Query((const char *)str);
        sumCU += fabs((double)(valCU - val)) / N_QUERY;
        if(val != 0)
        {
            temp = fabs((double)(valCU - val)) / val;
            rsumCU += temp;
            vec_RECU.push_back(temp);
        }
        fprintf(file_result_CU, "%d\t%d\n", val, valCU);

        valCU_one = onemem_cusketch.Query((const char *)str);
        sumCU_one += fabs((double)(valCU_one - val)) / N_QUERY;
        if(val != 0)
        {    
            temp = fabs((double)(valCU_one - val)) / val;
            rsumCU_one += temp;
            vec_RECU_one.push_back(temp);
        }
        fprintf(file_result_CU_one, "%d\t%d\n", val, valCU_one);
        #endif 








        #ifdef CML
        valCML = cmlsketch.Query((const char *)str);
        sumCML += fabs((double)(valCML - val)) / N_QUERY;
        if(val != 0)
        {
            temp = fabs((double)(valCML - val)) / val;
            rsumCML += temp;
            vec_RECML.push_back(temp);
        }
        fprintf(file_result_CML, "%d\t%d\n", val, valCML);

        valCML_one = onemem_cmlsketch.Query((const char *)str);
        sumCML_one += fabs((double)(valCML_one - val)) / N_QUERY;
        if(val != 0)
        {    
            temp = fabs((double)(valCML_one - val)) / val;
            rsumCML_one += temp;
            vec_RECML_one.push_back(temp);
        }
        fprintf(file_result_CML_one, "%d\t%d\n", val, valCML_one);
        #endif








        #ifdef C
        valC = csketch.Query((const char *)str);
        sumC += fabs((double)(valC - val)) / N_QUERY;
        if(val != 0)
        {
            temp = fabs((double)(valC - val)) / val;
            rsumC += temp;
            vec_REC.push_back(temp);
        }
        fprintf(file_result_C, "%d\t%d\n", val, valC);

        valC_one = onemem_csketch.Query((const char *)str);
        sumC_one += fabs((double)(valC_one - val)) / N_QUERY;
        if(val != 0)
        {    
            temp = fabs((double)(valC_one - val)) / val;
            rsumC_one += temp;
            vec_REC_one.push_back(temp);
        }
        fprintf(file_result_C_one, "%d\t%d\n", val, valC_one);
        #endif







        #ifdef PF
        valPF = pfsketch.Query((const char *)str);
        sumPF += fabs((double)(valPF - val)) / N_QUERY;
        if(val != 0)
        {
            temp = fabs((double)(valPF - val)) / val;
            rsumPF += temp;
            vec_REPF.push_back(temp);
        }
        fprintf(file_result_PF, "%d\t%d\n", val, valPF);

        valPF_one = onemem_pfsketch.Query((const char *)str);
        sumPF_one += fabs((double)(valPF_one - val)) / N_QUERY;
        if(val != 0)
        {    
            temp = fabs((double)(valPF_one - val)) / val;
            rsumPF_one += temp;
            vec_REPF_one.push_back(temp);
        }
        fprintf(file_result_PF_one, "%d\t%d\n", val, valPF_one);
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
        {
            temp = fabs((double)(valCB - val)) / val;
            rsumCB += temp;
            vec_RECB.push_back(temp);
        }
        
        fprintf(file_result_CB, "%d\t%d\n", val, valCB);

        valCB_one = onemem_est_rlt[i];
        sumCB_one += fabs((double)(valCB_one - val)) / N_QUERY;
        if(val != 0)
        {
            temp = fabs((double)(valCB_one - val)) / val;
            rsumCB_one += temp;
            vec_RECB_one.push_back(temp);
        }
        
        fprintf(file_result_CB_one, "%d\t%d\n", val, valCB_one);

        #endif

    }

#ifdef CM
    fclose(file_result_CM);
    printf("%-*s%-*lf%-*s%-*lf\n",
         15, "DE_CM", 15, sumCM, 15, "RE_CM", 15, rsumCM / (N_QUERY - zero));
    fclose(file_result_CM_one);
    printf("%-*s%-*lf%-*s%-*lf\n",
         15, "DE_CM_one", 15, sumCM_one, 15, "RE_CM_one", 15, rsumCM_one / (N_QUERY - zero));

    FILE *RE_CM = fopen("../result/python_draw/RE/RE_CM.dat", "w");
    fprintf(RE_CM, "%s,%s,%s\n", "Relative error", "CM", "OneMemCM");
    mkDrawData(vec_RECM, vec_RECM_one, RE_CM);

#endif

#ifdef CU
    fclose(file_result_CU);
    printf("%-*s%-*lf%-*s%-*lf\n",
         15, "DE_CU", 15, sumCU, 15, "RE_CU", 15, rsumCU / (N_QUERY - zero));
    fclose(file_result_CU_one);
    printf("%-*s%-*lf%-*s%-*lf\n",
         15, "DE_CU_one", 15, sumCU_one, 15, "RE_CU_one", 15, rsumCU_one / (N_QUERY - zero));

    FILE *RE_CU = fopen("../result/python_draw/RE/RE_CU.dat", "w");
    fprintf(RE_CU, "%s,%s,%s\n", "Relative error", "CU", "OneMemCU");
    mkDrawData(vec_RECU, vec_RECU_one, RE_CU);

#endif

#ifdef CML
    fclose(file_result_CML);
    printf("%-*s%-*lf%-*s%-*lf\n",
         15, "DE_CML", 15, sumCML, 15, "RE_CML", 15, rsumCML / (N_QUERY - zero));
    fclose(file_result_CML_one);
    printf("%-*s%-*lf%-*s%-*lf\n",
         15, "DE_CML_one", 15, sumCML_one, 15, "RE_CML_one", 15, rsumCML_one / (N_QUERY - zero));

    FILE *RE_CML = fopen("../result/python_draw/RE/RE_CML.dat", "w");
    fprintf(RE_CML, "%s,%s,%s\n", "Relative error", "CML", "OneMemCML");
    mkDrawData(vec_RECML, vec_RECML_one, RE_CML);

#endif

#ifdef C
    fclose(file_result_C);
    printf("%-*s%-*lf%-*s%-*lf\n",
         15, "DE_C", 15, sumC, 15, "RE_C", 15, rsumC / (N_QUERY - zero));
    fclose(file_result_C_one);
    printf("%-*s%-*lf%-*s%-*lf\n",
         15, "DE_C_one", 15, sumC_one, 15, "RE_C_one", 15, rsumC_one / (N_QUERY - zero));

    FILE *RE_C = fopen("../result/python_draw/RE/RE_C.dat", "w");
    fprintf(RE_C, "%s,%s,%s\n", "Relative error", "C", "OneMemC");
    mkDrawData(vec_REC, vec_REC_one, RE_C);

#endif 

#ifdef PF
    fclose(file_result_PF);
    printf("%-*s%-*lf%-*s%-*lf\n",
         15, "DE_PF", 15, sumPF, 15, "RE_PF", 15, rsumPF / (N_QUERY - zero));
    fclose(file_result_PF_one);
    printf("%-*s%-*lf%-*s%-*lf\n",
         15, "DE_PF_one", 15, sumPF_one, 15, "RE_PF_one", 15, rsumPF_one / (N_QUERY - zero));

    FILE *RE_PF = fopen("../result/python_draw/RE/RE_PF.dat", "w");
    fprintf(RE_PF, "%s,%s,%s\n", "Relative error", "PF", "OneMemPF");
    mkDrawData(vec_REPF, vec_REPF_one, RE_PF);
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
    fclose(file_result_CB_one);
    printf("%-*s%-*lf%-*s%-*lf\n",
         15, "DE_CB_one", 15, sumCB_one, 15, "RE_CB_one", 15, rsumCB_one / (N_QUERY - zero));

    FILE *RE_CB = fopen("../result/python_draw/RE/RE_CB.dat", "w");
    fprintf(RE_CB, "%s,%s,%s\n", "Relative error", "CB", "OneMemCB");
    // fprintf(RE_CB, "%s,%s\n", "Relative error", "CB");
    mkDrawData(vec_RECB, vec_RECB_one, RE_CB);

#endif

    printf("\n");
	return 0;
}
