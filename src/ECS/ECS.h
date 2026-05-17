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
        static uint64_t nextId;
};

//Assign a unique id per component type T
template <typename T>
class Component: public IComponent {
    //Returns the unique id of Component type T
    static uint64_t GetId() {
        static uint64_t id = nextId++;
        return id;
    }
};

//An object with an ID
class Entity {
    private:
        uint64_t id;
    public:
        Entity(uint64_t id) : id(id) {}
        uint64_t GetID() const;

        Entity& operator = (const Entity& other) = default; 
        bool operator == (const Entity& other) const { return id == other.id; }
        bool operator != (const Entity& other) const { return id != other.id; }
        bool operator < (const Entity& other) const { return id < other.id; }
        bool operator > (const Entity& other) const { return id > other.id;}
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
        const Signature& GetComponentSignature() const;

        template <typename TComponent> void RequireComponent();
};

class IPool {
    public:
        virtual ~IPool() = default;
};

template <typename T>
class Pool: IPool{
    private:
        std::vector<T> data;
    public:
        Pool(uint64_t size = 100) {
            data.resize(size);
        }
        
        virtual ~Pool() = default;

        bool isEmpty() const {
            return data.empty();
        }

        uint64_t GetSize() const {
            return data.size();
        }

        void Resize(uint64_t newSize) {
            data.resize(newSize);
        }

        void Clear() {
            data.clear();
        }

        void Add(const T& component) {
            data.emplace_back(component);
        }

        void Set(uint64_t index, const T& component) {
            if (index < data.size()) {
                data[index] = component;
            } else {
                Logger::Err("Index out of bounds when setting component in pool.");
            }
        }

        T& Get(uint64_t index) {
            if (index < data.size()) {
                return data[index];
            } else {
                Logger::Err("Index out of bounds when getting component from pool.");
                return data[0];
            }
        }

        T& operator [](uint64_t index) {
            return Get(index);
        }
};

class Registry {
    private:
        uint64_t numEntities = 0;
        std::vector<IPool*>componentPools;
    public:
        Registry() = default;
        ~Registry() = default;
};

template <typename TComponent> 
void System::RequireComponent() {
    const auto componentId = Component<TComponent>::GetId();
    componentSignature.set(componentId);
}


#endif