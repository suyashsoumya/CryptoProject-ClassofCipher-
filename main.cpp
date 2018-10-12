//
//  main.cpp
//  TandonProject1
//
//  Created by 1 on 10/8/18.
//  Copyright © 2018 1. All rights reserved.
//

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <algorithm>
typedef std::pair<char,int> PAIR;
std::map<char,int> freq;


int* PattenConstruct(std::string p, char c){
    int* pattern = new int[500];
    
    for(int i =0; i<500; i++){
        if(p[i] == c) pattern[i]=1;
        else pattern[i] = 0;
    }
    return pattern;
}
int Analyze(std::string p, char c, int freq, int* cipher, int length){
    int* pattern;
    std::vector<int> uniqcipher; // this vector contains the number of unique cipher number in certain place
    pattern = PattenConstruct(p, c);
    for(int i=0; i<length;i++){
        if(pattern[i] == 1){ // if this place in plaintext is the character c
            int value = cipher[i];
            std::vector<int>::iterator it;
            it = find(uniqcipher.begin(),uniqcipher.end(),value);
            
            if (it!=uniqcipher.end())
            {
                //repeated number
            }
            else
            {
                //new number record it
                uniqcipher.push_back(value);
            }
        }
    } // end for
    delete[] pattern;
    if (uniqcipher.size() <= freq) return 1; // we return 1 to raise the score
    else return 0; // we return 0 because it doesn't match
    
}
bool checkLimit(std::vector<std::map<char,std::vector<int>>> limittable){
    std::map<char,int>::iterator it;
    
    for(it = freq.begin();it!=freq.end();it++){
        if(limittable[it->first].size() > it->second ){
            return false;
        }
    }
    return true;
}

