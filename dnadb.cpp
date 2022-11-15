// CMSC 341 - Spring 2022 - Project 4
#include "dnadb.h"
DnaDb::DnaDb(int size, hash_fn hash){
    //sets size of current table
    if (size > MAXPRIME){
        m_currentCap = MAXPRIME;
    }
    else if (size < MINPRIME){
        m_currentCap = MINPRIME;
    }
    else if (isPrime(size) == false){
        m_currentCap = findNextPrime(size);
    }
    else{
        m_currentCap = size;
    }
    //initializes variables
    m_hash = hash;
    m_currentTable = new DNA[m_currentCap];
    m_oldTable = nullptr;     
    m_empty = true;
    m_times = 0;
    m_currentSize = 0;
    m_oldSize = 0;
    m_currNumDeleted = 0;
    m_oldNumDeleted = 0;
    m_oldCap = 0;
}
DnaDb::~DnaDb(){
    //deconstructor
    delete [] m_currentTable;
    delete [] m_oldTable;
}

bool DnaDb::insert(DNA dna){
    //cout << "im here" << endl;
    bool result = false;
    //checks for duplicates
    for (unsigned int i = 0; i < m_currentCap; i++){
        if (m_currentTable[i].m_sequence == dna.m_sequence && m_currentTable[i].m_location == dna.m_location){
            return result;
        }
    }
    //checks if index is empty or deleted (available for insertion)
    unsigned int index = (m_hash(dna.m_sequence)) % m_currentCap;
    if (m_currentTable[index] == EMPTY || m_currentTable[index] == DELETED){
        //increases size if adding something new to table
        if (m_currentTable[index] == EMPTY){
            m_currentSize++;
        }
        //puts object in the table
        m_currentTable[index] = dna;
        //checks if table needs rehashing
        if (lambda() > .5 && m_empty == true){
            //sets size of new table
            int size = (m_currentSize - m_currNumDeleted) * 4;
            if (isPrime(size) == false){
                size = findNextPrime(size);
            }
            //creates new table and swaps values
            m_oldTable = new DNA[size];
            swap(m_oldTable, m_currentTable);
            m_oldCap = m_currentCap;
            m_currentCap = size;
            m_oldSize = m_currentSize;
            m_currentSize = 0;
            m_oldNumDeleted = m_currNumDeleted;
            m_currNumDeleted = 0;
            m_empty = false;
            m_times++;
            int count = m_oldSize / 4;
            count = count * m_times;
            m_oldTable = rehash(m_oldTable, count);
        }
        //checks if rehashing is in progress
        if (m_empty == false && (findDNA(m_oldTable,dna.m_sequence, dna.m_location, m_oldCap) == EMPTY)){
            m_times++;
            //rehashes all data incrementally and deletes table if necessary
            if (m_times <= 3){
                int count = m_oldSize / 4;
                count = count * m_times;
                m_oldTable = rehash(m_oldTable, count);
                int deletes = 0;
                for (unsigned int i = 0; i < m_oldCap; i++){
                    bool empty = false;
                    if (m_oldTable[i] == DELETED || m_oldTable[i] == EMPTY){
                        empty = true;
                    }
                    if (empty == false){
                        deletes++;
                    }
                }
                if (deletes == 0){
                    delete [] m_oldTable;
                    m_oldTable = nullptr;
                    m_empty = true;
                    m_times = 0;
                    m_oldSize = 0;
                    m_oldCap = 0;
                    m_oldNumDeleted = 0;
                }
            }
            //if 4th time incrementing, moves rest of data into m_currentTable and then deletes m_oldTable
            if (m_times == 4){
                for (unsigned int i = 0; i < m_oldCap; i++){
                    bool empty = false;
                    if (m_oldTable[i] == DELETED || m_oldTable[i] == EMPTY){
                        empty = true;
                    }
                    if (empty == false){
                        insert(m_oldTable[i]);
                        m_oldTable[i] = DELETED;
                    }
                } 
                delete [] m_oldTable;
                m_oldTable = nullptr;
                m_empty = true;
                m_times = 0;
                m_oldSize = 0;
                m_oldCap = 0;
                m_oldNumDeleted = 0;
            }
        }
        return true;

    }
    else{
        //does quadratic probing if necessary
        for (unsigned int i = 0; i < m_currentCap; i++){
            index = ((m_hash(dna.m_sequence) % m_currentCap) + (i * i)) % m_currentCap;
            //if index is available for insertion, inserts it
            if (m_currentTable[index] == EMPTY || m_currentTable[index] == DELETED){
                 if (m_currentTable[index] == EMPTY){
                    m_currentSize++;
                }
                m_currentTable[index] = dna;
                //checks is table needs to be rehashed
                if (lambda() > .5 && m_empty == true){
                    //finds size of new table
                    int size = (m_currentSize - m_currNumDeleted) * 4;
                    if (isPrime(size) == false){
                        size = findNextPrime(size);
                    }
                    //creates new table and swaps all values
                    m_oldTable = new DNA[size];
                    swap(m_oldTable, m_currentTable);
                    m_oldCap = m_currentCap;
                    m_currentCap = size;
                    m_oldSize = m_currentSize;
                    m_currentSize = 0;
                    m_oldNumDeleted = m_currNumDeleted;
                    m_currNumDeleted = 0;
                    m_empty = false;
                    m_times++;
                    int count = m_oldSize / 4;
                    count = count * m_times;
                    m_oldTable = rehash(m_oldTable, count);
                }
                //checks if rehashing is in progress
                if (m_empty == false && (findDNA(m_oldTable,dna.m_sequence, dna.m_location, m_oldCap) == EMPTY)){
                    m_times++;
                    //rehashes incrementally and checks if table needs to be deleted 
                    if (m_times <= 3){
                        int count = m_oldSize / 4;
                        count = count * m_times;
                        m_oldTable = rehash(m_oldTable, count);
                        int deletes = 0;
                        for (unsigned int i = 0; i < m_oldCap; i++){
                            bool empty = false;
                            if (m_oldTable[i] == DELETED || m_oldTable[i] == EMPTY){
                                empty = true;
                            }
                            if (empty == false){
                                deletes++;
                            }
                        }
                        if (deletes == 0){
                            delete [] m_oldTable;
                            m_oldTable = nullptr;
                            m_empty = true;
                            m_times = 0;
                        }
                    }
                    //transfers all remaining data over and then deletes table
                    if (m_times == 4){
                        for (unsigned int i = 0; i < m_oldCap; i++){
                            bool empty = false;
                            if (m_oldTable[i] == DELETED || m_oldTable[i] == EMPTY){
                                empty = true;
                            }
                            if (empty == false){
                                insert(m_oldTable[i]);
                                m_oldTable[i] = DELETED;
                            }
                        }
                        delete [] m_oldTable;
                        m_oldTable = nullptr;
                        m_empty = true;
                        m_times = 0;
                        m_oldSize = 0;
                        m_oldCap = 0;
                        m_oldNumDeleted = 0;
                    }
                }
                return true;
            }
        }

    }
    return false;
}
DNA DnaDb::findDNA (DNA*table, string sequence, int location, unsigned int oldCap){
    //traverses through m_oldTable to see if value exists
    for (unsigned int i = 0; i < oldCap; i++){
        if (table[i].getSequence() == sequence && table[i].getLocId() == location){
            return table[i];
        }
    }
    return EMPTY;
}

