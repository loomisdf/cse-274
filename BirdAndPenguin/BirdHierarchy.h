#include <string>
using namespace std;

class Bird {
   public:
	  Bird();
      Bird(string);
	  virtual bool canFly();
	  virtual void printInfo();
   protected:
      string name;
};

class Penguin : public Bird {
   public:
      Penguin(string, int);
	  bool canFly();
	  void printInfo();
   private:
      int age;
};