bool RecursiveTest2(int* cipher, int length, std::vector<std::string> plaintexts, bool denied, std::vector<std::map<char,std::vector<int>>> limittable){// denied should be 0)

 
    
    if (length <= 0 || denied  == 1) return 0;
    for(int i =0; i<plaintexts.size();i++){
        std::string plaintext = plaintexts[i]; // extract the string
        for(int j=0;j<=plaintext.length();j++){
            if (j>= length) {denied = true; break;}; // get out if we reach the end
            std::vector<std::map<char,std::vector<int>>>::iterator it;
            if(j==plaintext.length()){
                for(it = limittable.begin(); it!=limittable.end();it++){
                    
                    if(it->begin()->first == ' '){
                        // insert unique cipher or repeated just ignore
                        std::vector<int>::iterator iterforvec; // iterator for vector<int>
                        iterforvec = find(it->begin()->second.begin(),it->begin()->second.end(),cipher[j]); // compare to the current cipher
                        if(iterforvec == it->begin()->second.end()){
                            it->begin()->second.push_back(cipher[j]) ;//insert unique cipher
                            // should test in here
                        }
                    }
                }
            }
            else {
            
                for(it = limittable.begin(); it!=limittable.end();it++){
                
                    if(it->begin()->first == plaintext[j]){
                        // insert unique cipher or repeated just ignore
                        std::vector<int>::iterator iterforvec; // iterator for vector<int>
                        iterforvec = find(it->begin()->second.begin(),it->begin()->second.end(),cipher[j]); // compare to the current cipher
                        if(iterforvec == it->begin()->second.end()){
                            it->begin()->second.push_back(cipher[j]) ;//insert unique cipher
                        // should test in here
                            }
                        }
                }
            }
        }
        // now check if any character break the limit
        if(!denied) denied = !checkLimit(limittable);
        
        //now recursive call the function
        if (!denied){
            length = length-plaintext.length()+1;
            cipher = cipher+plaintext.length()+1;
            if(!RecursiveTest2(cipher, length, plaintexts, denied, limittable)) std::cout<<plaintext<<' ';
        }else{
            if (length-plaintext.length() <=0 ){
                std::cout<<plaintext<<' ';
                return denied;
            }
        }
        
        
    }
                   return denied;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    // PARAMETER SETTING
    std::string p[5];
    p[0] = "dipped ligatured cannier cohabitation cuddling coiffeuses pursuance roper eternizes nullo framable paddlings femur bebop demonstrational tuberculoid theocracy women reappraise oblongatae aphasias loftiness consumptive lip neurasthenically dutchmen grift discredited resourcefulness malfeasants swallowed jogger sayable lewder editorials demimondaine tzaritza arrogations wish indisputable reproduces hygrometries gamuts alight borderlines draggle reconsolidated anemometer rowels staggerers grands nu";
    
    p[1] = "rereads predestines equippers cavitation bimolecular lucubrations cabin bettas quiverer prussians cosigner dressier bended dethronement inveigled davenport establish ganges rebroadcast supered bastiles willable abetted motionlessness demonic flatter bunyan securely tippiest tongue aw cotyledonal roomettes underlies miffs inducement overintellectually fertilize spasmodic bacchanal birdbrains decoct snakebite galliard boson headmistress unextended provence weakling pirana fiend lairds argils comma";
    
    p[2]= "trawling responsiveness tastiest pulsed restamps telescoping pneuma lampoonist divas theosophists pustules checkrowed compactor conditionals envy hairball footslogs wasteful conjures deadfall stagnantly procure barked balmier bowery vagary beaten capitalized undersized towpath envisages thermoplastic rationalizers professions workbench underarm trudger icicled incisive oilbirds citrins chambrays ungainliness weazands prehardened dims determinants fishskin cleanable henceforward misarranges fine";

    p[3] = "dean iller playbooks resource anesthetic credibilities nonplus tzetzes incursions stooged envelopments girdling risibility thrum repeaters catheterizing misbestowed cursing malingerers ensconces lippiest accost superannuate slush opinionated rememberer councils mishandling drivels juryless slashers tangent roistering scathing apprenticing fleabite sault achier quantize registrable nobbler sheaf natantly kashmirs dittoes scanned emissivity iodize dually refunded portliest setbacks eureka needines";
    
    p[4] = "mammate punners octette asylum nonclinically trotters slant collocation cardiology enchants ledge deregulated bottommost capsulate biotechnologies subtended cloddiest training joneses catafalque fieldmice hostels affect shrimper differentiations metacarpus amebas sweeter shiatsu oncoming tubeless menu professing apostatizing moreover eumorphic casked euphemistically programmability campaniles chickpea inactivates crossing defoggers reassures tableland doze reassembled striate precocious noncomba";
    
    //std::map<char,int> freq;
    freq.insert(PAIR(' ',19));
    freq.insert(PAIR('a',7));
    freq.insert(PAIR('b',1));
    freq.insert(PAIR('c',2));
    freq.insert(PAIR('d',4));
    freq.insert(PAIR('e',10));
    freq.insert(PAIR('f',2));
    freq.insert(PAIR('g',2));
    freq.insert(PAIR('h',5));
    freq.insert(PAIR('i',6));
    freq.insert(PAIR('j',1));
    freq.insert(PAIR('k',1));
    freq.insert(PAIR('l',3));
    freq.insert(PAIR('m',2));
    freq.insert(PAIR('n',6));
    freq.insert(PAIR('o',6));
    freq.insert(PAIR('p',2));
    freq.insert(PAIR('q',1));
    freq.insert(PAIR('r',5));
    freq.insert(PAIR('s',5));
    freq.insert(PAIR('t',7));
    freq.insert(PAIR('u',2));
    freq.insert(PAIR('v',1));
    freq.insert(PAIR('w',2));
    freq.insert(PAIR('x',1));
    freq.insert(PAIR('y',2));
    freq.insert(PAIR('z',1));
    
    //PARAMETER SETTING OVER
    
    // Get input file
    std::ifstream ciphertextFile("Test1-ciphertext.txt");
    // Check if file can be opened
    if (!ciphertextFile) {
        std::cerr << "File failed to open\n";
        exit(1);
    }
    /// construct an array of string that contains all plaintext words
    //insert code std::string plaintexts[70]
    ///
    int cipher[500];
    int index = 0;
    char c;
    std::string cipherChar;
    while (ciphertextFile >> c) {
        if (c == ',') {
            cipher[index] = std::stoi(cipherChar);
            ++index;
            cipherChar = "";
            
        }
        else {
            cipherChar += c;
        }
    }
    cipher[index] = std::stoi(cipherChar);
    ciphertextFile.close();
    
    
    // decrypt process below.... TEST1
    int score[5];
    for(int i =0 ; i<5 ;i++){
        score[i] = 0;
    std::map<char, int>::iterator iter;
    for(iter = freq.begin(); iter != freq.end(); iter++)
    {
        score[i]+= Analyze(p[i], iter->first, iter->second, cipher, 500);
    }
    }
    int correct = 0;
    int max = 0;
    for(int i = 0; i<5;i++){
        if( max <= score[i]){
            
            max = score[i];
            correct = i;
        }
    }
    std::cout<<"the correct one is "<<p[correct];
    
    // TEST 2
    int length = 500;
    std::map<char, int>::iterator iter;
    std::vector<std::map<char,std::vector<int>>> limittable;        // array of map, map is one char mapped to an an array of unique cipher
    for(iter = freq.begin(); iter != freq.end(); iter++)
    {
        std::map<char,std::vector<int>> temp;
        std::vector<int> inttemp;
        char chartemp = iter->first;// would store unique cipher number associated with the char
        temp.insert(std::make_pair(chartemp, inttemp));
                    limittable.push_back(temp);
    }
        
        std::cout << "Hello, World!\n";
    return 0;
}
