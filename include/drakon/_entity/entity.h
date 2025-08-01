#pragma once

#include <atomic>
#include <memory>
#include <vector>

#include <drakon/component>

namespace drakon::entity {

typedef unsigned long Entity;

Entity getNextEntity();
} // namespace drakon::entity
