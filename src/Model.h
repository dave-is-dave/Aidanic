#pragma once

#include "glm.hpp"
#include <vector>

namespace Model {
    struct Sphere {
        glm::vec4 posRadius = glm::vec4(0.f);
        glm::vec4 color = glm::vec4(0.f);
    
        Sphere() {}
        Sphere(glm::vec3 position, float radius, glm::vec4 color) : posRadius(glm::vec4(position, radius)), color(color) {}
    };

    struct Ellipsoid {
        glm::vec4 center = glm::vec4(0.f);
        glm::vec4 radius = glm::vec4(0.f);
        glm::vec4 color = glm::vec4(0.f);
    
        Ellipsoid() {}
        Ellipsoid(glm::vec3 center, glm::vec3 radius, glm::vec4 color) :
            center(glm::vec4(center, 1.0)), radius(glm::vec4(radius, 1.0)), color(color) {}

        void update(glm::vec3 center, glm::vec3 radius, glm::vec4 color) {
            this->center = glm::vec4(center, 1.0);
            this->radius = glm::vec4(radius, 1.0);
            this->color = color;
        }
    };

    class _ObjectID {
    public:
        _ObjectID() {}
        _ObjectID(int32_t id) : id(id) {}

        int32_t getID() { return id; }
        void invalidate() { id = -1; }
        bool isValid() { return id != -1; }

        bool operator == (const _ObjectID& other) const { return id == other.id; }
        bool operator <  (const _ObjectID& other) const { return id <  other.id; }

    protected:
        int32_t id = -1;
    };

    class EllipsoidID : public _ObjectID {
        using _ObjectID::_ObjectID;
    };

    template <class ID_Class>
    int containsID(std::vector<ID_Class>& set, ID_Class id);
}

namespace PrimitiveManager {
    Model::EllipsoidID addEllipsoid(Model::Ellipsoid ellipsoid);
    void updateEllipsoid(Model::EllipsoidID id, glm::vec3 center, glm::vec3 radius, glm::vec4 color);
    void deleteEllipsoid(Model::EllipsoidID& id);

    Model::Ellipsoid getEllipsoid(Model::EllipsoidID id);
    uint32_t getNumEllipsoids();
    std::vector<Model::EllipsoidID> getEllipsoidIDs();
};