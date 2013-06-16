#ifndef LIBVALIDATE_H
#define LIBVALIDATE_H

#include <list>

class LibValidate
{
public:
    LibValidate();
    static std::list<std::list<int> > findDouble(int field[]);
};

#endif // LIBVALIDATE_H
