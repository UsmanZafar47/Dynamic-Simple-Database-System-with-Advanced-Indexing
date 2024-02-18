#include <iostream>
#include<string>
#include<fstream>
#include <cstdlib>
#include<cstring>
#include<sstream>
#include"header.h"
using namespace std;

string GetNthWord(string s, int n)
{
    int counter = 0;
    string temp;
    int i = 0;
    //cout<<s<<endl;
    while (s[i] != '\0')
    {

        //cout<<s[i]<<".";
        if (s[i] == ',')
        {
            //	cout<<" space "<<endl;
            //	i++;
            counter++;
        }

        else if (counter == n - 1)
        {
            //cout<<" here "<<endl;
            temp += s[i];
        }
        i++;
    }
    //	cout<<temp<<endl;
    return temp;
}

template<class T>
struct RbNode
{
    T stuff;
    char Treecol;
    string fileN;
    int lineN;
    RbNode* L, * R, * Father;
    RbNode* agla;
    RbNode()
    {
       // this->stuff = "";
        L = R = Father= NULL;
        this->Treecol = 'R';
        fileN = "";
        lineN = 0;
    }
    RbNode(T stuff)
    {
        this->stuff = stuff;
        L = R = Father= NULL;
        this->Treecol = 'R';
    }
};



template<class T>
class RedBlackTree
{
public:
    RbNode<T>* Root;

    RedBlackTree() { Root = NULL; }

    bool ll = false;
    bool rr = false;
    bool rl = false;
    bool lr= false;

    RbNode<T>* Lrotation(RbNode<T>* RbNode)
    {
        RbNode<T>* x = RbNode->R;
        RbNode<T>* y = x->L;
        x->L = RbNode;
        RbNode->R = y;
        RbNode->Father = x; // Father resetting is also important.
        if (y != NULL)
            y->Father = RbNode;
        return(x);
    }
    //this function performs R rotationNU
    RbNode<T>* Rrotation(RbNode<T>* RbNode)
    {
        RbNode<T>* x = RbNode->L;
        RbNode<T>* y = x->R;
        x->R = RbNode;
        RbNode->L = y;
        RbNode->Father = x;
        if (y != NULL)
            y->Father = RbNode;
        return(x);
    }

    RbNode<T>* help_in_insertion(RbNode<T>* root, RbNode<T>* RbNode)
    {
        // f is true when RED RED conflict is there.
        bool f = false;

        //recursive calls to insert at proper position according to BST properties.
        if (root == NULL)
        {
            return(RbNode);
        }
        else if (RbNode->stuff == root->stuff)
        {
            root->agla = help_in_insertion(root->agla, RbNode);
        }
        else if (RbNode->stuff < root->stuff)
        {
            root->L = help_in_insertion(root->L, RbNode);
            root->L->Father = root;
            if (root != this->Root)
            {
                if (root->Treecol == 'R' && root->L->Treecol == 'R')
                    f = true;
            }
        }
        else
        {
            root->R = help_in_insertion(root->R, RbNode);
            root->R->Father = root;
            if (root != this->Root)
            {
                if (root->Treecol == 'R' && root->R->Treecol == 'R')
                    f = true;
            }
            // at the same time of insertion, we are also assigning Father RbNodes 
            // also we are checking for RED RED conflicts
        }

        // now lets rotate.
        if (this->ll) // for L rotate.
        {
            root = Lrotation(root);
            root->Treecol = 'B';
            root->L->Treecol = 'R';
            this->ll = false;
        }
        else if (this->rr) // for R rotate
        {
            root = Rrotation(root);
            root->Treecol = 'B';
            root->R->Treecol = 'R';
            this->rr = false;
        }
        else if (this->rl)  // for R and then L
        {
            root->R = Rrotation(root->R);
            root->R->Father = root;
            root = Lrotation(root);
            root->Treecol = 'B';
            root->L->Treecol = 'R';

            this->rl = false;
        }
        else if (this->lr)          // for L and then R.
        {
            root->L = Lrotation(root->L);
            root->L->Father = root;
            root = Rrotation(root);
            root->Treecol = 'B';
            root->R->Treecol = 'R';
            this->lr = false;
        }
        // when rotation and recolouring is done flags are reset.
        // Now lets take care of RED RED conflict
        if (f)
        {
            if (root->Father->R == root)  // to check which child is the current RbNode of its Father
            {
                if (root->Father->L == NULL || root->Father->L->Treecol == 'B')  // case when Father's sibling is black
                {// perform certaing rotation and recolouring. This will be done while backtracking. Hence setting up respective flags.
                    if (root->L != NULL && root->L->Treecol == 'R')
                        this->rl = true;
                    else if (root->R != NULL && root->R->Treecol == 'R')
                        this->ll = true;
                }
                else // case when Father's sibling is red
                {
                    root->Father->L->Treecol = 'B';
                    root->Treecol = 'B';
                    if (root->Father != this->Root)
                        root->Father->Treecol = 'R';
                }
            }
            else
            {
                if (root->Father->R == NULL || root->Father->R->Treecol == 'B')
                {
                    if (root->L != NULL && root->L->Treecol == 'R')
                        this->rr = true;
                    else if (root->R != NULL && root->R->Treecol == 'R')
                        this->lr = true;
                }
                else
                {
                    root->Father->R->Treecol = 'B';
                    root->Treecol = 'B';
                    if (root->Father != this->Root)
                        root->Father->Treecol = 'R';
                }
            }
            f = false;
        }
        return(root);
    }

    void insert(T x, string filename1, int line_num1)
    {
        RbNode<T>* temp = new RbNode<T>;

        temp->stuff = x;
        temp->fileN = filename1;
        temp->lineN = line_num1;
        temp->Treecol = 'R';
        temp->L = NULL;
        temp->R = NULL;
        temp->agla = NULL;

        if (this->Root == NULL)
        {
            this->Root = temp;
            this->Root->Treecol = 'B';
        }
        else
            this->Root = help_in_insertion(this->Root, temp);
    }

    RbNode<T>* Decendant(RbNode<T>* p)
    {
        RbNode<T>* y = NULL;
        if (p->L != NULL)
        {
            y = p->L;
            while (y->R != NULL)
                y = y->R;
        }
        else
        {
            y = p->R;
            while (y->L != NULL)
                y = y->L;
        }
        return y;
    }

    void deleterecord(string filename, int lineNum) 
    {
        //cout << filename << " " << lineNum << endl;

        ifstream file;
        file.open(filename.c_str());
        ofstream temp;
        temp.open("temp.csv");
        string line;
        int count = 0;
       
       // if (!file.is_open())cout << "masla" << endl;
       // temp.open("temp.csv");
        while (getline(file, line)) {
            if (count == lineNum) {
               // cout << "checklol" << endl;
                
            }
            else{
          
                temp << line << endl;
            }
            count++;
        }
        file.close();
        temp.close();
        remove(filename.c_str());
        if (rename("temp.csv", filename.c_str()) == -1) {
            //cout << "unsuccessful" << endl;
        }
        else{}
           // cout << "Yas" << endl;
        


    }

    void deleteyear(int year) {

        ifstream file;
        ofstream temp;
        
        string line;
        for (int i = 0; i < 10; i++) {

            string filename = (to_string(i + 1) + ".csv");
            string filename2 = ("temp" + to_string(i + 1) + ".csv");
            file.open(filename.c_str());
            temp.open(filename2.c_str());

            while (getline(file, line)) {
                string check = GetNthWord(line, 2);

                if (check == to_string(year)) {
                    //cout << "check" << endl;
                }
                else {
                    temp << line << endl;
                }
            }

            temp.close();
            file.close();
            remove(filename.c_str());
            if (rename(filename2.c_str(), filename.c_str()) == -1) {
                //cout << "unsuccessful" << endl;
            }
            else {}

        }
    }
    void deletestate(string state) {
        ifstream file;
        ofstream temp;

        string line;
        for (int i = 0; i < 10; i++) {

            string filename = (to_string(i + 1) + ".csv");
            string filename2 = ("temp" + to_string(i + 1) + ".csv");
            file.open(filename.c_str());
            temp.open(filename2.c_str());

            while (getline(file, line)) {
                string check = GetNthWord(line, 5);

                if (check == state) {
                    //cout << "check" << endl;
                }
                else {
                    temp << line << endl;
                }
            }

            temp.close();
            file.close();
            remove(filename.c_str());
            if (rename(filename2.c_str(), filename.c_str()) == -1) {
                //cout << "unsuccessful" << endl;
            }
            else {}

        }
    }

