#ifndef EXTERNALDECL_H
#define EXTERNALDECL_H

#include "Visitor.hpp"

class ExternalDecl {
    public:
    virtual ~ExternalDecl() = default;
    virtual void accept(Visitor& visitor) = 0;
};

#endif
