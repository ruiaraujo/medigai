#ifndef PATIENT_H
#define PATIENT_H
#include <iostream>
#include "person.h"
#include "convention.h"

class Patient : public Person {
  std::string address;
  Convention insurance;
  static unsigned long LastNumber;
  public:
    Patient() {}
    Patient(std::string, std::string, std::string , Convention);
    Patient(std::string, std::string , std::string, std::string, float, unsigned long);
    Patient(std::string, std::string , std::string, std::string, float, unsigned long , unsigned long);
    Patient(const Patient &);
    ~Patient() {}
    void setAdd(std::string);
    void setIns(std::string, float);
    void setIns(std::string, float , unsigned long);
    void setIns(float);
    void setIns(std::string);
    void setUN(unsigned long);
    long getUN() const ;
    std::string getAdd()const;
    Convention getIns()const;
    Patient * find ( const std::vector<Patient *> & );
    Patient * find ( unsigned long , const std::vector<Patient *> & );
    int findPos( unsigned long , const std::vector<Patient *> & );
    int findPos( const std::vector<Patient *> & );
    std::vector<Patient *>::iterator insOrd ( std::vector<Patient *> & );
    Patient & operator=( const Patient &u);
    friend std::ostream & operator<<(std::ostream &, Patient &);
};

#endif