    void updaterecord(string filename, int lineNum, string saman, int choice) {
        ifstream file;
        file.open(filename.c_str());
        ofstream temp;
        temp.open("temp.csv");
        string line;
        int count = 0;
        getline(file, line);
        // if (!file.is_open())cout << "masla" << endl;
        // temp.open("temp.csv");
        while (getline(file, line)) {
            if (count == lineNum-1) {
                //cout << line << endl;
                if (choice == 1) {
                    string id = GetNthWord(line, 1);
                    string year = GetNthWord(line, 2);
                    string c113 = GetNthWord(line, 3);

                    /* string lol=GetNthWord(line, 4);
                     string cn= GetNthWord(line, 5);
                     string state= GetNthWord(line, 6);
                     string deaths= GetNthWord(line, 7);
                     string adr= GetNthWord(line, 8);
                     temp << id << "," << year << "," << c113 << "," << lol << "," << cn << "," << saman << "," << deaths << "," << adr << endl;*/


                    string cn = GetNthWord(line, 4);
                    string state = GetNthWord(line, 5);
                    string deaths = GetNthWord(line, 6);
                    string adr = GetNthWord(line, 7);
                    temp << id << "," << year << "," << c113 << "," << cn << "," << saman << "," << deaths << "," << adr << endl;

                    //cout << id << "," << year << "," << c113 << "," << cn << "," << saman << "," << deaths << "," << adr << endl;
                }
                else if (choice == 2) {
                    string id = GetNthWord(line, 1);
                    string year = GetNthWord(line, 2);
                    string c113 = GetNthWord(line, 3);

                    /* string lol=GetNthWord(line, 4);
                     string cn= GetNthWord(line, 5);
                     string state= GetNthWord(line, 6);
                     string deaths= GetNthWord(line, 7);
                     string adr= GetNthWord(line, 8);
                     temp << id << "," <<saman << "," << c113 << "," << lol << "," << cn << "," << state << "," << deaths << "," << adr << endl;*/


                    string cn = GetNthWord(line, 4);
                    string state = GetNthWord(line, 5);
                    string deaths = GetNthWord(line, 6);
                    string adr = GetNthWord(line, 7);
                    temp << id << "," << saman << "," << c113 << "," << cn << "," << state << "," << deaths << "," << adr << endl;

                    //cout << id << "," <<saman<< "," << c113 << "," << cn << "," << saman << "," << deaths << "," << adr << endl;
                }
                else if (choice == 3) {
                    string id = GetNthWord(line, 1);
                    string year = GetNthWord(line, 2);
                    string c113 = GetNthWord(line, 3);

                    /* string lol=GetNthWord(line, 4);
                     string cn= GetNthWord(line, 5);
                     string state= GetNthWord(line, 6);
                     string deaths= GetNthWord(line, 7);
                     string adr= GetNthWord(line, 8);
                     temp << id << "," <year << "," << c113 << "," << lol << "," << saman << "," << state << "," << deaths << "," << adr << endl;*/


                    string cn = GetNthWord(line, 4);
                    string state = GetNthWord(line, 5);
                    string deaths = GetNthWord(line, 6);
                    string adr = GetNthWord(line, 7);
                    temp << id << "," << year << "," << c113 << "," << saman << "," << state << "," << deaths << "," << adr << endl;

                    //cout << id << "," <<saman<< "," << c113 << "," << cn << "," << saman << "," << deaths << "," << adr << endl;
                }
                else if (choice == 4) {
                    string id = GetNthWord(line, 1);
                    string year = GetNthWord(line, 2);
                    string c113 = GetNthWord(line, 3);

                    /* string lol=GetNthWord(line, 4);
                     string cn= GetNthWord(line, 5);
                     string state= GetNthWord(line, 6);
                     string deaths= GetNthWord(line, 7);
                     string adr= GetNthWord(line, 8);
                     temp << id << "," <year << "," << c113 << "," << lol << "," << cn << "," << state << "," <<saman << "," << adr << endl;*/


                    string cn = GetNthWord(line, 4);
                    string state = GetNthWord(line, 5);
                    string deaths = GetNthWord(line, 6);
                    string adr = GetNthWord(line, 7);
                    temp << id << "," << year << "," << c113 << "," << cn << "," << state << "," <<saman << "," << adr << endl;

                    //cout << id << "," <<saman<< "," << c113 << "," << cn << "," << saman << "," << deaths << "," << adr << endl;
                }
                else if (choice == 5) {
                    string id = GetNthWord(line, 1);
                    string year = GetNthWord(line, 2);
                    string c113 = GetNthWord(line, 3);

                    /* string lol=GetNthWord(line, 4);
                     string cn= GetNthWord(line, 5);
                     string state= GetNthWord(line, 6);
                     string deaths= GetNthWord(line, 7);
                     string adr= GetNthWord(line, 8);
                     temp << id << "," <year << "," << c113 << "," << lol << "," << cn << "," << state << "," <<deaths << "," << saman << endl;*/


                    string cn = GetNthWord(line, 4);
                    string state = GetNthWord(line, 5);
                    string deaths = GetNthWord(line, 6);
                    string adr = GetNthWord(line, 7);
                    temp << id << "," << year << "," << c113 << "," << cn << "," << state << "," << deaths << "," << saman << endl;

                    //cout << id << "," <<saman<< "," << c113 << "," << cn << "," << saman << "," << deaths << "," << adr << endl;
                }
              

            }
            else {

                temp << line << endl;
            }
            count++;
        }
        file.close();
        temp.close();
        remove(filename.c_str());
        if (rename("temp.csv", filename.c_str()) == -1) {
            //cout << "unsuccessful" << endl;
        }
        else {}
        // cout << "Yas" << endl;



    }

    void delete_RbNode(T x, string path, int choice)
    {
        if (Root == NULL)
        {
            cout << "\nEmpty Tree.";
            return;
        }
        RbNode<T>* p = Root;
        RbNode<T>* y = NULL;
        RbNode<T>* q = NULL;
        int found = 0;
        while (p != NULL && found == 0)
        {
            if (p->stuff == x)
                found = 1;
            if (found == 0)
            {
                if (p->stuff < x) p = p->R;
                else
                    p = p->L;
            }
        }
        if (found == 0)
        {
            cout << "\nElement Not Found.";
            return;
        }
        else
        {

           // cout << x << endl;
            string filename;
            if (choice == 1) {
               //filename = to_string(x) + ".txt";
                //cout << filename << endl;
            }
            else if(choice==2) {
                filename = x + ".txt";
                //cout << filename << endl;
            }
            string fullpath = "D:\\Vs projects\\semproject\\semproject\\" + path + "\\" + filename;
            // cout << fullpath << endl;
            fstream file;
            string tp;
            file.open(fullpath);

           // while (!file.eof()) {
                string ff;
                int lineNum;
                getline(file, ff);
                getline(file, tp);
                lineNum = stoi(tp);

               // cout << ff << " " << lineNum << endl;
                deleterecord(ff, lineNum);
               
           // }
            file.close();

           
            if (p->L == NULL || p->R == NULL)
                y = p;
            else
                y = Decendant(p);
            if (y->L != NULL)
                q = y->L;
            else
            {
                if (y->R != NULL)
                    q = y->R;
                else
                    q = NULL;
            }
            if (q != NULL)
                q->Father= y->Father;
            if (y->Father== NULL)
                Root = q;
            else
            {
                if (y == y->Father->L)
                    y->Father->L = q;
                else
                    y->Father->R = q;
            }
            if (y != p)
            {
                p->Treecol = y->Treecol;
                p->stuff = y->stuff;
            }
            if (y->Treecol == 'B')
                Viol_Fixation(q);
        }
    }


    void updatest(int id, string path, string saman, int choice) {
        string filename="D:\\Vs projects\\semproject\\semproject\\" + path + "\\" + to_string(id)+".txt";
        fstream file;
        string tp1, tp2;
        int lineNum;
        file.open(filename.c_str());
        if (!file.is_open())cout << "masla" << endl;
        getline(file, tp1);
        getline(file, tp2);
        lineNum = stoi(tp2);
        
        updaterecord(tp1, lineNum, saman, choice);

    }

    void idindexing(RbNode<T>* root)
    {
        ofstream file;

        if (root == NULL)
            return;
       

        idindexing(root->L);
        file.open("D:\\Vs projects\\semproject\\semproject\\idfiles\\"+to_string(root->stuff) + ".txt");

        file << root->fileN << endl;
        file << root->lineN << endl;


        idindexing(root->R);
       // cout << "khoti dya nikl jaa :" << endl;
    }
    


