#include "ScheduleSorter.h"
#include <algorithm>
using namespace std;

ScheduleSorter::ScheduleSorter():count(0){}

void ScheduleSorter::addBus(int id,string route,int time,int platform,int seats){
    if(count>=MAX_BUSES){cout<<"  [!] Schedule full.\n";return;}
    schedule[count++]={id,route,time,platform,seats};
}

void ScheduleSorter::merge(BusSchedule arr[],int l,int m,int r){
    int n1=m-l+1,n2=r-m;
    BusSchedule L[MAX_BUSES],R[MAX_BUSES];
    for(int i=0;i<n1;i++)L[i]=arr[l+i];
    for(int j=0;j<n2;j++)R[j]=arr[m+1+j];
    int i=0,j=0,k=l;
    while(i<n1&&j<n2){
        if(L[i].arrivalTime<=R[j].arrivalTime) arr[k++]=L[i++];
        else arr[k++]=R[j++];
    }
    while(i<n1)arr[k++]=L[i++];
    while(j<n2)arr[k++]=R[j++];
}

void ScheduleSorter::mergeSort(BusSchedule arr[],int l,int r){
    if(l>=r)return;
    int m=l+(r-l)/2;
    mergeSort(arr,l,m);
    mergeSort(arr,m+1,r);
    merge(arr,l,m,r);
}

void ScheduleSorter::sortByArrival(){
    if(!count){cout<<"  [!] No buses.\n";return;}
    mergeSort(schedule,0,count-1);
    cout<<"  [+] Sorted by arrival time (Merge Sort).\n";
}

void ScheduleSorter::sortBySeats(){
    if(!count)return;
    sort(schedule,schedule+count,[](const BusSchedule&a,const BusSchedule&b){
        return a.seatsAvailable>b.seatsAvailable;
    });
    cout<<"  [+] Sorted by seats (STL sort + lambda).\n";
}

string ScheduleSorter::formatTime(int t){
    int h=t/100,m=t%100;
    string hh=(h<10?"0":"")+to_string(h);
    string mm=(m<10?"0":"")+to_string(m);
    return hh+":"+mm;
}

void ScheduleSorter::displaySchedule(){
    if(!count){cout<<"  [i] Schedule empty.\n";return;}
    cout<<"\n  Bus  | Route                | Time  | Plat | Seats\n";
    cout<<"  ─────────────────────────────────────────────────────\n";
    for(int i=0;i<count;i++){
        BusSchedule& b=schedule[i];
        string r=b.routeName; while(r.length()<20)r+=" ";
        cout<<"  "<<b.busID<<" | "<<r<<" | "<<formatTime(b.arrivalTime)
            <<"  |   "<<b.platform<<"  | "<<b.seatsAvailable<<"\n";
    }
}

void ScheduleSorter::loadSampleSchedule(){
    addBus(101,"Nagpur-Wardha",    1430,1,42);
    addBus(102,"Nagpur-Amravati",   900,2,18);
    addBus(103,"Nagpur-Chandrapur",1200,1,55);
    addBus(104,"Nagpur-Yavatmal",  1615,3,30);
    addBus(105,"Nagpur-Bramhapuri", 730,2, 8);
    addBus(106,"Nagpur-Bhandara",  1100,4,60);
    addBus(107,"Nagpur-Gondia",    1330,1,22);
    cout<<"  [i] Sample schedule loaded ("<<count<<" buses).\n";
}

int ScheduleSorter::getCount(){return count;}