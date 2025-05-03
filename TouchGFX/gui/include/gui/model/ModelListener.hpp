#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>
#include "main.h"

class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }

    // update dynamic graph
    virtual void UpdateGraph(uint8_t*, uint8_t*, uint8_t*) {}
    virtual void tick() {}

protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