    void yearindexing(RbNode<T>* root)
    {
       
        ofstream file;

        if (root == NULL)
            return;


        yearindexing(root->L);
        file.open("D:\\Vs projects\\semproject\\semproject\\yearfiles\\" + to_string(root->stuff) + ".txt" );

        /*file << root->fileN << endl;
        file << root->lineN << endl;*/
        

        if (root->agla != NULL) {
            RbNode<T>* ptr = root;
            while (ptr != NULL) {
               
                
                    file << ptr->fileN << endl;
                    file << ptr->lineN << endl;
                    ptr = ptr->agla;
            }
        }

       /* if (root->L != NULL) {
            file << to_string(root->L->stuff) + ".txt" << endl;
        }
        if (root->R != NULL) {
            file << to_string(root->R->stuff) + ".txt" << endl;
        }*/
        


       yearindexing(root->R);
    }

    void stateindexing(RbNode<T>* root)
    {

        ofstream file;

        if (root == NULL)
            return;


        stateindexing(root->L);
        file.open("D:\\Vs projects\\semproject\\semproject\\statefiles\\" + (root->stuff) + ".txt");

        /*file << root->fileN << endl;
        file << root->lineN << endl;*/


        if (root->agla != NULL) {
            RbNode<T>* ptr = root;
            while (ptr != NULL) {


                file << ptr->fileN << endl;
                file << ptr->lineN << endl;
                ptr = ptr->agla;
            }
        }
        else {
            file << root->fileN << endl;
            file << root->lineN << endl;
        }

        



        stateindexing(root->R);
    }
    void deathindexing(RbNode<T>* root)
    {
       // cout << "check" << endl;

        ofstream file;

        if (root == NULL)
            return;


        deathindexing(root->L);
        file.open("D:\\Vs projects\\semproject\\semproject\\deathfiles\\" + (root->stuff) + ".txt");

        /*file << root->fileN << endl;
        file << root->lineN << endl;*/


        if (root->agla != NULL) {
            RbNode<T>* ptr = root;
            while (ptr != NULL) {


                file << ptr->fileN << endl;
                file << ptr->lineN << endl;
                ptr = ptr->agla;
            }
        }
        else {
            file << root->fileN << endl;
            file << root->lineN << endl;
        }

        deathindexing(root->R);
    }

    void ageadrindexing(RbNode<T>* root)
    {
        // cout << "check" << endl;

        ofstream file;

        if (root == NULL)
            return;


        ageadrindexing(root->L);
        file.open("D:\\Vs projects\\semproject\\semproject\\ageadrfiles\\" + (root->stuff) + ".txt");

        /*file << root->fileN << endl;
        file << root->lineN << endl;*/


        if (root->agla != NULL) {
            RbNode<T>* ptr = root;
            while (ptr != NULL) {


                file << ptr->fileN << endl;
                file << ptr->lineN << endl;
                ptr = ptr->agla;
            }
        }
        else {
            file << root->fileN << endl;
            file << root->lineN << endl;
        }

        ageadrindexing(root->R);
    }

    void cnindexing(RbNode<T>* root)
    {
        // cout << "check" << endl;

        ofstream file;

        if (root == NULL)
            return;


        cnindexing(root->L);
        file.open("D:\\Vs projects\\semproject\\semproject\\CNfiles\\" + (root->stuff) + ".txt");

        /*file << root->fileN << endl;
        file << root->lineN << endl;*/


        if (root->agla != NULL) {
            RbNode<T>* ptr = root;
            while (ptr != NULL) {


                file << ptr->fileN << endl;
                file << ptr->lineN << endl;
                ptr = ptr->agla;
            }
        }
        else {
            file << root->fileN << endl;
            file << root->lineN << endl;
        }

        cnindexing(root->R);
    }


    void idsearchinR(int a, int b) {
        for (int i = a; i <= b; i++) {
            int lineno = 0;

            string line = " ";
            int id{};
            string year;
            string cn;
            string st;
            string deaths;
            string c113;
            double ad{};
            double aadr{};
            string temp = " ";

            string fName = "";
            string tp;
            fstream file;
            string filename = "D:\\Vs projects\\semproject\\semproject\\idfiles\\" + to_string(i) + ".txt";
            //cout << filename << endl;
            //cout << filename << endl;

            file.open(filename);
           if( !file.is_open()) { cout << "masla" << endl; }
            getline(file, tp);
            fName = tp;
            getline(file, tp);
            lineno = stoi(tp);

           //  cout << fName << " " << lineno << endl;

            file.close();
            
            filedisplay(fName, lineno);

        }
    }


    void idsearch(T x)
    {
        if (Root == NULL)
        {
            cout << "\nEmpty Tree\n";
            return;
        }

        RbNode<T>* p = Root;
        int found = 0;

        while (p != NULL && found == 0)
        {
            if (p->stuff == x)
                found = 1;
            if (found == 0)
            {
                if (p->stuff < x)
                    p = p->R;
                else
                    p = p->L;
            }
        }
        if (found == 0)
            cout << "\nRbNode Not Found.";
        else
        {
            
            if (p->agla == NULL) {
                int lineno = 0;

                string line = " ";
                int id{};
                string year;
                string cn;
                string st;
                string deaths;
                string c113;
                double ad{};
                double aadr{};
                string temp = " ";

                string fName = "";
                string tp;
                fstream file;
                string filename = "D:\\Vs projects\\semproject\\semproject\\idfiles\\" + to_string(p->stuff) + ".txt";
                //cout << filename << endl;

                file.open(filename);
                getline(file, tp);
                fName = tp;
                getline(file, tp);
                lineno = stoi(tp);

                // cout << fName << " " << line << endl;

                file.close();
                string newname= "D:\\Vs projects\\semproject\\semproject\\" + fName;
                
                file.open(newname);
                for (int i = 0; i < lineno; i++) {
                    getline(file, tp);
                }
                getline(file, tp);

                stringstream inputs(tp);


                getline(inputs, temp, ',');
                id = atoi(temp.c_str());
                getline(inputs, year, ',');
                getline(inputs, cn, ',');
                getline(inputs, c113, ',');
                getline(inputs, st, ',');
                getline(inputs, deaths, ',');

                temp = " ";
                getline(inputs, temp, ',');
                ad = atof(temp.c_str());
                getline(inputs, temp, ',');

                aadr = atof(temp.c_str());

                // line = " ";

                cout << id << " " << year << " " << cn << " " << c113 << " " << st << " " << deaths << " " << ad << endl;

                file.close();
            }
            
        }
    }
    void yearsearch(T x)
    {
        if (Root == NULL)
        {
            cout << "\nEmpty Tree\n";
            return;
        }

        RbNode<T>* p = Root;
        int found = 0;

        while (p != NULL && found == 0)
        {
            if (p->stuff == x)
                found = 1;
            if (found == 0)
            {
                if (p->stuff < x)
                    p = p->R;
                else
                    p = p->L;
            }
        }
        if (found == 0)
            cout << "\nRbNode Not Found.";
        else
        {

           
            string fname;
            string tp;
            int lineno;
                fstream file;
                string filename = "D:\\Vs projects\\semproject\\semproject\\yearfiles\\" + to_string(p->stuff) + ".txt";
                //cout << filename << endl;
                //cout << filename << endl;

                file.open(filename);

                while (!file.eof()) {
                    getline(file, fname);
                    getline(file,tp);
                    lineno = stoi(tp);

                    filedisplay(fname, lineno);

                }
                file.close();
               
            
           
        }
    }

    void statesearch(T x) {

        if (Root == NULL)
        {
            cout << "\nEmpty Tree\n";
            return;
        }

        RbNode<T>* p = Root;
        int found = 0;

        while (p != NULL && found == 0)
        {
            if (p->stuff == x)
                found = 1;
            if (found == 0)
            {
                if (p->stuff < x)
                    p = p->R;
                else
                    p = p->L;
            }
        }
        if (found == 0)
            cout << "\nRbNode Not Found.";
        else
        {


            string fname;
            string tp;
            int lineno;
            fstream file;
            string filename = "D:\\Vs projects\\semproject\\semproject\\statefiles\\" + p->stuff + ".txt";
            //cout << filename << endl;
            //cout << filename << endl;

            file.open(filename);

            while (!file.eof()) {
                getline(file, fname);
                getline(file, tp);
                lineno = stoi(tp);

                filedisplay(fname, lineno);

            }
            file.close();



        }

    }

