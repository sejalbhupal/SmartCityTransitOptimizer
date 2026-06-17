#include "FareLookup.h"

FareLookup::FareLookup():entryCount(0){}

void FareLookup::loadDefaultFares(){
    fareTable[0]={2,10};  fareTable[1]={5,20};  fareTable[2]={8,30};
    fareTable[3]={12,40}; fareTable[4]={16,50}; fareTable[5]={20,60};
    fareTable[6]={25,75}; fareTable[7]={30,90}; fareTable[8]={40,110};
    fareTable[9]={50,130};fareTable[10]={999,150};
    entryCount=11;
    cout<<"  [i] Fare table loaded.\n";
}

// BINARY SEARCH - O(log n)
int FareLookup::getFare(int dist){
    if(!entryCount){cout<<"  [!] Fare table empty.\n";return -1;}
    int low=0,high=entryCount-1;
    while(low<=high){
        int mid=low+(high-low)/2;
        if(dist<=fareTable[mid].maxKm){
            if(mid==0||dist>fareTable[mid-1].maxKm) return fareTable[mid].baseFare;
            high=mid-1;
        } else low=mid+1;
    }
    return fareTable[entryCount-1].baseFare;
}

void FareLookup::displayFareTable(){
    cout<<"\n  === Fare Table ===\n";
    int prev=0;
    for(int i=0;i<entryCount;i++){
        if(fareTable[i].maxKm==999)
            cout<<"  Above "<<prev<<" km  -> Rs "<<fareTable[i].baseFare<<"\n";
        else{
            cout<<"  "<<prev+1<<"-"<<fareTable[i].maxKm<<" km -> Rs "<<fareTable[i].baseFare<<"\n";
            prev=fareTable[i].maxKm;
        }
    }
}