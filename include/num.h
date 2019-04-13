#ifndef __NUM_H__
#define __NUM_H__

class Num
{
  protected:
    int _num;
  public:
    Num(int);
    virtual ~Num();
    virtual int getNum();
    virtual void setNum(int);
};

#endif //__NUM_H__