    void deathsearch(T x) {

        if (Root == NULL)
        {
            cout << "\nEmpty Tree\n";
            return;
        }

        RbNode<T>* p = Root;
        int found = 0;

        while (p != NULL && found == 0)
        {
            if (p->stuff == x)
                found = 1;
            if (found == 0)
            {
                if (p->stuff < x)
                    p = p->R;
                else
                    p = p->L;
            }
        }
        if (found == 0)
            cout << "\nRbNode Not Found.";
        else
        {


            string fname;
            string tp;
            int lineno;
            fstream file;
            string filename = "D:\\Vs projects\\semproject\\semproject\\deathfiles\\" + p->stuff + ".txt";
            //cout << filename << endl;
           // cout << filename << endl;

            file.open(filename);

            while (!file.eof()) {
                getline(file, fname);
                getline(file, tp);
                lineno = stoi(tp);

                filedisplay(fname, lineno);

            }
            file.close();



        }

    }

    void CNsearch(T x) {

        if (Root == NULL)
        {
            cout << "\nEmpty Tree\n";
            return;
        }

        RbNode<T>* p = Root;
        int found = 0;

        while (p != NULL && found == 0)
        {
            if (p->stuff == x)
                found = 1;
            if (found == 0)
            {
                if (p->stuff < x)
                    p = p->R;
                else
                    p = p->L;
            }
        }
        if (found == 0)
            cout << "\nRbNode Not Found.";
        else
        {


            string fname;
            string tp;
            int lineno;
            fstream file;
            string filename = "D:\\Vs projects\\semproject\\semproject\\CNfiles\\" + p->stuff + ".txt";
            //cout << filename << endl;
           // cout << filename << endl;

            file.open(filename);

            while (!file.eof()) {
                getline(file, fname);
                getline(file, tp);
                lineno = stoi(tp);

                filedisplay(fname, lineno);

            }
            file.close();



        }

    }

    void ageadrsearch(T x) {

        if (Root == NULL)
        {
            cout << "\nEmpty Tree\n";
            return;
        }

        RbNode<T>* p = Root;
        int found = 0;

        while (p != NULL && found == 0)
        {
            if (p->stuff == x)
                found = 1;
            if (found == 0)
            {
                if (p->stuff < x)
                    p = p->R;
                else
                    p = p->L;
            }
        }
        if (found == 0)
            cout << "\nRbNode Not Found.";
        else
        {


            string fname;
            string tp;
            int lineno;
            fstream file;
            string filename = "D:\\Vs projects\\semproject\\semproject\\ageadrfiles\\" + p->stuff + ".txt";
            //cout << filename << endl;
           // cout << filename << endl;

            file.open(filename);

            while (!file.eof()) {
                getline(file, fname);
                getline(file, tp);
                lineno = stoi(tp);

                filedisplay(fname, lineno);

            }
            file.close();



        }

    }


    void filedisplay(string fName, int lineno) {
        fstream file;
        string tp;
        string line = " ";
        int id{};
        string year;
        string cn;
        string st;
        string deaths;
        string c113;
        double ad{};
        double aadr{};
        string temp = " ";

        file.open(fName);
        for (int i = 0; i < lineno; i++) {
            getline(file, tp);
        }
        getline(file, tp);

        stringstream inputs(tp);


        getline(inputs, temp, ',');
        id = atoi(temp.c_str());
        getline(inputs, year, ',');
        getline(inputs, cn, ',');
        getline(inputs, c113, ',');
        getline(inputs, st, ',');
        getline(inputs, deaths, ',');

        temp = " ";
        getline(inputs, temp, ',');
        ad = atof(temp.c_str());
        getline(inputs, temp, ',');

        aadr = atof(temp.c_str());

        // line = " ";

        cout << id << " " << year << " " << cn << " " << c113 << " " << st << " " << deaths << " " << ad << endl;

        file.close();
    }

    void yrsearchinR(int a, int b) {
        for (int i = a; i <= b; i++) {
            string fname;
            string tp;
            int lineno;
            fstream file;
            string filename = "D:\\Vs projects\\semproject\\semproject\\yearfiles\\" + to_string(i) + ".txt";
            //cout << filename << endl;
            //cout << filename << endl;

            file.open(filename);

            while (!file.eof()) {
                getline(file, fname);
                getline(file, tp);
                lineno = stoi(tp);

                filedisplay(fname, lineno);

            }
            file.close();

        }

    }

    void Viol_Fixation(RbNode<T>* pt)
    {
        RbNode<T>* Father_pt = NULL;
        RbNode<T>* grand_Father_pt = NULL;
        if (pt != NULL) {
            while ((pt != Root) && (pt->Treecol != 'B'))
            {

                Father_pt = pt->Father;
                grand_Father_pt = pt->Father->Father;

                /*  Case : A
                    Father of pt is L child
                    of Grand-Father of pt */
                if (Father_pt == grand_Father_pt->L)
                {

                    RbNode<T>* uncle_pt = grand_Father_pt->R;

                    /* Case : 1
                       The uncle of pt is also red
                       Only ReTreecoling required */
                    if (uncle_pt != NULL && uncle_pt->Treecol ==
                        'R')
                    {
                        grand_Father_pt->Treecol = 'R';
                        Father_pt->Treecol = 'B';
                        uncle_pt->Treecol = 'B';
                        pt = grand_Father_pt;
                    }

                    else
                    {
                        /* Case : 2
                           pt is R child of its Father
                           L-rotation required */
                        if (pt == Father_pt->R)
                        {
                            Lrotation(Father_pt);
                            pt = Father_pt;
                            Father_pt = pt->Father;
                        }

                        /* Case : 3
                           pt is L child of its Father
                           R-rotation required */
                        Rrotation(grand_Father_pt);
                        swap(Father_pt->Treecol, grand_Father_pt->Treecol);
                        pt = Father_pt;
                    }
                }

                /* Case : B
                   Father of pt is R child
                   of Grand-Father of pt */
                else
                {
                    RbNode<T>* uncle_pt = grand_Father_pt->L;

                    /*  Case : 1
                        The uncle of pt is also red
                        Only ReTreecoling required */
                    if ((uncle_pt != NULL) && (uncle_pt->Treecol == 'R'))
                    {
                        grand_Father_pt->Treecol = 'R';
                        Father_pt->Treecol = 'B';
                        uncle_pt->Treecol = 'B';
                        pt = grand_Father_pt;
                    }
                    else
                    {
                        /* Case : 2
                           pt is L child of its Father
                           R-rotation required */
                        if (pt == Father_pt->L)
                        {
                            Rrotation(Father_pt);
                            pt = Father_pt;
                            Father_pt = pt->Father;
                        }

                        /* Case : 3
                           pt is R child of its Father
                           L-rotation required */
                        Lrotation(grand_Father_pt);
                        swap(Father_pt->Treecol, grand_Father_pt->Treecol);
                        pt = Father_pt;
                    }
                }
            }
        }

        Root->Treecol = 'B';
    }

   

    void Deletefix(RbNode<T>* L)
    {
        RbNode<T>* R;
        while (L != Root && L->Treecol == 'B')
        {
            if (L->Father->L == L)
            {
                R = L->Father->R;
                if (R->Treecol == 'R')
                {
                    R->Treecol = 'B';
                    L->Father->Treecol = 'R';
                    Lrotation(L->Father);
                    R = L->Father->R;
                }
                if (R->R->Treecol == 'B' && R->L->Treecol == 'B')
                {
                    R->Treecol = 'R';
                    L = L->Father;
                }
                else
                {
                    if (R->R->Treecol == 'B')
                    {
                        R->L->Treecol == 'B';
                        R->Treecol = 'R';
                        Rrotation(R);
                        R = L->Father->R;
                    }
                    R->Treecol = L->Father->Treecol;
                    L->Father->Treecol = 'B';
                    R->R->Treecol = 'B';
                    Lrotation(L->Father);
                    L = Root;
                }
            }
            else
            {
                R = L->Father->L;
                if (R->Treecol == 'R')
                {
                    R->Treecol = 'B';
                    L->Father->Treecol = 'R';
                    Rrotation(L->Father);
                    R = L->Father->L;
                }
                if (R->L->Treecol == 'B' && R->R->Treecol == 'B')
                {
                    R->Treecol = 'R';
                    L = L->Father;
                }
                else
                {
                    if (R->L->Treecol == 'B')
                    {
                        R->R->Treecol = 'B';
                        R->Treecol = 'R';
                        Lrotation(R);
                        R = L->Father->L;
                    }
                    R->Treecol = L->Father->Treecol;
                    L->Father->Treecol = 'B';
                    R->L->Treecol = 'B';
                    Rrotation(L->Father);
                    L = Root;
                }
            }
            L->Treecol = 'B';
            Root->Treecol = 'B';
        }
    }
};

