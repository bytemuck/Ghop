#include "ghop_ecs/ecs.h"

#include <assert.h>
#include <malloc.h>
#include <stdio.h>

typedef enum Component
{
    COMPONENT_HEALTH,
    COMPONENT_SHIELD,
    COMPONENT_POSITION,
    COMPONENT_COUNT,
} Component;

typedef struct CHealth
{
    uint8_t Value;
} CHealth;

typedef struct CShield
{
    size_t Value;
} CShield;

typedef struct CPosition
{
    size_t X, Y;
} CPosition;

int
main()
{
    GHOPECS ecs = ecs_CreateECS(COMPONENT_COUNT);

    ECS_REGISTER_COMPONENT(ecs, COMPONENT_HEALTH, CHealth);
    ECS_REGISTER_COMPONENT(ecs, COMPONENT_SHIELD, CShield);
    ECS_REGISTER_COMPONENT(ecs, COMPONENT_POSITION, CPosition);

    GHOPEntity entity = ecs_CreateEntity(&ecs);

    CHealth* health_ptr = malloc(sizeof(CHealth));
    health_ptr->Value = 0xFF;

    ecs_AddComponent(&ecs, entity, COMPONENT_PTR(COMPONENT_HEALTH, health_ptr));
    ecs_AddComponent(&ecs, entity, COMPONENT(COMPONENT_SHIELD, (CShield){ .Value = 0x13 }));
    ecs_AddComponent(&ecs, entity, COMPONENT(COMPONENT_POSITION, (CPosition){ .X = 0x48, .Y = 0x52 }));

    free(health_ptr); // the value is copied inside the ECS.

    CHealth health = *(CHealth*)ecs_GetComponent(&ecs, entity, COMPONENT_HEALTH).Content;
    assert(health.Value == 0xFF);

    CShield shield = *(CShield*)ecs_GetComponent(&ecs, entity, COMPONENT_SHIELD).Content;
    assert(shield.Value == 0x13);

    CPosition position = *(CPosition*)ecs_GetComponent(&ecs, entity, COMPONENT_POSITION).Content;
    assert(position.X == 0x48);
    assert(position.Y == 0x52);
}