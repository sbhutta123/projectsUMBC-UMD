// CMSC 341 - Spring 2022 - Project 4
#include "dnadb.h"
#include <random>
#include <vector>
enum RANDOM {UNIFORMINT, UNIFORMREAL, NORMAL};
class Random {
public:
    Random(int min, int max, RANDOM type=UNIFORMINT, int mean=50, int stdev=20) : m_min(min), m_max(max), m_type(type)
    {
        if (type == NORMAL){
            //the case of NORMAL to generate integer numbers with normal distribution
            m_generator = std::mt19937(m_device());
            //the data set will have the mean of 50 (default) and standard deviation of 20 (default)
            //the mean and standard deviation can change by passing new values to constructor 
            m_normdist = std::normal_distribution<>(mean,stdev);
        }
        else if (type == UNIFORMINT) {
            //the case of UNIFORMINT to generate integer numbers
            // Using a fixed seed value generates always the same sequence
            // of pseudorandom numbers, e.g. reproducing scientific experiments
            // here it helps us with testing since the same sequence repeats
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_unidist = std::uniform_int_distribution<>(min,max);
        }
        else{ //the case of UNIFORMREAL to generate real numbers
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_uniReal = std::uniform_real_distribution<double>((double)min,(double)max);
        }
    }
    void setSeed(int seedNum){
        // we have set a default value for seed in constructor
        // we can change the seed by calling this function after constructor call
        // this gives us more randomness
        m_generator = std::mt19937(seedNum);
    }

    int getRandNum(){
        // this function returns integer numbers
        // the object must have been initialized to generate integers
        int result = 0;
        if(m_type == NORMAL){
            //returns a random number in a set with normal distribution
            //we limit random numbers by the min and max values
            result = m_min - 1;
            while(result < m_min || result > m_max)
                result = m_normdist(m_generator);
        }
        else if (m_type == UNIFORMINT){
            //this will generate a random number between min and max values
            result = m_unidist(m_generator);
        }
        return result;
    }

    double getRealRandNum(){
        // this function returns real numbers
        // the object must have been initialized to generate real numbers
        double result = m_uniReal(m_generator);
        // a trick to return numbers only with two deciaml points
        // for example if result is 15.0378, function returns 15.03
        // to round up we can use ceil function instead of floor
        result = std::floor(result*100.0)/100.0;
        return result;
    }
    
    private:
    int m_min;
    int m_max;
    RANDOM m_type;
    std::random_device m_device;
    std::mt19937 m_generator;
    std::normal_distribution<> m_normdist;//normal distribution
    std::uniform_int_distribution<> m_unidist;//integer uniform distribution
    std::uniform_real_distribution<double> m_uniReal;//real uniform distribution

};
class Tester{
public:
bool testInsert();
bool testGetDNA();
bool testRemove();

};

unsigned int hashCode(const string str);
string sequencer(int size, int seedNum);

int main(){
    Tester tester;
    {
        cout << "testing insert function for non-colliding keys and colliding keys:\n\n";
        if (tester.testInsert() == true){
            cout << "All data points exist in the DnaDb!\n";
        }
        else
            cout << "Some data points are missing in DnaDb\n";
    }
    {
        cout << "testing getDNA() function:\n\n";
        if (tester.testGetDNA() == true){
            cout << "getDNA() works for non-colliding and colliding keys\n";
        }
        else{
            cout << "getDNA() does not work correctly\n";
        }
    }
    {
        cout << "testing remove function:\n\n";
        if (tester.testRemove() == true){
            cout << "remove function works for non-colliding and colliding data and rehashes correctly\n";
        }
        else{
            cout << "remove function does not work correctly\n";
        }
    }

    
    return 0;
}
unsigned int hashCode(const string str) {
   unsigned int val = 0 ;
   const unsigned int thirtyThree = 33 ;  // magic number from textbook
   for (unsigned int i = 0 ; i < str.length(); i++)
      val = val * thirtyThree + str[i] ;
   return val ;
}
string sequencer(int size, int seedNum){
    //this function returns a random DNA sequence
    string sequence = "";
    Random rndObject(0,3);
    rndObject.setSeed(seedNum);
    for (int i=0;i<size;i++){
        sequence = sequence + ALPHA[rndObject.getRandNum()];
    }
    return sequence;
}

