#pragma once

// Guaranteed size_t
#include <stddef.h>

// The rest of sized integers
#include <stdint.h>

typedef uint32_t GHOPEntity;

typedef struct GHOPComponent {
    uint8_t *Content;
    size_t Index;
} GHOPComponent;

// The component is a value. ex: float, MyStruct, etc
#define COMPONENT(_COMPONENT_INDEX, _VALUE...) (GHOPComponent) { .Index = _COMPONENT_INDEX, .Content = (uint8_t*) &_VALUE }

// The component is a pointer. ex: float*, MyStruct*, etc
#define COMPONENT_PTR(_COMPONENT_INDEX, _VALUE...) (GHOPComponent) { .Index = _COMPONENT_INDEX, .Content = (uint8_t*) _VALUE }

// Register a component in the ECS.
#define ECS_REGISTER_COMPONENT(_ECS, _COMPONENT_INDEX, _COMPONENT) _ECS.Rows[_COMPONENT_INDEX].Size = sizeof(_COMPONENT);

typedef struct GHOPEntities {
    size_t Count; // Number of elements in the row.
    size_t Capacity; // How many elements the row can hold before we reallocate.
    GHOPEntity *Entities; // Entities linked with Data & ECS->Entities.
} GHOPEntities;

typedef struct GHOPRow {
    size_t Size; // Size of an element.
    size_t Count; // Number of elements in the row.
    size_t Capacity; // How many elements the row can hold before we reallocate.
    uint8_t *Data; // The raw data of components.
    GHOPEntity *Dense; // Entities linked with Data & ECS->Entities.
    GHOPEntity *Sparse; // Entities linked with Data & ECS->Entities.
} GHOPRow;

typedef struct GHOPECS {
    GHOPRow *Rows; // The components live here.
    GHOPEntities Entities; // All entities.
} GHOPECS;

void ecs_AddECS(GHOPECS *pECS, GHOPComponent vComponent);

void ecs_AddComponent(GHOPECS *pECS, GHOPEntity vEntity, GHOPComponent vComponent);

GHOPComponent ecs_GetComponent(GHOPECS *pECS, GHOPEntity vEntity, size_t vIndex);

GHOPEntity ecs_CreateEntity(GHOPECS *pECS);

GHOPECS ecs_CreateECS(size_t vMaxComponents);