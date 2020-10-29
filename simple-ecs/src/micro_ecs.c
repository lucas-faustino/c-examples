#include "stdlib.h"
#include "stdint.h"
#include "micro_ecs.h"

micro_ecs_object* micro_createECS()
{
    micro_ecs_object* ecs = (micro_ecs_object*)malloc(sizeof(micro_ecs_object));

    for (int32_t i = 0; i < MICRO_MAX_ENTITIES; i++)
    {
        ecs->entities[i].id = i;
        ecs->entities[i].bits = MICRO_EMPTY_ENTITY;
    }

    return ecs;
}

void micro_destroyECS(micro_ecs_object* ecs)
{
    if(ecs != NULL)
    {
        for (int32_t i = 0; i < MICRO_MAX_ENTITIES; i++)
            free(ecs->components[i].buffer);

        free(ecs);
    }
}

int16_t micro_getFreeIndex(micro_entity* entities)
{
    int16_t index;

    for (int16_t i = 0; i < MICRO_MAX_ENTITIES; i++)
    {
        if(entities[i].bits == MICRO_EMPTY_ENTITY)
            return i;
    }
    
    return MICRO_INVALID;
}

int64_t micro_idToBit(uint8_t componentID)
{
    return 1 << componentID;
}

void micro_createComponent(micro_component* components, uint8_t componentID, size_t typeSize)
{
    if(components[componentID].buffer == NULL)
        components[componentID].buffer = malloc(typeSize * MICRO_MAX_COMPONENT_SIZE);

}

void micro_componentAdd(micro_entity* entity, int64_t components)
{
    entity->bits |= components;
}

void micro_componentRemove(micro_entity* entity, int64_t components)
{
    entity->bits &= ~components;
}

void micro_forEach(micro_ecs_object* ecs, int64_t componentMatch, micro_action action)
{
    for (int32_t i = 0; i < MICRO_MAX_ENTITIES; i++)
    {
        if((ecs->entities[i].bits & componentMatch) == componentMatch)
            action(&ecs->entities[i], ecs->components);        
    }
}

void micro_forEachNested(micro_ecs_object* ecs, int64_t outerMatch, int64_t innerMatch, micro_action_nested action)
{
    for (int32_t i = 0; i < MICRO_MAX_ENTITIES; i++)
    {
        for (int32_t j = 0; j < MICRO_MAX_ENTITIES; j++)
        {
            // ignore if entities have the same id
            if(i != j && (ecs->entities[i].bits & outerMatch) == outerMatch && (ecs->entities[j].bits & innerMatch) == innerMatch)
                action(&ecs->entities[i], &ecs->entities[j], ecs->components);
        }
    }
}
