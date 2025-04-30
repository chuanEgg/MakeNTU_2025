#ifndef DISPLAYOPTION_HPP
#define DISPLAYOPTION_HPP

#include <gui_generated/containers/displayOptionBase.hpp>

class displayOption : public displayOptionBase
{
public:
    displayOption();
    virtual ~displayOption() {}

    virtual void initialize();

    void setText(int id);
protected:
};

#endif // DISPLAYOPTION_HPP
