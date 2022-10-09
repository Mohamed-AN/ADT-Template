// ADT.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

class Employee
{
private:
    char* name;
    int id;
    int salary;

public:
    // default constructor
    Employee()
    {
        cout << "Default Constructor invoked ..." << endl;
        this->id = 0;
        this->salary = 0;
        this->name = new char('\0');
        cout << "Created Object at address: " << this << endl;
        cout << endl;
    }

    // fully parameterized constructor
    Employee(const int eid, const int esal, const char* ename)
    {
        cout << "Fully Parameterized Constructor invoked ..." << endl;
        this->id = eid;
        this->salary = esal;
        this->name = new char[strlen(ename) + 1];
        if (this->name != NULL)
            strcpy(this->name, ename);
        else
            cout << "Allocating in fully parameterized constructor Failed" << endl;
        cout << "Created Employee with name: " << this->name << ", at address: " << this << endl;
        cout << endl;
    }

    // copy constructor
    Employee(Employee const & re)
    {
        cout << "Copy Constructor invoked, with temporary object (need data) at address: " << this << endl;
        cout << "Assigning the refrence \"&re\" to the passed object (has data) at address: " << &re << endl;
        this->id = re.id;
        this->salary = re.salary;
        this->name = new char[strlen(re.name) + 1];
        if (this->name != NULL)
            strcpy(this->name, re.name);
        else
            cout << "Allocating in copy constructor Failed" << endl;
    }

    // overloading operator=()
    Employee& operator=(Employee const & rHandEmp)
    {
        this->id = rHandEmp.id;
        this->salary = rHandEmp.salary;
        delete this->name;
        this->name = new char[strlen(rHandEmp.name) + 1];
        if (this->name != NULL)
        {
            strcpy(this->name, rHandEmp.name);
            this->name[strlen(rHandEmp.name)] = { '\0' };
        }

        return *this;
    }

    // overloading comparison operator<()
    int operator<(Employee const & rHandEmp)
    {
        if (this->getId() < rHandEmp.getId())
            return 1;
        else
            return 0;
    }

    // overloading comparison operator>()
    int operator>(Employee const & rHandEmp)
    {
        if (this->getId() > rHandEmp.getId())
            return 1;
        else
            return 0;
    }

    // set name
    void setName(const char* ename)
    {
        delete name;
        this->name = new char[strlen(ename) + 1];
        if (this->name != NULL)
            strcpy(this->name, ename);
    }

    // set salary
    void setSalary(int esalary)
    {
        this->salary = esalary;
    }

    // set id
    void setId(int eid)
    {
        this->id = eid;
    }

    // get name
    char* getName() const { return this->name; }

    // get salary
    int getSalary() const { return this->salary; }

    // get id
    int getId() const { return this->id; }

    // print employee
    void printEmp() const
    {
        cout << "ID: " << this->id << endl;
        cout << "Salary: " << this->salary << endl;
        cout << "Name: " << this->name << endl;
        cout << "#########################" << endl;
    }

    // destructor
    ~Employee()
    {
        cout << "Destroying Object with Name: " << this->name << ", at address: " << this << endl;
        delete this->name;
    }
};

template <typename T>
class ADT
{
protected:
    int size;
    T* arr;
    void Swap(T& firstElem, T& secondElem)
    {
        T temp;
        temp = firstElem;
        firstElem = secondElem;
        secondElem = temp;
    }

public:
    ADT()
    {
        this->size = 0;
        this->arr = NULL;
        std::cout << "From ADT 1-Constructor \n";
    }
    ADT(T* arrToBeSorted, const int arrSize)
    {
        this->size = arrSize;
        this->arr = arrToBeSorted;
        /* 
        // do not forget to add const to the pointer declaration in the parameter list of this constructor
        this->arr = new T[this->size];
        if (this->arr != NULL)
        {
            for (int i = 0; i < this->size; i++)
            {
                this->arr[i] = arrToBeSorted[i];
            }
        }
        */
        std::cout << "From ADT 2-Constructor \n";
    }

    /*
    ~ADT()
    {
        delete[] this->arr;
        std::cout << "... Object Destroyed ..." << std::endl;
    }
    */
    
    virtual void Sort() = 0;
};


template <typename T>
class Selection : public ADT<T>
{
public:
    Selection(T* arrNeedSort, const int arrSize):ADT<T>(arrNeedSort, arrSize){ std::cout << "From Selection 2-Constructor \n"; }

    void Sort()
    {
        int minIdx;
        for (int i = 0; i < this->size-1; i++)
        {
            minIdx = i;
            for (int j = i+1; j < this->size; j++)
            {
                if (this->arr[j] < this->arr[i])
                    minIdx = j;
            }

            if (minIdx != i)
                this->Swap(this->arr[minIdx], this->arr[i]);
        }
    }

};


template <typename T>
class Bubble : public ADT<T>
{
public:
    Bubble(T* arrToBeSorted, const int arrSize) :ADT<T>(arrToBeSorted, arrSize) { std::cout << "From Bubble 2-Constructor \n"; }

    void Sort()
    {
        int swapFlag = 0;
        for (int i = 1; i < this->size; i++)
        {
            for (int j = 0; j < (this->size - 1); j++)
            {
                if (this->arr[j] > this->arr[j + 1])
                {
                    this->Swap(this->arr[j], this->arr[j + 1]);
                    swapFlag++;
                }
            }

            if (!swapFlag)
                break;
        }

    }
};

template <typename T>
class Insertion : public ADT<T>
{
public:
    Insertion(T* arrToBeSorted, const int arrSize) :ADT<T>(arrToBeSorted, arrSize) { std::cout << "From Insertion 2-Constructor \n"; }

    void Sort()
    {
        for (int i = 1; i < this->size; i++)
        {
            for (int j = i - 1; j >= 0; j--)
            {
                if (this->arr[j + 1] < this->arr[j])
                    this->Swap(this->arr[j + 1], this->arr[j]);
                else
                    break;
            }
        }
    }
};

void fillEmps (Employee* arrOfEmps, const int arrSize);
void printEmps (Employee* arrOfEmps, const int arrSize);
char* generateRandomString();

int main()
{
    int arrOfInt[] = { 5, 8, 3, 2, 1 };
    Selection <int> myInts(arrOfInt, 5);
    Bubble <int> myInts1(arrOfInt, 5);
    Insertion <int> myInts2(arrOfInt, 5);
    myInts.Sort();
    for (int i = 0; i < 5; i++)
    {
        cout << arrOfInt[i] << endl;
    }
    
    Employee emps[5];
    fillEmps(emps, 5);
    cout << "Before Sorting ...\n#########################" << endl;
    printEmps(emps, 5);

    Selection <Employee> myEmps(emps, 5);
    cout << "After Sorting ...\n#########################" << endl;
    myEmps.Sort();
    printEmps(emps, 5);

    return 0;
}

void fillEmps (Employee* arrOfEmps, const int arrSize)
{
    for (int i = 0; i < arrSize; i++)
    {
        arrOfEmps[i].setId(rand()%10);
        arrOfEmps[i].setSalary(rand());
        arrOfEmps[i].setName("Mohamed");
    }
}

void printEmps (Employee* arrOfEmps, const int arrSize)
{
    for (int i = 0; i < arrSize; i++)
    {
        arrOfEmps[i].printEmp();
    }
}

char* generateRandomString()
{
    char myStr[5] = {'0', '0', '0', '0', '\0'};
    for (int i = 0; i < 4; i++)
    {
        myStr[i] = rand()%26;
    }
    myStr[4] = { '\0' };

    return myStr;
}