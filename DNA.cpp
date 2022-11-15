/**************
File: DNA.cpp
Project: CMSC 202 Project 3,Spring 2021
Author: Shifa Bhutta
Date: 4/2/21
Section: 30/35
E-mail: shifab1@umbc.edu

This file implements every function in "DNA.h" and controls the nodes in the DNA objects by utilizing linked lists
***************/

#include "DNA.h"
DNA::DNA() {
  //holds member variables values
  m_name = "";
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
}
DNA::DNA(string name) {
  //overloaded constructor that contains name
  m_name = name;
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
}
DNA::~DNA() {
  //deconstructs nodes in DNA objects
  if (m_size > 0) {
    Node *curr = m_head;
    while (curr != nullptr) {
      m_head = curr;
      curr = curr->m_next;
      delete m_head;
    }
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
  }
}
void DNA::InsertEnd(char data) {
  Node *temp = new Node();
  Node *curr = m_head;
  temp->m_next = nullptr;
  temp->m_data = data;
  m_size ++;
  //if list is emppty, it makes m_head = temp
  if (m_head == nullptr) {
    m_head = temp;
  }
  //if list is not empty, it iterates thorugh linked list to find the end of the list and then inserts value
  else{
    while(curr->m_next != nullptr) {
      curr = curr->m_next;
    }
    curr->m_next = temp;
  }
}
string DNA::GetName(){
  //getter for m_name
  return m_name;
}
int DNA::GetSize(){
  //getter for m_size
  return m_size;
}
void DNA::ReverseSequence() {
  Node *curr = m_head;
  Node *prev = nullptr;
  Node *next = nullptr;
  int counter = 0;
  //iterates through linked list and reverses values
  while (counter < m_size) {
    while (curr != nullptr) {
    next = curr->m_next;
    curr->m_next = prev;
    prev = curr;
    curr = next;
    }
    counter ++;
  }
  //updates m_head and m_tail
  m_head = prev;
  m_tail = curr;
}
bool DNA::CompareSequence(DNA &evidence) {
  Node *curr = m_head;
  Node *currEv = evidence.m_head;
  int index = -1;
  int indexEv = -1;
  int count = 0;
  int counter = 0;
  //nested for loop iterates through both sequences
  for (int i = 0; i < m_size; i++) {
    for (int j = 0; j < evidence.m_size; j++){
      //if data is equal and its the beginning of the evidence list, then updates variables as needed
      if ((j == 0) && (curr->m_data == currEv->m_data)){
	if (index == -1){
	  index = i;
	  indexEv = j;
	  count = count + 1;
	  counter++;
	}
      }
      //if data matches and j > 0, then checks indexes of both loops to make sure that the letters are next to each other in both sequences
      if ((curr->m_data == currEv->m_data) && (j > 0)){
	if ((i == index + 1) && (indexEv == j - 1)) {
	  count = count + 1;
	  index = i;
	  counter++;
	  indexEv = j;
	}
      }
      currEv = currEv->m_next;
    }
    //checks if values were updated, if not then values are reset as needed
    if (counter == 0) {
      if (curr->m_data != evidence.GetData(count - 1)){
      index = -1;
      count = 0;
      }
      if (curr->m_data == evidence.GetData(count - 1)){
	index++;
      }
    }
    //checks if count is = to evidence.m_size
    if (count == evidence.m_size){
      return true;
    }
    counter = 0;
    currEv = evidence.m_head;
    curr = curr->m_next;
  }
  //checks if count is = to evidence.m_size
  if (count == evidence.m_size) { 
    return true;
  }
  else {
    return false;
  }
}
char DNA::GetData(int nodeNum) {
  Node *curr = m_head;
  Node *prev = m_head;
  int counter = 0;
  //checks to see if index is valid
  if (nodeNum <= m_size - 1) {
    //iterates through list until value is found and then return value
    while(curr != nullptr) {
      if (counter == nodeNum) {
	return curr->m_data;
      }
      prev = curr;
      curr = curr->m_next;
      counter++;
    }
  }
  if (prev == NULL){
    prev = m_head;
  }
  return 'N';
}
//displays linked list when called
ostream &operator << (ostream &output, DNA &myDNA) {
  Node *curr = myDNA.m_head;
  output << myDNA.m_name << '\n';
  while (curr != nullptr) {
    output << curr->m_data;
    output << "->";
    curr = curr->m_next;
  }
  output << "END";
  return output;
}

