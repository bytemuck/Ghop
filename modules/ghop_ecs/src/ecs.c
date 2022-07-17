#include "ghop_ecs/ecs.h"
#include  "ghop_ecs/common.h"

#include <stdlib.h>
#include <string.h>

void ecs_AddECS(GHOPECS *pECS, GHOPComponent vComponent) {
    GHOPRow *row = pECS->Rows + vComponent.Index;

    GROW(row->Data, row->Size, row->Count, row->Capacity);
    memcpy(row->Data + (row->Size * row->Count), vComponent.Content, row->Size);

    row->Count++;
}

void ecs_AddComponent(GHOPECS *pECS, GHOPEntity vEntity, GHOPComponent vComponent) {
    GHOPRow *row = pECS->Rows + vComponent.Index;

    if (row->Data == NULL) {
        row->Capacity = 16;
        row->Data = malloc(row->Size * row->Capacity);
        row->Dense = malloc(sizeof(GHOPEntity) * row->Capacity);
        row->Sparse = malloc(sizeof(GHOPEntity) * row->Capacity);
    } else if (row->Count == row->Capacity) {
        row->Capacity *= 2;
        row->Data = realloc(row->Data, row->Size * row->Capacity);
        row->Dense = realloc(row->Dense, sizeof(GHOPEntity) * row->Capacity);
        row->Sparse = realloc(row->Sparse, sizeof(GHOPEntity) * row->Capacity);
    }

    memcpy(row->Data + (row->Size * row->Count), vComponent.Content, row->Size);

    row->Dense[row->Count] = vEntity;
    row->Sparse[vEntity] = row->Count;

    row->Count++;
}

GHOPComponent ecs_GetComponent(GHOPECS *pECS, GHOPEntity vEntity, size_t vIndex) {
    const GHOPComponent c = (GHOPComponent) {.Index = vIndex, .Content = &pECS->Rows[vIndex].Data[
            pECS->Rows[vIndex].Sparse[vEntity] * pECS->Rows[vIndex].Size]};

    return c;
}

GHOPEntity ecs_CreateEntity(GHOPECS *pECS) {
    GROW(pECS->Entities.Entities, sizeof(GHOPEntity), pECS->Entities.Count, pECS->Entities.Capacity);

    const GHOPEntity id = pECS->Entities.Count;
    pECS->Entities.Entities[pECS->Entities.Count] = id;
    pECS->Entities.Count++;

    return id;
}

GHOPECS ecs_CreateECS(size_t vMaxComponents) {
    GHOPECS ecs;

    ecs.Rows = malloc(sizeof(GHOPRow) * vMaxComponents);

    ecs.Entities.Entities = malloc(sizeof(GHOPEntity) * 16);
    ecs.Entities.Count = 0;
    ecs.Entities.Capacity = 16;

    for (uint32_t i = 0; i < vMaxComponents; i++) {
        ecs.Rows[i].Data = NULL; // Components (raw bytes)

        ecs.Rows[i].Dense = NULL; // Entities
        ecs.Rows[i].Sparse = NULL; // Entities

        ecs.Rows[i].Count = 0;
        ecs.Rows[i].Capacity = 0;
    }

    return ecs;
}
