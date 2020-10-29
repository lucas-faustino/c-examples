#ifndef MICRO_ECS_H
#define MICRO_ECS_H

// this number has to be between 1 and 64. It's the maximum total of component types
#define MICRO_MAX_COMPONENTS              64
// feel free to change this value. The value chosen was arbitrary. Keep in mind you can't go past 32767
// as the entity id is a signed 16 bit int
#define MICRO_MAX_ENTITIES                100
// every entity can have every component so this is always = to the max entity limit
#define MICRO_MAX_COMPONENT_SIZE          MICRO_MAX_ENTITIES
#define MICRO_INVALID                     -1
#define MICRO_EMPTY_ENTITY                0

#include "stdint.h"

typedef void (*micro_action)(micro_entity*, micro_component*);
typedef void (*micro_action_nested)(micro_entity*, micro_entity*, micro_component*);

typedef struct micro_entity
{
    int16_t id;
    int64_t bits;

} micro_entity;

typedef struct micro_component
{
    void* buffer;
} micro_component;

typedef struct micro_ecs_object
{
    micro_entity entities[MICRO_MAX_ENTITIES];
    micro_component components[MICRO_MAX_COMPONENTS];
} micro_ecs_object;

micro_ecs_object*  micro_createECS        ();
void micro_destroyECS                     (micro_ecs_object* ecs);
int16_t micro_getFreeIndex                (micro_entity* entities);
int64_t micro_idToBit                     (uint8_t componentID);
void micro_createComponent                (micro_component* components, uint8_t componentID, size_t typeSize);
// multiple components can be added
void micro_componentAdd                   (micro_entity* entity, int64_t components);
// multiple components can be removed
void micro_componentRemove                (micro_entity* entity, int64_t components);
void micro_forEach                        (micro_ecs_object* ecs, int64_t componentMatch, micro_action action);
void micro_forEachNested                  (micro_ecs_object* ecs, int64_t outerMatch, int64_t innerMatch, micro_action_nested action);

#endif
