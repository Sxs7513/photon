#pragma once
#include "core/yogaComp/Comp.h"
#include "core/event/EventWidget.h"

// class to unify all the custom features + add extra features if needed
class CoreWidget : public YogaComp, public EventWidget {};
