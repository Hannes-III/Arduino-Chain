#include <Chain.h>

class Xxx : public ChainElement{
  public:
    Xxx(String name);

    String getName();
    void setName(String name);

  private:
    String name;
};

