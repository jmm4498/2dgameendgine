#ifndef ECS_H
#define ECS_H

#include <bitset>
#include <vector>

const unsigned int MAX_COMPONENTS = 32;

/*
*   A signature is a bitset that represents which components an entity has. 
*/
typedef std::bitset<MAX_COMPONENTS> Signature;

struct IComponent {
    protected:
        static int nextId;
};

//Assign a unique id per component type T
template <typename T>
class Component: public IComponent {
    //Returns the unique id of Component type T
    static int GetId() {
        static auto id = nextId++;
        return id;
    }
};

class Entity {
    private:
        int id;
    public:
        Entity(int id) : id(id) {}
        int GetID() const;
};

class System {
    private :
        Signature componentSignature;
        std::vector<Entity> entities;
    public:
        System() = default;
        ~System() = default;
        void AddEntityToSystem(Entity entity);
        void RemoveEntityFromSystem(Entity entity);
        std::vector<Entity> GetSystemEntities() const;
        Signature& GetComponentSignature() const;

        template <typename TComponent> void RequireComponent();
};

class Registry {};

template <typename TComponent> 
void System::RequireComponent() {
    const auto componentId = Component<TComponent>::GetId();
    componentSignature.set(componentId);
}


#endif