DNA* DnaDb::rehash(DNA* table, int amountTimes){
    int count = 0;
    int index = 0;
    //finds data in table and if deleted, adds one, and if live data, then inserts into m_currentTable and accounts for that data
    //runs till count is m_times * (m_oldSize/4)
    while (count < amountTimes){
        bool empty = false;
        bool deleted = false;
        //if deleted add one to count and deleted = true
        if (table[index] == DELETED){
            count++;
            deleted = true;
        }
        //if empty, make note that empty
        else if (table[index] == EMPTY){
            empty = true;
        }
        //if live data, insert and count++
        else if (!deleted && !empty){
            DNA temp = DNA(table[index].getSequence(), table[index].getLocId());
            insert(temp);
            count++;
            table[index] = DELETED;
            m_oldNumDeleted++;
        }
        index++;
    }
    //returns m_oldTable
    return m_oldTable;
}

bool DnaDb::remove(DNA dna){
    //checks if object passed in is valid to remove
    if (getDNA(dna.m_sequence, dna.m_location) == EMPTY){
        return false;
    }
    else if (dna == EMPTY || dna == DELETED){
        return false;
    }
    else{
        unsigned int index = 0;
        //finds object through quadratic probing
        for (unsigned int i = 0; i < m_currentCap; i++){
            index = ((m_hash(dna.m_sequence) % m_currentCap) + (i * i)) % m_currentCap;
            if (m_currentTable[index] == dna){
                m_currentTable[index] = DELETED;
                m_currNumDeleted++;
            }
        }
        //checks if removal is taking place in oldtable
        if (m_empty == false){
            for (unsigned int i = 0; i < m_oldCap; i++){
                index = ((m_hash(dna.m_sequence) % m_oldCap) + (i * i)) % m_oldCap;
                if (m_oldTable[index] == dna){
                    m_oldTable[index] = DELETED;
                    m_oldNumDeleted++;
                }
            }
        }
        //checks if table is to be rehashed
        if (deletedRatio() > .8 && m_empty == true){
            //finds size of new table
            int size = (m_currentSize - m_currNumDeleted) * 4;
            if (isPrime(size) == false){
                size = findNextPrime(size);
            }
            //creates new table and swaps values of tables
            m_oldTable = new DNA[size];
            swap(m_oldTable, m_currentTable);
            m_oldCap = m_currentCap;
            m_currentCap = size;
            m_oldSize = m_currentSize;
            m_currentSize = 0;
            m_oldNumDeleted = m_currNumDeleted;
            m_currNumDeleted = 0;
            m_empty = false;
            m_times++;
            int count = m_oldSize / 4;
            count = count * m_times;
            m_oldTable = rehash(m_oldTable, count);
        }
        //checks if rehashing is in progress
        if (m_empty == false && (findDNA(m_oldTable,dna.m_sequence, dna.m_location, m_oldCap) == EMPTY)){
            m_times++;
            //rehashes and then checks if table should be deleted
            if (m_times <= 3){
                int count = m_oldSize / 4;
                count = count * m_times;
                m_oldTable = rehash(m_oldTable, count);
                int deletes = 0;
                for (unsigned int i = 0; i < m_oldCap; i++){
                    bool empty = false;
                    if (m_oldTable[i] == DELETED || m_oldTable[i] == EMPTY){
                        empty = true;
                    }
                    if (empty == false){
                        deletes++;
                    }
                }
                if (deletes == 0){
                    delete [] m_oldTable;
                    m_oldTable = nullptr;
                    m_empty = true;
                    m_times = 0;
                    m_oldSize = 0;
                    m_oldCap = 0;
                    m_oldNumDeleted = 0;
                }
            }
            //if 4th time rehashing, transfers rest of data and then deletes m_oldTable
            if (m_times == 4){
                for (unsigned int i = 0; i < m_oldCap; i++){
                    bool empty = false;
                    if (m_oldTable[i] == DELETED || m_oldTable[i] == EMPTY){
                        empty = true;
                    }
                    if (empty == false){
                        insert(m_oldTable[i]);
                        m_oldTable[i] = DELETED;
                    }
                }
                delete [] m_oldTable;
                m_oldTable = nullptr;
                m_empty = true;
                m_times = 0;
                m_oldSize = 0;
                m_oldCap = 0;
                m_oldNumDeleted = 0;
            }
        }
        return true;
    }
    return false;
}

