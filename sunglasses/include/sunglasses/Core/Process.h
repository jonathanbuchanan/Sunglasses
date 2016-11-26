#ifndef PROCESS_H
#define PROCESS_H

#include <sunglasses/Core/Entity.h>

#include <utility>

namespace sunglasses {

/// A logic-containing object that operates on components of entities
template<typename... Cs>
class Process {
public:
    /// Runs the operation of the process
    void operator()(Entity<Cs...> &entity) {
        std::tuple<Cs &...> components = entity.template getComponents<Cs...>();

        apply(components, std::index_sequence_for<Cs...>{});
    }
protected:
    /// Operates on a set of components
    virtual void operate(Cs &...) = 0;
private:
    /// Template method used to apply tuple as function parameters
    template<size_t... Is>
    void apply(std::tuple<Cs &...> &components, std::index_sequence<Is...>) {
        operate(std::get<Is>(components)...);
    }
};

} // sunglasses

#endif
