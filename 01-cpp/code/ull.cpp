/*
 *
 * \author (2016) Artur Pereira <artur at ua.pt>
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>
#include <iostream>
#include <fstream>

#include "ull.h"

using namespace std;

namespace ull
{
    /* ************************************************* */

    /* The information support data structure  */
    struct Register
    {
        uint32_t nmec;       //!< student number
        const char *name;    //!< student name
    };

    /* The linked-list support data structure */
    struct Node 
    {
        Register reg;
        struct Node *next;
    };

    static Node *head = NULL;

    /* ************************************************* */

    void reset()
    {
        head = NULL;
    }

    /* ************************************************* */

    void load(const char *fname)
    {
        ifstream myFile(fname);
        string line;
        int count = 1;
        while (getline(myFile,line, '\n')){
            bool appearedDelim = false;
            string name;
            string nmec;
            int index = 0;
            line.length();
            for(int index = 0; index < line.length(); index++){
                char x = line[index];
                if (x == ';'){
                    appearedDelim = true;
                } else {
                    if (appearedDelim == false) {
                        name = name + x;
                    } else {
                        nmec = nmec + x;
                    }
                }
                
            }
            insert(atoi(nmec.c_str()), name.c_str());
        }
    }

    /* ************************************************* */

    void print()
    {
        
        cout << "||Printing all students:-----------||\n";
        Node *currentNode = head;
        while (currentNode != NULL)
        {
            cout << "||  " << currentNode->reg.nmec << " " << currentNode->reg.name << "\n";
            currentNode = currentNode->next;
        }
        cout << "||---------------------------------||\n";
        
    }

    /* ************************************************* */

    void insert(uint32_t nmec, const char *name)
    {
        //Registro do novo aluno
        Register newStudent;
        newStudent.name = strdup(name);
        newStudent.nmec = nmec;

        Node *nullNode = NULL;
        Node *newNode = new Node();
        newNode->reg = newStudent;

        //Adiciona nó quando a lista está vazia
        if(head == NULL){
            newNode->next = nullNode;
            head = newNode;
            return;
        }

        //Adiciona nó quando o atual numero é menor que o head
        if(head->reg.nmec > nmec){
            newNode->next = head;
            head = newNode;
            return;
        }

        //Adiciona nó quando o atual número é maior que o head 
        //e a lista tem apenas 1 elemento
        if(head->next == NULL && head->reg.nmec < nmec){
            head->next = newNode;
            newNode->next = nullNode;
            return;
        }

        //Adiciona nó no meio da lista ou no fim
        Node *currentNode = head;
        while (currentNode->next != NULL)
        {
            if(currentNode->next->reg.nmec > nmec){
                break;
            } else {
                currentNode = currentNode->next;
            }  
        }
        if (currentNode->next == NULL){
            //Adiciona no fim
            newNode->next = nullNode;
            currentNode->next = newNode;
            return;
        } else {
            //Adiciona no meio
            newNode->next = currentNode->next;
            currentNode->next = newNode;
            return;
        }
    }

    /* ************************************************* */

    const char *query(uint32_t nmec)
    {
        Node *currentNode = head;

        while (currentNode->next != NULL)
        {
            if (currentNode->reg.nmec == nmec)
            {
                break;
            } else {
                currentNode = currentNode->next;
            }
        }

        if(currentNode->reg.nmec != nmec){
            return NULL;
        } else {
            return currentNode->reg.name;
        }
    }

    /* ************************************************* */

    void remove(uint32_t nmec)
    {
        Node *currentNode = head;

        if(currentNode == NULL)
        {
            cout << "!!STUDENT NOT FOUND!!";
            return;
        }

        //Remove head quando há apenas 1 nó
        if (currentNode->next == NULL && currentNode->reg.nmec == nmec)
        {
            head = NULL;
            return;
        }

        //Remove head quando há mais que 1 nó
        if(currentNode->reg.nmec == nmec && currentNode->next != NULL)
        {
            head = currentNode->next;
            return;
        }
        
        //Remove qualquer outro nó
        while (currentNode->next != NULL)
        {
            if (currentNode->next->reg.nmec == nmec)
            {
                currentNode->next = currentNode->next->next;
                return;
            } else {
                currentNode = currentNode->next;
            }
        }

        cout << "!!STUDENT NOT FOUND!!";
    }

    /* ************************************************* */

}