void TreeCreation(RedBlackTree<int>& ID, RedBlackTree<int>& YR, RedBlackTree<string>& state, RedBlackTree<string>& death, RedBlackTree<string>& ageadr, RedBlackTree<string>& causeN)
{
    ifstream ifile;

    string filename;
    for (int i = 0; i < 10; i++) {

        int linen = 1;
        filename = to_string(i + 1) + ".csv";
       // cout << filename << endl;

        ifile.open(filename);

        string istring="";
        string line = " ";
        int id{};
        string year;
        string cn;
        string st;
        int yr;
        string deaths;
        string c113;
        double ad{};
        double aadr{};
        string temp = " ";
        
        if (!ifile) { cout << "masla" << endl; }
        getline(ifile, line);

        while (getline(ifile, line))
        {
            /*string year;
            string cn;
            string st;
            string death;
            double ad;
            string temp = " ";*/


            stringstream inputs(line);


            getline(inputs, temp, ',');
            id = atoi(temp.c_str());
            getline(inputs, year, ',');
            yr = atoi(year.c_str());
            getline(inputs, c113, ',');

            if (c113[0] == '\"')
            {
                getline(inputs, istring, ',');
                c113 += ',';
                c113 += istring;
                if (c113[c113.length() - 1] != '\"')
                {
                    istring = "";
                    getline(inputs, istring, ',');
                    c113 += ',';
                    c113 += istring;
                }
                if (c113[c113.length() - 1] != '\"')
                {
                    istring = "";
                    getline(inputs, istring, ',');
                    c113 += ',';
                    c113 += istring;
                }
            }

            getline(inputs, cn, ',');

           

            getline(inputs, st, ',');
            getline(inputs, deaths, ',');

            temp = " ";
            getline(inputs, temp, ',');
            ad = atof(temp.c_str());
            getline(inputs, temp, ',');

            aadr = atof(temp.c_str());

            line = " ";

            //cout <<aadr<< endl;
            
            ID.insert(id, filename, linen);
            YR.insert(yr, filename, linen);
            state.insert(st, filename, linen);
            death.insert(deaths, filename, linen);
            ageadr.insert(to_string(aadr), filename, linen);
            causeN.insert(cn, filename, linen);
            linen++;
            /*
                    Year.root = Year.insertAVLyear(Year.root, year);

                    causename.root = causename.insertAVLcn(causename.root, cn);


                    state.root = state.insertAVLstate(state.root, st);*/

        }
        ifile.close();
    }

}

