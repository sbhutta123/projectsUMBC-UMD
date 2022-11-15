/**********************
File: Sequencer.cpp
Project: CMSC 202 Project 3, Spring 2021
Author: Shifa Bhutta
Date: 4/3/21
Section: 30/35
E-mail: shifab1@umbc.edu

This file implements every function from "Sequencer.h" and controls the vectors tht hold DNA* objects. It also controls the gameplay like the main menu and diplaying,reversing,and comparing sequences
 *********************/

#include "Sequencer.h"
Sequencer::Sequencer(string fileName) {
  //calls ReadFile and MainMenu and stores file name
  m_fileName = fileName;
  Sequencer::ReadFile();
  Sequencer::MainMenu();
}
Sequencer::~Sequencer(){
  //clears vectors and deletes DNA* objects
  int sizeSus = m_suspects.size();
  int sizeEv = m_evidence.size();
  for (int i = 0; i < sizeSus; i++){
    delete m_suspects.at(i);
  }
  for (int i = 0; i < sizeEv; i++){
    delete m_evidence.at(i);
  }
  m_suspects.clear();
  m_evidence.clear();
  m_fileName = "";
}
void Sequencer::DisplayStrands(){
  int evSize = m_evidence.size();
  int susSize = m_suspects.size();
  //iterates through both vectors displaying and displays DNA objects
  for (int i = 0; i < susSize; i++){
    cout << *m_suspects.at(i);
    cout << '\n';
  }
  for (int i = 0; i < evSize; i++){
    cout << *m_evidence.at(i);
    cout << '\n';
  }
}
void Sequencer::ReadFile(){
  string name;
  string namechar;
  int size = 0;
  ifstream infile(m_fileName);
  //checks if file is open
  if (infile.is_open()){
    while(getline(infile,name)){
      //checks if strand belongs to a suspect
      if (name[0] == 'S'){
	//stores name of strand
	DNA *obj = new DNA(name);
	getline(infile,name);
	size = name.length();
	//iterates through strand and stores every char in the object
	for (int i = 0; i < size; i++){
	  if (name[i] != ','){
	    obj->InsertEnd(name[i]);
	  }
	}
	//adds object to m_suspects
	m_suspects.push_back(obj);
	}
      //checks if strand belongs to evidence
      if (name[0] == 'E') {
	//stores name of strand
	DNA *obj = new DNA(name);
	getline(infile, name);
	size = name.length();
	//iterates through strand and stores every char in the object
	for (int i = 0; i < size; i++){
	  if (name[i] != ','){
	    obj->InsertEnd(name[i]);
	  }
	}
	//adds object to to m_evidence
	m_evidence.push_back(obj);
      }
    }
    //closes file
    infile.close();
    int sizeSus = m_suspects.size();
    int sizeEv = m_evidence.size();
    int quantStrands = sizeSus + sizeEv;
    cout << "Opened file " << '\n' << quantStrands << " strands loaded" << endl;
  }
}
void Sequencer::MainMenu(){
  int choice = 0;
  //asks user what they want to do and stores it in choice
  cout << "What would you like to do? " << '\n' << "1. Display Strands" << '\n' << "2. Reverse Sequence " << '\n' << "3. Check Suspects " <<'\n' << "4. Exit" << '\n';
  cin >> choice;
  //checks validity of answer given
  while ((choice < 1) || (choice > 4)){
    cout << "Please enter a valid number " << '\n';
    cin >> choice;
  }
  while ((1 <= choice) && (choice < 4)){
    //displays strand if user chose 1
    if (choice == 1){
	Sequencer::DisplayStrands();
    }
    //reverses sequence if user chose 2
    if (choice == 2){
      Sequencer::ReverseSequence();
    }
    //checks suspects (compares sequences of all strands) if user chose 3
    if (choice == 3){
      Sequencer::CheckSuspects();
    }
    //prompts user again 
    cout << "What would you like to do? " << '\n' << "1. Display Strands" << '\n' << "2. Reverse Sequence " << '\n' << "3. Check Suspects" <<'\n' << "4. Exit" << '\n';
    cin >> choice;
    //checks validity of answer
    while ((choice < 1) || (choice > 4)){
      cout << "Please enter a valid number " << '\n';
      cin >> choice;
    }
  }
  //ends game if chose 4
  if (choice == 4){
    cout << "Thanks for playing!" << endl;
  }     
}
void Sequencer::CheckSuspects() {
   int count = 0;
   int sizeSus = m_suspects.size();
   int sizeEv = m_evidence.size();
   bool trueFalse;
   //iterates through all sequences to see if they match, and keeps track of how many evidence strands match with a suspect strand
   for (int i = 0; i < sizeSus; i++){
     for (int j = 0; j < sizeEv; j++){
       trueFalse = m_suspects.at(i)->CompareSequence(*m_evidence.at(j));
       if (trueFalse == true){
	 cout << m_suspects.at(i)->GetName() << " matches " << m_evidence.at(j)->GetName() << endl;
	 count++;
       }
       if (trueFalse == false){
	 cout << m_suspects.at(i)->GetName() << " does NOT match " << m_evidence.at(j)->GetName() << endl;
       }
     }
     if (count == sizeEv){
       cout << m_suspects.at(i)->GetName() << " matches for ALL Evidence" << endl;
       count = 0;
     }
   }
}
void Sequencer::ReverseSequence(){
  int choice = 0;
  int sizeSus = m_suspects.size();
  int sizeEv = m_evidence.size();
  int count = 1;
  int choiceEv = 0;
  int choiceSus = 0;
  //asks user which strand they would like to reverse
  while((choice != 1) && (choice != 2)) {
    cout << "Which type of sequence to reverse? " << '\n' << "1. Suspect " << '\n' << "2. Evidence " << '\n';
    cin >> choice;
    //checks validity of answer
    if ((choice != 1) && (choice != 2)){
      cout << "That input is invalid " << endl;
    }
  }
  //if 2, and there are multiple evidence strands, then it prompts user on which strand they want to reverse and then reverses that strand
  if ((choice == 2) && (sizeEv > 1)){
    for (int i = 0; i < sizeEv; i++){
      cout << count << ". " << m_evidence.at(i)->GetName() << '\n';
      count++;
    }
    cin >> choiceEv;
    if ((choiceEv > 0) && (choiceEv <= sizeEv)){
      m_evidence.at(choiceEv - 1)->ReverseSequence();
      cout << "Done reversing " << m_evidence.at(choiceEv - 1)->GetName() << "'s sequence." << endl; 
    }
    if ((choiceEv < 1) || (choiceEv > sizeEv)){
      while((choiceEv < 1) || (choiceEv > sizeEv)){
	cout << "Please enter a valid input" << '\n';
	cin >> choiceEv;
      }
      m_evidence.at(choiceEv - 1)->ReverseSequence();
      cout << "Done reversing " << m_evidence.at(choiceEv - 1)->GetName() << "'s " << "sequence." << endl;
    }
  }
  //if 1, and there are multiple suspect strands, then it prompts the user on which strand they would like to reverse. Then, it checks the validity of their answer and reverses strand they chose 
  if ((choice == 1) && (sizeSus > 1)){
    for (int i = 0; i < sizeSus; i++){
      cout << count << ". " << m_suspects.at(i)->GetName() << '\n';
      count ++;
    }
    cin >> choiceSus;
    if ((choiceSus > 0) && (choiceSus <= sizeSus)){
      m_suspects.at(choiceSus - 1)->ReverseSequence();
      cout << "Done reversing " << m_suspects.at(choiceSus - 1)->GetName() << "'s sequence. " << endl;
    }
    if ((choiceSus < 1) || (choiceSus > sizeSus)){
      while((choiceSus < 1) || (choiceSus > sizeSus)){
	cout << "Please enter a valid input" << '\n';
	cin >> choiceSus;
      }
      m_suspects.at(choiceSus - 1)->ReverseSequence();
      cout << "Done reversing " << m_suspects.at(choiceSus - 1)->GetName() << "'s sequence. " << endl;
    }
  }
  //if there is only one strand of evidence or suspect, then it reverses that one
  if ((choice == 1) && (sizeSus == 1)){
    m_suspects.at(sizeSus - 1)->ReverseSequence();
    cout << "Done reversing " << m_suspects.at(sizeSus - 1)->GetName() << "'s sequence. " << endl;
  }
  if ((choice == 2) && (sizeEv == 1)){
    m_evidence.at(sizeEv - 1)->ReverseSequence();
    cout << "Done reversing " << m_evidence.at(sizeEv - 1)->GetName() << "'s sequence. " << endl;
  }
}
   
