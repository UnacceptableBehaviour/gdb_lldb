// compile with - C++17
//
// g++ -v -Wall -Weffc++ -std=c++17 virtual_interface.cc -o virt
// -v 		    verbose show commands issued by compiler / linker
// -Wall 	    show c++ related warnnings
// -Weff++ 	  warning generated by code that breaks coding advice in Effective C++ - S.Meyers   
// -g  		    include debugger information
// -std=c++17 __cplusplus=201703 => C++ Standard=C++17

#include<iostream>

// decalring an interface w/ pure virtual functions
class Printable
{
public:
    virtual std::string GetClassName() = 0;     // pure virtual func
    virtual ~Printable() = 0;   
};
Printable::~Printable(){};  // get rid of warning:
                            // warning: 'Printable' has virtual functions but non-virtual destructor [-Wnon-virtual-dtor]
                            // if dtor not declared get linker error

class Entity : public Printable
{
public:
    virtual std::string GetClassName() override { return "Entity"; }
    //~Entity(){};
};

class Player : public Entity
{
private:
    std::string m_Name;
public:
    Player(const std::string& name)
        : m_Name(name) {}
    virtual std::string GetClassName() override { return "Player"; }
    virtual std::string GetName() { return m_Name; }
};

void Print(Printable& obj) {
    std::cout << obj.GetClassName() << " & ref \n";
}
void Print(Printable* obj) {
    std::cout << obj->GetClassName() << " -> ptr \n";
}


int main(){
    Entity e;
    Player p("Player 1");
    
    Print(e);
    Print(p);
    
    std::cout << p.GetName() << "\n";       // object . direct

    Entity* pe = new Entity();
    Player* pp = new Player("Player 2");
    
    Print(pe);
    Print(pp);
    std::cout << pp->GetName() << "\n";     // -> dereference pointer
    
    // TODO Note on freeing memory
    // https://stackoverflow.com/questions/3428956/deleting-an-object-in-c
    //delete e; // error: cannot delete expression of type 'Entity'
    //delete p; // error: cannot delete expression of type 'Player'
    delete pe; // OK
    delete pp; // OK
}