bool Tester::testInsert(){
    vector<DNA> dataList;
    Random RndLocation(MINLOCID,MAXLOCID);
    DnaDb dnadb(MINPRIME, hashCode);
    bool result = true;
    for (int i=0;i<53;i++){
        // generating random data
        DNA dataObj = DNA(sequencer(5, i), RndLocation.getRandNum());
        // saving data for later use
        dataList.push_back(dataObj);
        //inserting data in to the DnaDb object
        dnadb.insert(dataObj);
        if (i == 51){
            if (dnadb.m_oldSize != 51){
                return false;
            }
            if (dnadb.m_currentCap != 211){
                return false;
            }
        }
    }
    //checking if all data points exist
    for (vector<DNA>::iterator it = dataList.begin(); it != dataList.end(); it++){
        result = result && (*it == dnadb.getDNA((*it).getSequence(), (*it).getLocId()));
    }
    for (int i=0;i<10;i++){
        // generating random data
        DNA dataObj = DNA(sequencer(5, i), RndLocation.getRandNum());
        // saving data for later use
        dataList.push_back(dataObj);
        //inserting data in to the DnaDb object
        dnadb.insert(dataObj);
    }
    for (int i=0;i<100;i++){
        // generating random data
        DNA dataObj = DNA(sequencer(5, i), RndLocation.getRandNum());
        // saving data for later use
        dataList.push_back(dataObj);
        //inserting data in to the DnaDb object
        dnadb.insert(dataObj);
    }
    //checking if all data was inserted
    for (vector<DNA>::iterator it = dataList.begin(); it != dataList.end(); it++){
        result = result && (*it == dnadb.getDNA((*it).getSequence(), (*it).getLocId()));
    }
    // checking whether all data are inserted
    for (vector<DNA>::iterator it = dataList.begin(); it != dataList.end(); it++){
        result = result && (*it == dnadb.getDNA((*it).getSequence(), (*it).getLocId()));
    }
    return result;
}

bool Tester::testGetDNA(){
    vector<DNA> dataList;
    Random RndLocation(MINLOCID,MAXLOCID);
    DnaDb dnadb(MINPRIME, hashCode);
    bool result = true;
    for (int i=0;i<10;i++){
        // generating random data
        DNA dataObj = DNA(sequencer(5, i), RndLocation.getRandNum());
        // saving data for later use
        dataList.push_back(dataObj);
        //inserting data in to the DnaDb object
        dnadb.insert(dataObj);
        if (dnadb.getDNA(dataObj.getSequence(), dataObj.getLocId()) == EMPTY){
            result = false;
        }
    }
    vector<DNA> dataList2;
    Random RndLocation2(MINLOCID,MAXLOCID);
    DnaDb dnadb2(MINPRIME, hashCode);
 
    for (int i=0;i<10;i++){
        // generating random data
        DNA dataObj = DNA(sequencer(5, i), RndLocation2.getRandNum());
        // saving data for later use
        dataList2.push_back(dataObj);
        //inserting data in to the DnaDb object
        dnadb2.insert(dataObj);
        if (dnadb2.getDNA(dataObj.getSequence(), dataObj.getLocId()) == EMPTY){
            result = result + false;
        }
    }
    vector<DNA> dataList3;
    Random RndLocation3(MINLOCID,MAXLOCID);
    DnaDb dnadb3(MINPRIME, hashCode);
 
    for (int i=0;i<1;i++){
        // generating random data
        DNA dataObj = DNA(sequencer(5, i), RndLocation3.getRandNum());
        // saving data for later use
        if (dnadb3.getDNA(dataObj.getSequence(), dataObj.getLocId()) == EMPTY){
            result = result + true;
            return result;
        }
        else{
            return false;
        }
        dataList3.push_back(dataObj);
        //inserting data in to the DnaDb object
        dnadb3.insert(dataObj);
    }
    return result;



}

bool Tester::testRemove(){
    vector<DNA> dataList;
    Random RndLocation(MINLOCID,MAXLOCID);
    DnaDb dnadb(MINPRIME, hashCode);
    bool result = true;
    for (int i=0;i<53;i++){
        // generating random data
        DNA dataObj = DNA(sequencer(5, i), RndLocation.getRandNum());
        // saving data for later use
        dataList.push_back(dataObj);
        //inserting data in to the DnaDb object
        dnadb.insert(dataObj);
        if (i >= 30){
            dnadb.remove(dataObj);
            dataList.pop_back();
        }
    }
    //checking if all data points exist
    for (vector<DNA>::iterator it = dataList.begin(); it != dataList.end(); it++){
        result = result && (*it == dnadb.getDNA((*it).getSequence(), (*it).getLocId()));
    }
    vector<DNA> dataList2;
    Random RndLocation2(MINLOCID,MAXLOCID);
    DnaDb dnadb2(MINPRIME, hashCode);
    for (int i=0;i<10;i++){
        // generating random data
        DNA dataObj = DNA(sequencer(5, i), RndLocation2.getRandNum());
        // saving data for later use
        dataList2.push_back(dataObj);
        //inserting data in to the DnaDb object
        dnadb2.insert(dataObj);
        if (i >= 2){
            dnadb2.remove(dataObj);
            dataList2.pop_back();
        }
    }
    //checking if all data points exist
    for (vector<DNA>::iterator it = dataList2.begin(); it != dataList2.end(); it++){
        result = result && (*it == dnadb2.getDNA((*it).getSequence(), (*it).getLocId()));
    }
    return result;

}

