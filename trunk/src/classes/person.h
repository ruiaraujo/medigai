#ifndef PESSOAS_H
#define PESSOAS_H
#include <vector>
#include <iostream>

class Person {
  protected:
    std::string name;
    std::string tel;
    bool system;
    const unsigned long id;
  public:
    Person (std::string = "", std::string = "" , unsigned long = 0);
    Person (const Person &);
    void setName(std::string);
    void setTel(std::string);
    virtual ~Person() = 0;
    std::string getName() const;
    std::string getTel() const;
    void setSis(bool);
    bool getSis() const;
    unsigned long getId() const;
    Person & operator=( const Person & );
    virtual Person * find ( const std::vector<Person *> & );
    friend std::ostream & operator<<(std::ostream &, const Person &);
};


#endif

