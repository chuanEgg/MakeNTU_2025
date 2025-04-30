#ifndef MEASUREOPTION_HPP
#define MEASUREOPTION_HPP

#include <gui_generated/containers/measureOptionBase.hpp>

class measureOption : public measureOptionBase
{
public:
    measureOption();
    virtual ~measureOption() {}

    virtual void initialize();

    void setText(int id);
protected:
};

#endif // MEASUREOPTION_HPP
