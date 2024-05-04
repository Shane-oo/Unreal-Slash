#pragma once
#include "DrawDebugHelpers.h"

#define DRAW_SPHERE(Location) if(const UWorld* World = GetWorld()) DrawDebugSphere(World, Location, 25.f, 12, FColor::Red, true);
#define DRAW_SPHERE_SINGLE_FRAME(Location) if(const UWorld* World = GetWorld()) DrawDebugSphere(World, Location, 25.f, 12, FColor::Red, false, -1.f);
#define DRAW_LINE(StartLocation, EndLocation) if(const UWorld* World = GetWorld()) DrawDebugLine(World, StartLocation, EndLocation, FColor::Red, true, -1.f, 0, 1.f);
#define DRAW_LINE_SINGLE_FRAME(StartLocation, EndLocation) if(const UWorld* World = GetWorld()) DrawDebugLine(World, StartLocation, EndLocation, FColor::Red, false, -1.f, 0, 1.f);
#define DRAW_POINT(Location) if(const UWorld* World = GetWorld()) DrawDebugPoint(World, Location, 15.f, FColor::Red, true);
#define DRAW_POINT_SINGLE_FRAME(Location) if(const UWorld* World = GetWorld()) DrawDebugPoint(World, Location, 15.f, FColor::Red, false, -1.f);
#define DRAW_VECTOR(StartLocation, EndLocation)  {\
DRAW_LINE(StartLocation, EndLocation); \
DRAW_POINT(EndLocation); \
}
#define DRAW_VECTOR_SINGLE_FRAME(StartLocation, EndLocation)  {\
DRAW_LINE_SINGLE_FRAME(StartLocation, EndLocation); \
DRAW_POINT_SINGLE_FRAME(EndLocation); \
}
#define DRAW_BOX(Location) if(const UWorld* World = GetWorld()) DrawDebugBox(World, Location, FVector(10, 10, 10), FColor::Red, true);
#define DRAW_BOX_SINGLE_FRAME(Location) if(const UWorld* World = GetWorld()) DrawDebugBox(World, Location, FVector(10, 10, 10), FColor::Red, false, -1.f);
