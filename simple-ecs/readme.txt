This is a dead simple ECS. I wouldn't really advise using this for your projects as there a lot of really good ones out there. As is the nature of this repository, I just wanted
to mess around and figure out how to do a simple implemnetation in C. I don't claim to be a C master so this code is probably not the best.

Feel free to take it, tweak it, change it, improve it, or whatever else you'd like to do with it but do so at your own risk. read below if you're thinking about using this.

*NOTE BEFORE READING*
THIS ECS HAS NOT BEEN TESTED YET SO IT MAY NOT EVEN WORK IN ITS CURRENT STATE. ONCE I'M ABLE TO TEST IT AND MAKE SURE EVERYTHING WORKS, I'LL REMOVE THIS DISCLAIMER.
*END NOTE*

HOW TO USE IT:

ECS:
Create an ecs object via micro_create_ecs(). From there create your component types (up to 64 max) and you can loop through them by passing in a function pointer using
micro_forEach() or micro_forEachNested.

ENTITIES:
Creating entities is done by getting a free index via micro_getFreeIndex(). An empty entity is any that doesn't have any component flags set (which is 0). The     
function simply loops through entities until it finds one that has it's bits set to 0. The ids are all set when you create the ecs object so make sure you don't 
change them. With your entity id, you can now add components to it.

COMPONENTS:
As stated before, you can have up to 64 of these. Creating a component is just simply micro_createComponent() and then give some constant ids to them so that you can 
easily access them later for example (and a very simple one at that):

#define HIT_POINTS 0
#define PHYSICS    1

From there, you can wrap up the add/remove component functions for example:
typedef struct hitPoints
{
    int value;
} hitPoints

void AddHealthComponent(micro_ecs_object* ecs, int id, hitPoints hp)
{
    // could also just bit shift 1 << HIT_POINTS (that's what micro_idToBit does), delcare a constant, or whatever else
    micro_componentAdd(&ecs->entities[id], micro_idToBit(HIT_POINTS));
    ecs->components[HIT_POINTS] = hp;
}

void RemoveHealthComponent(micro_ecs_object* ecs, int id)
{
    // could also just bit shift 1 << HIT_POINTS (that's what micro_idToBit does), delcare a constant, or whatever else
    micro_componentRemove(&ecs->entities[id], micro_idToBit(HIT_POINTS));
    ecs->components[HIT_POINTS].value = 0;
}
    
SYSTEMS:
A system is just running the micro_forEach() function and using a function pointer for the work you'd like to have done on an entity. for checking 2 entities against
each other (like a trigger or something), you use the micro_forEachNested() version instead. Systems loop through every single entity. If the entity doesn't match, the loop wil just 
skip it. The reason I'm stating that it loops through every entity is so you can keep that in mind when deciding what you'd like entity limit to be.

WHY MICRO?:
It was done to hopefully avoid name collisions and it's small so micro seemed like a good fit. If people end up using this I can always change it if they run into name
collision issues.

Is it fast?
This ecs wasn't built for speed in mind. It's designed around simplicity and ease of use (which I think it more or less accomplishes). I haven't benchmarked it but it should be more 
than fast enough for games that are small in scope. For bigger games I'd suggest flecs (C) or entt (C++).

COMPONENT MAX:
You can have up to 64 components total with the way this ECS is setup. The reason why is that entities are matched via a 64 bit integer. This keeps conditional checks when matching 
down to just one.

ADDING TO PROJECT:
This is just made up of 2 small files so simply copy them and paste them into you project; no need to worry about linking or references.

DEPENDENCIES:
This ecs has a dependency on stdlib.h and stdint.h so nothing crazy
