#ifndef LIBVALIDATE_H
#define LIBVALIDATE_H

#include <list>
#include <vector>

class LibValidate
{
public:
    LibValidate();
    static std::list<std::list<int> > findDouble(std::vector<int> field);
};

#endif // LIBVALIDATE_H