DNA DnaDb::getDNA(string sequence, int location){
    //sees if data exists in either old table or current table
    if (sequence != DELETEDKEY){
        for (unsigned int i = 0; i < m_currentCap; i++){
            if (m_currentTable[i].m_sequence == sequence && m_currentTable[i].m_location == location){
                return m_currentTable[i];
            }
        }
        for (unsigned int i = 0; i < m_oldCap; i++){
            if (m_oldTable[i].m_sequence == sequence && m_oldTable[i].m_location == location){
                return m_oldTable[i];
            }
        }
    }
    return EMPTY;
}


float DnaDb::lambda() const {
    //load factor
    float ratio = (float) m_currentSize / m_currentCap; 
    return ratio;
}

float DnaDb::deletedRatio() const {
    //deleted Ratio
    float ratio = (float) m_currNumDeleted / m_currentSize; 
    return ratio;
}

void DnaDb::dump() const {
    cout << "Dump for current table: " << endl;
    if (m_currentTable != nullptr)
        for (unsigned int i = 0; i < m_currentCap; i++) {
            cout << "[" << i << "] : " << m_currentTable[i] << endl;
        }
    cout << "Dump for old table: " << endl;
    if (m_oldTable != nullptr)
        for (unsigned int i = 0; i < m_oldCap; i++) {
            cout << "[" << i << "] : " << m_oldTable[i] << endl;
        }
}

bool DnaDb::isPrime(int number){
    bool result = true;
    for (int i = 2; i <= number / 2; ++i) {
        if (number % i == 0) {
            result = false;
            break;
        }
    }
    return result;
}

int DnaDb::findNextPrime(int current){
    //we always stay within the range [MINPRIME-MAXPRIME]
    //the smallest prime starts at MINPRIME
    if (current < MINPRIME) current = MINPRIME-1;
    for (int i=current; i<MAXPRIME; i++) { 
        for (int j=2; j*j<=i; j++) {
            if (i % j == 0) 
                break;
            else if (j+1 > sqrt(i) && i != current) {
                return i;
            }
        }
    }
    //if a user tries to go over MAXPRIME
    return MAXPRIME;
}

DNA::DNA(string sequence, int location) {
    if ((location >= MINLOCID && location <= MAXLOCID) ||
        (location == 0 && sequence == "DELETED")){
        // this is a normal or a DELETED object
        m_sequence = sequence;
        m_location = location;
    }
    else{
        // this is the empty object
        m_sequence = "";
        m_location = 0;
    }
}

string DNA::getSequence() const {
    return m_sequence;
}

int DNA::getLocId() const {
    return m_location;
}

// Overloaded assignment operator
const DNA& DNA::operator=(const DNA& rhs){
    if (this != &rhs){
        m_sequence = rhs.m_sequence;
        m_location = rhs.m_location;
    }
    return *this;
}

// Overloaded insertion operator.  Prints DNA's sequence (key),
// and the location ID. This is a friend function in DNA class.
ostream& operator<<(ostream& sout, const DNA &dna ) {
    if (!dna.m_sequence.empty())
        sout << dna.m_sequence << " (Location ID " << dna.m_location << ")";
    else
        sout << "";
  return sout;
}

// Overloaded equality operator. This is a friend function in DNA class.
// To test inequality we may negate the results of this operator.
bool operator==(const DNA& lhs, const DNA& rhs){
    return ((lhs.m_sequence == rhs.m_sequence) && (lhs.m_location == rhs.m_location));
}