void menu() 

    {

    int lll;
    cout << "Press 1 for Red Black Tree" << endl;
    cout << "Press 2 for Avl Tree" << endl;
    cin >> lll;
    
    if (lll == 1) {
        RedBlackTree<int> idtree;
        RedBlackTree<int> yrtree;
        RedBlackTree<string> statetree;
        RedBlackTree<string> deathtree;
        RedBlackTree<string> ageadstree;
        RedBlackTree<string> causeNtree;

        int lol;
        int id;
        int year;
        string state;
        string death;
        string ageadr;
        string causeN;


        TreeCreation(idtree, yrtree, statetree, deathtree, ageadstree, causeNtree);


        cout << "__________________WELCOME TO Red Black Tree stuffBASE__________________" << endl << endl;
        cout << "Press 1 for id indexing" << endl;
        cout << "Press 2 for year indexing" << endl;
        cout << "Press 3 for state indexing" << endl;
        cout << "Press 4 for death indexing" << endl;
        cout << "Press 5 for age adjusted death rate indexing" << endl;
        cout << "Press 6 for Cause Name indexing" << endl;
        cout << "Press 7 to index all" << endl;
        cout << "press 0 to exit" << endl;
        cin >> lol;

        switch (lol) {
        case 1:
            idtree.idindexing(idtree.Root);
            break;
        case 2:
            yrtree.yearindexing(yrtree.Root);
            break;
        case 3:
            statetree.stateindexing(statetree.Root);
            break;
        case 4:
            deathtree.deathindexing(deathtree.Root);
            break;
        case 5:
            ageadstree.ageadrindexing(ageadstree.Root);
            break;
        case 6:
            causeNtree.cnindexing(causeNtree.Root);
            break;
        case 7:
            idtree.idindexing(idtree.Root);
            yrtree.yearindexing(yrtree.Root);
            statetree.stateindexing(statetree.Root);
            deathtree.deathindexing(deathtree.Root);
            ageadstree.ageadrindexing(ageadstree.Root);
            causeNtree.cnindexing(causeNtree.Root);
            break;
        case 0:
            exit(0);
        }







        // yrtree.delete_RbNode(1999);

        int sr;
        cout << "Press 1 to search." << endl;
        cout << "Press 2 to search in Range" << endl;
        cout << "Press 3 to delete." << endl;
        cout << "Press 4 to update" << endl;
        cout << "Press 0 to exit" << endl;
        cin >> sr;

        switch (sr) {
        case 1:
            cout << "Press 1 for searching in id" << endl;
            cout << "Press 2 for searching in year" << endl;
            cout << "Press 3 for searching in state" << endl;
            cout << "Press 4 for searching in death" << endl;
            cout << "Press 5 for searching in age adjusted death rate" << endl;
            cout << "Press 6 for searching in cause name" << endl;
            cout << "Press 0 to exit" << endl;
            cin >> lol;

            switch (lol) {
            case 1:
                cout << "Enter id to search" << endl;
                cin >> id;
                idtree.idsearch(id);
                break;
            case 2:
                cout << "Enter year to search" << endl;
                cin >> year;
                yrtree.yearsearch(year);
                break;
            case 3:
                cout << "Enter state to search" << endl;
                cin.ignore();
                getline(cin, state);
                statetree.statesearch(state);
                break;
            case 4:
                cout << "Enter death to search" << endl;
                cin.ignore();
                getline(cin, death);
                deathtree.deathsearch(death);
                break;
            case 5:
                cout << "Enter aadr to search" << endl;
                cin.ignore();
                getline(cin, ageadr);
                ageadstree.ageadrsearch(ageadr);
                break;
            case 6:
                cout << "Enter cause name to search" << endl;
                cin.ignore();
                getline(cin, causeN);
                //cout<<causeN<<endl;
                causeNtree.CNsearch(causeN);
                break;
            case 0:
                exit(0);
            }
            break;
        case 2:
            int l;
            cout << "Press 1 to search id in range" << endl;
            cout << "Press 2 to search year in range" << endl;

            cin >> l;
            switch (l) {
            case 1:
                int r1, r2;
                cout << "Enter starting Range" << endl;
                cin >> r1;
                cout << "Enter ending Range" << endl;
                cin >> r2;
                idtree.idsearchinR(r1, r2);

                break;
            case 2:
                int R1, R2;
                cout << "Enter starting year" << endl;
                cin >> R1;
                cout << "Enter ending year" << endl;
                cin >> R2;
                yrtree.yrsearchinR(R1, R2);
                break;
            }
            break;
        case 3:
            cout << "Press 1 for deletion in id" << endl;
            cout << "Press 2 for deletion in year" << endl;
            cout << "Press 3 for deletion in state" << endl;
            cout << "Press 4 for deletion in death" << endl;
            cout << "Press 5 for deletion in age adjusted death rate" << endl;
            cout << "Press 6 for deletion in cause name" << endl;
            cout << "Press 0 to exit" << endl;
            cin >> lol;
            switch (lol) {
            case 1:
                int id;
                cout << "Enter id to delete" << endl;
                cin >> id;
                idtree.delete_RbNode(id, "idfiles", 1);
                idtree.idindexing(idtree.Root);

                break;
            case 2:
                int yr;
                cout << "Enter year to delete" << endl;
                cin >> yr;
                yrtree.delete_RbNode(yr, "yearfiles", 1);
                yrtree.deleteyear(yr);
                yrtree.yearindexing(yrtree.Root);
                break;
            case 3:
                cout << "Enter state to delete" << endl;
                cin.ignore();
                getline(cin, state);
                statetree.delete_RbNode(state, "statefiles", 2);
                statetree.deletestate(state);
                statetree.stateindexing(statetree.Root);
                break;
            case 4:
                cout << "Enter death to delete" << endl;
                cin.ignore();
                getline(cin, death);
                deathtree.delete_RbNode(death, "deathfiles", 2);
                deathtree.deathindexing(deathtree.Root);
                break;
            case 5:
                cout << "Enter aadr to delete" << endl;
                cin.ignore();
                getline(cin, ageadr);
                ageadstree.delete_RbNode(ageadr, "ageadrfiles", 2);
                ageadstree.ageadrindexing(ageadstree.Root);
                break;
            case 6:
                cout << "Enter cause name to delete" << endl;
                cin.ignore();
                getline(cin, causeN);
                //cout<<causeN<<endl;
                causeNtree.delete_RbNode(causeN, "CNfiles", 2);
                causeNtree.cnindexing(causeNtree.Root);
                break;
            case 0:
                exit(0);
            }
        case 4:
            int wow;
            int iidd;
            cout << "Press 1 to update state" << endl;
            cout << "Press 2 to update year" << endl;
            cout << "Press 3 to update cause name" << endl;
            cout << "Press 4 to update deaths" << endl;
            cout << "Press 5 to update age adjusted death rate" << endl;
            cout << "Press 0 to exit" << endl;
            cin >> wow;

            if (wow == 1) {

                string state2;
                cout << "Enter id to update record" << endl;
                cin >> iidd;

                cout << "Enter new state name" << endl;
                cin.ignore();
                getline(cin, state2);

                idtree.updatest(iidd, "idfiles", state2, 1);

            }
            else if (wow == 2) {
                string yrr;
                cout << "Enter id to update record" << endl;
                cin >> iidd;
                cout << "Enter year to update to" << endl;
                cin >> yrr;
                idtree.updatest(iidd, "idfiles", yrr, 2);
            }
            else if (wow == 3) {
                string cnn;
                cout << "Enter id to update record" << endl;
                cin >> iidd;
                cout << "Enter Cause Name to update to" << endl;
                cin.ignore();
                getline(cin, cnn);

                idtree.updatest(iidd, "idfiles", cnn, 3);
            }
            else if (wow == 4) {
                string deaths;
                cout << "Enter id to update record" << endl;
                cin >> iidd;
                cout << "Enter death to update to" << endl;
                cin.ignore();
                getline(cin, deaths);

                idtree.updatest(iidd, "idfiles", deaths, 4);
            }
            else if (wow == 5) {
                string dr;
                cout << "Enter id to update record" << endl;
                cin >> iidd;
                cout << "Enter deathrate to update to" << endl;
                cin.ignore();
                getline(cin, dr);

                idtree.updatest(iidd, "idfiles", dr, 5);
            }
            else {

                exit(0);
            }

        }



    }
    
    else if (lll == 2) {

    AVLbst <int> IDtree;//to insert ID;
    AVLbst <int> yeartree;//to insert Year in tree
    AVLbst <float> deathrate_tree;//to insert deathrate
    AVLbst <int> death_tree;//to insert deaths
    AVLbst <string> state_tree;//to insert states
    AVLbst <string> cause_tree;//to insert causes

    //file handling variables
    ifstream f, f2;
    string line;
    string dataID[1400];
    string data2[1100][8] = {  };
    int i = 0;
    int row = 0, col = 0;
    int count = 0;

    //distinict variables for every column 
    string line2;
    string year[1400];
    string causes[1400];
    string death[1400];
    string state[1400];
    string deathrate[1400];
    string cause_113[1400];

    int ID[1400];
    int year_int[1400];
    float deathrate_int[1400];
    int deaths_int[1400];
    int c;
    string filename;


    for (int k = 0; k < 10; k++)
    {

        int line_no = 1;
        filename = to_string(k + 1) + ".csv";
        cout << filename << endl;

        i = 0;
        //storing ID in string
        f.open(filename);
        while (getline(f, line, ','))//storing ONLY ID in string 
        {
            if (getline(f, line, '\n'))
            {
                if (getline(f, line, ','))
                    dataID[i] = line;
                i++;
                count = i;
            }
        }
        f.close();


        row = 0; col = 0;


        bool flag = false;
        i = 0;
        //	string cause_113[1100];
        string extra;

        //reading from file and storing them in variables
        f2.open(filename);
        while (!f2.eof())
        {

            getline(f2, line2, ',');
            getline(f2, year[i], ',');

            getline(f2, cause_113[i], ',');
            if (cause_113[i][0] == '\"')
            {
                getline(f2, extra, ',');
                cause_113[i] += extra;
                if (cause_113[i][cause_113[i].length() - 1] != '\"')
                {
                    getline(f2, extra, ',');
                    cause_113[i] += extra;
                }
                if (cause_113[i][cause_113[i].length() - 1] != '\"')
                {
                    getline(f2, extra, ',');
                    cause_113[i] += extra;
                }

            }

            getline(f2, causes[i], ',');
            getline(f2, state[i], ',');
            getline(f2, death[i], ',');
            getline(f2, deathrate[i], '\n');

            i++;
        }


        /*cout << "\t\t\t [1] Indexing by ID\n";
        cout << "\t\t\t [2] Indexing by YEAR\n";
        cout << "\t\t\t [3] Indexing by CAUSE\n";
        cout << "\t\t\t [4] Indexing by STATE\n";
        cout << "\t\t\t [5] Indexing by DEATHS\n";
        cout << "\t\t\t [6] Indexing by DEATHRATE\n";
        cin >> c;*/
        //while (c<1&&c>7) 
        //{
        //	cout << "Enter Valid Input\n";
        //	cin >> c;
        //}
        //converting string ID to in and storing in AVL

        for (int j = 1; j < count; j++) {
            //conversions 
            ID[j] = stoi(dataID[j - 1]);
            year_int[j] = stoi(year[j]);
            deaths_int[j] = stoi(death[j]);
            deathrate_int[j] = stof(deathrate[j]);


            //inseration
            IDtree.insert(ID[j], year_int[j], cause_113[j], causes[j], state[j], deaths_int[j], deathrate_int[j], filename, line_no, 1);
            yeartree.insert(ID[j], year_int[j], cause_113[j], causes[j], state[j], deaths_int[j], deathrate_int[j], filename, line_no, 2);
            cause_tree.insert(ID[j], year_int[j], cause_113[j], causes[j], state[j], deaths_int[j], deathrate_int[j], filename, line_no, 3);
            state_tree.insert(ID[j], year_int[j], cause_113[j], causes[j], state[j], deaths_int[j], deathrate_int[j], filename, line_no, 4);
            death_tree.insert(ID[j], year_int[j], cause_113[j], causes[j], state[j], deaths_int[j], deathrate_int[j], filename, line_no, 5);
            deathrate_tree.insert(ID[j], year_int[j], cause_113[j], causes[j], state[j], deaths_int[j], deathrate_int[j], filename, line_no, 6);

            line_no++;

        }



        f2.close();
    }


    cout << "\t\t\t[1]Indexing BY id\n";
    cout << "\t\t\t[2]Indexing BY year\n";
    cout << "\t\t\t[3]Indexing BY deaths\n";
    cout << "\t\t\t[4]Indexing BY death_rate\n";
    cout << "\t\t\t[5]Indexing BY cause\n";
    cout << "\t\t\t[6]Indexing BY state\n";
    cout << "\t\t\t[7]skip\n";
    cout << "\t\t\tEnter: ";
    cin >> c;

    switch (c)
    {
    case 1:
        IDtree.idindex();
        break;
    case 2:
        yeartree.year_index();
        break;
    case 3:
        death_tree.death_index();
        break;
    case 4:
        deathrate_tree.deathrate_index();
        break;
    case 5:
        cause_tree.cause_index();
        break;
    case 6:
        state_tree.state_index();
        break;
    case 7:
        break;
    }

    /// MENU
    ///
    /// 
    /// MENU
    //inputs for seacrh delete etc
    int choice, choice2;
    int id, range_inp, year_inp, death_inp;
    float deathrate_inp;
    string state_inp, cause_inp;
    char temp_cause[40];
    string inp;


    cout << "\t\t-----------------INDEX TREE--------------------\n";
    cout << "\t\t\t[1]------- AVL TREE----------\n";
    cout << "\t\t\t[2]------- B TREE------------\n";
    cout << "\t\t\t[3]------- RED BLACK TREE----\n";
    cin >> choice;

    system("cls");
    switch (choice)
    {
    case 1:
        cout << "\t\t\t [1] SEARCH\n";
        cout << "\t\t\t [2] DELETE\n";
        cout << "\t\t\t [3] UPDATE\n";
        cout << "\t\t\t [4] RANGE SEARCH\n";
        cin >> choice;
        system("cls");
        switch (choice)
        {
        case 1:
            cout << "\t\t\t [1] SEARCH by ID\n";
            cout << "\t\t\t [2] SEARCH by YEAR\n";
            cout << "\t\t\t [3] SEARCH by CAUSE\n";
            cout << "\t\t\t [4] SEARCH by STATE\n";
            cout << "\t\t\t [5] SEARCH by DEATHS\n";
            cout << "\t\t\t [6] SEARCH by DEATHRATE\n";
            cin >> choice;
            switch (choice)
            {
            case 1:
                cout << "Enter ID: ";
                cin >> id;
                if (IDtree.search(id) == 1) {
                    IDtree.search(id);
                }
                else
                    cout << "Not Found\n";

                break;//switch(3) -> case 1

            case 2:
                cout << "Enter YEAR: ";
                cin >> year_inp;
                if (yeartree.searchyear(year_inp) == 1)
                {
                    system("cls");
                    yeartree.searchyear(year_inp);

                }
                else
                    cout << "NOT FOUND\n";

                break; //switch(3) -> case 2
            case 3:
                cout << "Enter CAUSE: ";
                cin.ignore();
                getline(cin, cause_inp);
                if (cause_tree.search_cause(cause_inp) == 1)
                {
                    system("cls");
                    cause_tree.search_cause(cause_inp);
                }
                else
                {
                    cout << "\nNOT FOUND\n";
                }

                break;//switch(3) ->case 3 

            case 4:
                cout << "Enter STATE: ";
                cin >> state_inp;
                if (state_tree.searchstate(state_inp) == 1)
                {
                    system("cls");
                    state_tree.searchstate(state_inp);
                }
                else
                    cout << "NOT FOUND\n";

                break; //switch(3) -> case 4

            case 5:
                cout << "Enter Deaths: ";
                cin >> death_inp;
                if (death_tree.search_death(death_inp) == 1)
                {
                    system("cls");
                    death_tree.search_death(death_inp);

                }
                else
                    cout << "NOT FOUND\n";


                break;

            case 6:
                cout << "Enter Deathrate: ";
                cin >> deathrate_inp;
                if (deathrate_tree.search_deathrate(deathrate_inp) == 1)
                {
                    system("cls");
                    deathrate_tree.search_deathrate(deathrate_inp);
                }
                else
                    cout << "NOT FOUND\n";


                break;

            }

            break;//switch(1) -> case 1 break



        case 2:
            cout << "\t\t\t [1] DELETE by ID\n";
            cout << "\t\t\t [2] DELETE by YEAR\n";
            cout << "\t\t\t [3] DELETE by CAUSE\n";
            cout << "\t\t\t [4] DELETE by STATE\n";
            cout << "\t\t\t [5] DELETE by DEATHS\n";
            cout << "\t\t\t [6] DELETE by DEATHRATE\n";
            cin >> choice;
            switch (choice)
            {
                cout << "\t\t\t--------DELETION-----------\n";
            case 1:
                cout << "\t\t\tEnter ID: ";
                cin >> id;
                IDtree.Delete(id);

                if (IDtree.search(id) == 1)
                    cout << "\t\t\tNot Deleted";
                else
                {
                    //	IDtree.idindex();
                    cout << "\t\t\tDeleted Successfully\n";

                }
                break;//switch(3) -> case 1

            case 2:
                cout << "Enter YEAR: ";
                cin >> year_inp;
                yeartree.Delete_year(year_inp);
                yeartree.deleteyearfull(year_inp);

                if (yeartree.searchyear(year_inp) == 1)
                {

                    cout << "\t\t\tNot Deleted\n";
                }
                else
                {
                    //	yeartree.year_index();
                    cout << "\t\t\tDeleted Successfully\n";
                }

                break; //switch(3) -> case 2
            case 3:
                cout << "Enter CAUSE: ";
                cin.ignore();
                getline(cin, cause_inp);
                cause_tree.Delete_cause(cause_inp);
                if (cause_tree.search_cause(cause_inp) == 1)
                {
                    cout << "not deleted\n";
                }
                else
                {
                    // cause_tree.cause_index();
                    cout << "DEleted Successfully\n";
                }

                break;//switch(3) ->case 3 

            case 4:
                cout << "\t\t\tEnter STATE: ";
                cin >> state_inp;


                state_tree.Delete_state(state_inp);
                state_tree.deletestatefull(state_inp);

                if (state_tree.searchstate(state_inp) == 1)
                {
                    cout << "\t\t\tNOT DELETED\n";
                }
                else
                {
                    state_tree.state_index();
                    cout << "\t\t\tDELETED SUCCESSFULLY\n";

                }
                //yeartree.preorder();//cout << "Not Found\n";

                break; //switch(3) -> case 4

            case 5:
                cout << "\t\t\tEnter Deaths: ";
                cin >> death_inp;
                death_tree.Delete_death(death_inp);


                if (death_tree.search_death(death_inp) == 1)
                {
                    death_tree.death_index();
                    cout << "\t\t\tNOT DELETED\n";
                    //	death_tree.search_death(death_inp);

                }
                else
                    cout << "\t\t\tDELETED SUCCESSFULLY\n";


                break;

            case 6:
                cout << "\t\t\tEnter Deathrate: ";
                cin >> deathrate_inp;
                deathrate_tree.Delete_deathrate(deathrate_inp);
                if (deathrate_tree.search_deathrate(deathrate_inp) == 1)
                {
                    cout << "\t\t\tNOT DELETED\n";
                }
                else {
                    cout << "\t\t\tDELETED SUCCESSFULLY\n";
                    deathrate_tree.deathrate_index();
                }

                break;

            }

            break;//switch(1) -> case 2 break;

        case 3://UPDATE
//			cout << "\t\t\tNOT IMPLEMENTED YET\n \t\t\tBYE ";

            cout << "-----------UPDATE------------\n";
            cout << "Enter id: ";
            cin >> id;

            cout << "\t\t\t[1]Update State\n";
            cout << "\t\t\t[2]Update Years\n";
            cout << "\t\t\t[3]Update Causes\n";
            cout << "\t\t\t[4]Update deaths\n";
            cout << "\t\t\t[5]Update Deathrate\n";
            cout << "\t\t\tEnter choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                cout << "Enter state: ";
                cin >> state_inp;
                IDtree.update_state(id, "Id", state_inp, 1);
                break;

            case 2:
                cout << "Enter Year: ";
                cin >> inp;
                yeartree.update_state(id, "Id", inp, 2);


                break;
            case 3:
                cout << "Enter cause: ";
                cin >> inp;
                cause_tree.update_state(id, "Id", inp, 3);


                break;
            case 4:
                cout << "Enter deaths: ";
                cin >> inp;
                death_tree.update_state(id, "Id", inp, 4);


                break;

            case 5:
                cout << "Enter deathrate: ";
                cin >> inp;
                deathrate_tree.update_state(id, "Id", inp, 5);


                break;


            }
            break;//switch(1) -> case 3 break


        case 4:
            cout << "\t\t\t [1]RANGE SEARCH BY ID\n";
            cout << "\t\t\t [2]RANGE SEARCH BY YEAR\n";
            cout << "\t\t\t [3]RANGE SEARCH BY DEATHS\n \t\t\t";
            cin >> choice;
            // switch for range search choice ( range 1)
            switch (choice) {
            case 1:
                cout << "\t\t\t Enter Starting Range: ";
                cin >> id;
                cout << "\t\t\t Enter Ending Range: ";
                cin >> range_inp;

                /*		if (IDtree.search(id) == 1 && IDtree.search(range_inp) == 1 && id < range_inp)
                        {
                        }
                */		if (id > range_inp)
                {
                    system("cls");
                    cout << "\t\t\tOut of Range -- NOT FOUND\n";
                }
                else
                {
                    system("cls");
                    IDtree.rangesearch(id, range_inp);
                }
                break;//(range 1)

            case 2://(range 2)
                cout << "\t\t\t Enter Starting Range: ";
                cin >> year_inp;
                cout << "\t\t\t Enter Ending Range: ";
                cin >> range_inp;

                //					if (yeartree.searchyear(year_inp) == 1 && yeartree.searchyear(range_inp) == 1 && year_inp < range_inp)
                    //				{
                        //			}
                if (year_inp > range_inp)
                {
                    system("cls");
                    cout << "\t\t\tOut of Range -- NOT FOUND\n";
                }
                else
                {
                    system("cls");
                    yeartree.rangesearchyear(year_inp, range_inp);

                }

                break;//(range 2)

            case 3:
                cout << "\t\t\t Enter Starting Range: ";
                cin >> death_inp;
                cout << "\t\t\t Enter Ending Range: ";
                cin >> range_inp;

                //	if (death_tree.search_death(death_inp) == 1 && death_tree.search_death(range_inp) == 1 && death_inp < range_inp)
                    //{
                    //}
                if (death_inp > range_inp)
                {
                    system("cls");
                    cout << "\t\t\tOut of Range -- NOT FOUND\n";

                }
                else
                {

                    system("cls");
                    death_tree.rangesearch_death(death_inp, range_inp);


                }
                break;
            }
            break;
            //default:
                //cout << "invalid choice ";
        }



    }













    //for(int i)


    //IDtree.preorder();
    //yeartree.preorder();

    int j = 0;
    //for (int i = 0; i < 1000; i++)
    //{
    ////	for (j = 0; j < 8; j++) {
    //	cout << year[i] << " \n" << " ";// count++;
    ////}
    //}


//cout << "\n\n\n\n" << count;
    //cout << data2[1][0];

    //for (int i = 0; i < 10; i++) 
    //{
    //	cout << ID[i] << " ";
    //}

    }


