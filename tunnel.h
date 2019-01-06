#pragma once

#include <QObject>
#include "effect.h"

class tunnel : public IEffect
{
public:
    tunnel();

public slots:
    virtual void update();
};
