#include "MockStats.h"

double MockStats::getGameTime() const { return 0.0; }

float MockStats::getFrameDelta() const { return 1.0; }

bool MockStats::isRunning() const { return true; }

void MockStats::closeGame() {}