else if(lll=3){

template<typename T>
class node
{
    long int* keys;  
    long int degree;      
    node** ptr; 
    long int num;     
    bool leaf; 

public:

    node<T>(long int temp, bool l)
    {
      
        degree = temp;
        leaf = l;
        keys = new long int[2 * degree - 1];
        ptr = new node<T> * [2 * degree];
        num = 0;
    }

    void traverse() {

        long int i=0;
        while (i < num)
        {
            if (leaf == false)
                ptr[i]->traverse();
            cout << " " << keys[i];
            i++;
        }

        if (leaf == false)
            ptr[i]->traverse();
    }

    node<T>* find(long int k) {
       long int i = 0;
        for (;i < num && k > keys[i];i++)

        if (keys[i] == k)
            return this;

        if (leaf == true)
            return NULL;

        return ptr[i]->find(k);
    }

    long int keySearch(long int temp)
    {
        long int i = 0;
        for (;i < num && keys[i] < temp;i++)
        return i;
    }


    void insertionNFull(long int temo) {
        long int i = num - 1;

        if (leaf == true)
        {
            for (;i >= 0 && keys[i] > temo;i--)
            {
                keys[i + 1] = keys[i];
            }
            keys[i + 1] = temo;
            num = num + 1;
        }
        else
        {
            for (;i >= 0 && keys[i] > temo;i--)

            if (ptr[i + 1]->num == 2 * degree - 1)
            {
                childHalf(i + 1, ptr[i + 1]);

                if (keys[i + 1] < temo)
                    i++;
            }
            ptr[i + 1]->insertionNFull(temo);
        }
    }

    void childHalf(int i, node<T>* y) {
        node<T>* z = new node<T>(y->degree, y->leaf);
        z->num = degree - 1;
        int j = 0;
        while (j < degree - 1) {
            z->keys[j] = y->keys[j + degree];
            j++;
        }
        if (y->leaf == 0)
        {
            long int j = 0;
            while (j < degree) {
                z->ptr[j] = y->ptr[j + degree];
                j++;
            }
        }

        y->num = degree - 1;

        long int j = num;
        while (j >= i + 1) {
            ptr[j + 1] = ptr[j];
            j++;
        }

        ptr[i + 1] = z;

        long int j = num - 1;
        while (j >= i) {
            keys[j + 1] = keys[j];
            j--;
        }

        keys[i] = y->keys[degree - 1];
        num = num + 1;
    }


    void deletion(int temp) {
        long int i = keySearch(temp);

        if (i < num && keys[i] == temp)
        {
            if (leaf)
                leafDeletion(i);
            else
                nonLeafDeletion(i);
        }
        else
        {
            if (leaf)
            {
                cout << "key " << temp << "isn't in the tree\n";
                return;
            }
            bool flag = ((i == num) ? true : false);

            if (ptr[i]->num < degree)
                in(i);
            if (flag && i > num)
                ptr[i - 1]->deletion(temp);
            else
                ptr[i]->deletion(temp);
        }
        return;
    }


    void leafDeletion(long int id) {
       long int i = id + 1;
        while (i < num) {
            keys[i - 1] = keys[i];
            i++;
        }

        num--;

        return;
    }


    void nonLeafDeletion(int id) {

        long int temp = keys[id];

        if (ptr[id]->num >= degree)
        {
            int pred = getP(id);
            keys[id] = pred;
            ptr[id]->deletion(pred);
        }
        else if (ptr[id + 1]->num >= degree)
        {
            long int succ = getS(id);
            keys[id] = succ;
            ptr[id + 1]->deletion(succ);
        }

        else
        {
            concatenate(id);
            ptr[id]->deletion(temp);
        }
        return;
    }

    int getP(int id) {
        node<T>* cur = ptr[id];
        for (;!cur->leaf;)
            cur = cur->ptr[cur->num];
        return cur->keys[cur->num - 1];
    }

    long int getS(int id) {

        node<T>* cur = ptr[id + 1];
        for (;!cur->leaf;)
            cur = cur->ptr[0];

        return cur->keys[0];
    }
    void in(long int id) {

        if (id != 0 && ptr[id - 1]->num >= degree)
            takePrev(id);

        else if (id != num && ptr[id + 1]->num >= degree)
            takeNext(id);
        else
        {
            if (id != num)
                concatenate(id);
            else
                concatenate(id - 1);
        }
        return;
    }

    void takePrev(int id) {

        node<T>* child = ptr[id];
        node<T>* sibling = ptr[id - 1];

        int i = child->num - 1;
        while (i >= 0) {
            child->keys[i + 1] = child->keys[i];
            i--;
        }
        if (!child->leaf)
        {
            for (int i = child->num; i >= 0; --i)
                child->ptr[i + 1] = child->ptr[i];
        }

        child->keys[0] = keys[id - 1];

        if (!child->leaf)
            child->ptr[0] = sibling->ptr[sibling->num];

        keys[id - 1] = sibling->keys[sibling->num - 1];

        child->num += 1;
        sibling->num -= 1;

        return;
    }


    void takeNext(long int id) {

        node<T>* child = ptr[id];
        node<T>* sibling = ptr[id + 1];

        child->keys[(child->num)] = keys[id];

        if (!(child->leaf))
            child->ptr[(child->num) + 1] = sibling->ptr[0];
        keys[id] = sibling->keys[0];
        int i = 1;
        while (i < sibling->num) {
            sibling->keys[i - 1] = sibling->keys[i];
            ++i;
        }
        if (!sibling->leaf)
        {
            long int i = 1;
            while (i <= sibling->num) {
                sibling->ptr[i - 1] = sibling->ptr[i];
                ++i;
            }
        }
        child->num += 1;
        sibling->num -= 1;

        return;
    }

 
    void concatenate(long int id) {
        node<T>* child = ptr[id];
        node<T>* sibling = ptr[id + 1];
        child->keys[degree - 1] = keys[id];

        for (int i = 0; i < sibling->num; ++i)
            child->keys[i + degree] = sibling->keys[i];

        if (!child->leaf)
        {
            long int i = 0;
            while (i <= sibling->num) {
                child->ptr[i + degree] = sibling->ptr[i];
                ++i;
            }
        }
        int i = id + 1;
        while (i < num) {
            keys[i - 1] = keys[i];
            ++i;
        }

        for (int i = id + 2; i <= num; ++i)
            ptr[i - 1] = ptr[i];

        child->num += sibling->num + 1;
        num--;

        delete(sibling);
        return;
    }

    friend class BTree;
};

template<typename T1>
class BTree
{
    node<T1>* head;
    int degree; 
public:

    // Constructor (Initializes tree as empty)
    BTree(int temp)
    {
        head = NULL;
        degree = temp;
    }

    void traverse()
    {
        if (head != NULL) head->traverse();
    }


    node<T1>* find(long int k)
    {
        return (head == NULL) ? NULL : head->find(k);
    }

    void insertion(long int l) {
        if (head == NULL)
        {
            head = new node<T1>(degree, true);
            head->keys[0] = l; 
            head->num = 1; 
        }
        else
        {
            if (head->num == 2 * degree - 1)
            {
            
                node<T1>* s = new node<T1>(degree, false);

                s->ptr[0] = head;
                s->childHalf(0, head);
                long int i = 0;
                if (s->keys[0] < l)
                    i++;
                s->ptr[i]->insertionNFull(l);
                head = s;
            }
            else 
                head->insertionNFull(l);
        }
    }


    void deletion(long int temp) {
        if (!head)
        {
            cout << "The tree is empty\n";
            return;
        }

        head->deletion(temp);
        if (head->num == 0)
        {
            node<T1>* tmp = head;
            if (head->leaf)
                head = NULL;
            else
                head = head->ptr[0];
            delete tmp;
        }
        return;
    }


};
}

}

int main()
{
    menu();
    return 0;
}