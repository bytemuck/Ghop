// It's the file where I try stuff.

#include "ghop_ecs/ecs.h"

#include <stdio.h>

enum
{ // Holds every component id
    COMPONENT_MARKER,
    COMPONENT_HEALTH,
    COMPONENT_POSITION,
    COMPONENT_COUNT,
};

typedef struct CMarker
{
    uint32_t Mark;
} CMarker;

typedef uint32_t CHealth;

typedef struct CPosition
{
    int32_t X, Y;
} CPosition;

int32_t
main()
{
    GHOPECS ecs = ecs_CreateECS(COMPONENT_COUNT);
    ECS_REGISTER_COMPONENT(ecs, COMPONENT_MARKER, CMarker);
    ECS_REGISTER_COMPONENT(ecs, COMPONENT_HEALTH, CHealth);
    ECS_REGISTER_COMPONENT(ecs, COMPONENT_POSITION, CPosition);

    GHOPEntity entity = ecs_CreateEntity(&ecs);
    GHOPEntity entity2 = ecs_CreateEntity(&ecs);
    GHOPEntity entity3 = ecs_CreateEntity(&ecs);

    ecs_AddComponent(
      &ecs, entity2, COMPONENT(COMPONENT_MARKER, (CMarker){ .Mark = 0x24 }));
    ecs_AddComponent(
      &ecs, entity2, COMPONENT(COMPONENT_HEALTH, (CHealth){ 0x23 }));

    ecs_AddComponent(
      &ecs, entity, COMPONENT(COMPONENT_MARKER, (CMarker){ .Mark = 0x42 }));
    ecs_AddComponent(
      &ecs, entity, COMPONENT(COMPONENT_HEALTH, (CHealth){ 0x16 }));

    ecs_AddComponent(
      &ecs, entity3, COMPONENT(COMPONENT_HEALTH, (CHealth){ 0x80 }));

    ecs_AddComponent(
      &ecs,
      entity,
      COMPONENT(COMPONENT_POSITION, (CPosition){ .X = 0x10, .Y = 0x20 }));

    CHealth health =
      *(CHealth*)ecs_GetComponent(&ecs, entity, COMPONENT_HEALTH).Content;
    printf("Health: 0x%x\n", health);

    CHealth health2 =
      *(CHealth*)ecs_GetComponent(&ecs, entity2, COMPONENT_HEALTH).Content;
    printf("Health2: 0x%x\n", health2);

    CHealth health3 =
      *(CHealth*)ecs_GetComponent(&ecs, entity3, COMPONENT_HEALTH).Content;
    printf("Health3: 0x%x\n", health3);

    CMarker marker =
      *(CMarker*)ecs_GetComponent(&ecs, entity, COMPONENT_MARKER).Content;
    printf("Marker: 0x%x\n", marker.Mark);

    CPosition position =
      *(CPosition*)ecs_GetComponent(&ecs, entity, COMPONENT_POSITION).Content;
    printf("Position: 0x%x, 0x%x\n", position.X, position.Y);

    CMarker marker2 =
      *(CMarker*)ecs_GetComponent(&ecs, entity2, COMPONENT_MARKER).Content;
    printf("Marker2: 0x%x\n", marker2.Mark);
}