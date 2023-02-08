#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    long minutes=seconds/60;
    long Second=seconds%60;
    long Hours=minutes/60;
    minutes=minutes%60;
    string H_S=std::to_string(Hours);
    if(H_S.size()<2){
         H_S+='0';
         H_S[1]=H_S[0];
         H_S[0]='0';
    }
        string M_S=std::to_string(minutes);
    if(M_S.size()<2){
         M_S+='0';
         M_S[1]=M_S[0];
         M_S[0]='0';
    }
        string S_S=std::to_string(Second);
    if(S_S.size()<2){
         S_S+='0';
        S_S[1]=S_S[0];
         S_S[0]='0';
    }
    string ElpTime=H_S+":"+M_S+":"+S_S;
    
    return ElpTime; }