#pragma once
#include "DrawDebugHelpers.h"

#define DRAW_SPHERE(Location) if(const UWorld* World = GetWorld()) DrawDebugSphere(World, Location, 25.f, 12, FColor::Red, true);
#define DRAW_LINE(StartLocation, EndLocation) if(const UWorld* World = GetWorld()) DrawDebugLine(World, StartLocation, EndLocation, FColor::Red, true, -1.f, 0, 1.f);
#define DRAW_POINT(Location) if(const UWorld* World = GetWorld()) DrawDebugPoint(World, Location, 15.f, FColor::Red, true);
#define DRAW_VECTOR(StartLocation, EndLocation)  {\
DRAW_LINE(StartLocation, EndLocation); \
DRAW_POINT(EndLocation); \
}
