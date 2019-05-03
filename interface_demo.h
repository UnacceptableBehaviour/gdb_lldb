#ifndef INTERFACE_DEMO_X
#define INTERFACE_DEMO_X


class InterfaceDemo{
  
  static int number_of_instances;
  static int number_of_class_observers;
  
  int number_of_observers;  

  
public:  

  InterfaceDemo(const char* name){
    
    InterfaceDemo::number_of_instances++;
    
    number_of_observers = 0;
  
  };
  
  
  InterfaceDemo* attacch_observer(void* observer) {
    // add observer to list
    InterfaceDemo::number_of_class_observers++;
    
    // pass back handle
    return this;
  };
  
  static int GetNoOfClassObservers(void){ return InterfaceDemo::number_of_class_observers; };
  static int GetNoOfInstances(void){ return InterfaceDemo::number_of_instances; };  

};



#endif