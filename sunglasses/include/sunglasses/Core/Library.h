#ifndef LIBRARY_H
#define LIBRARY_H

#include <type_traits>
#include <set>
#include <unordered_map>
#include <memory>

namespace sunglasses {

/// A library that holds many instances of one resource
/**
 * The first template parameter is the key type for the library.
 * The second template parameter is the resource type for the library.
 * The third template parameter is the resource 'parameter' type for the library.
 */
template<typename K, typename R, typename P>
class Library {
static_assert(std::is_constructible<R, P>::value, "The resource must be constructible by its parameter object!");
public:
    class ResourceHandle;

    /// Constructs the library with nothing
    Library() {

    }

    /// Constructs the library with a list of keys/values
    Library(std::initializer_list<std::pair<const K, ResourceHandle>> _contents) : contents(_contents) {

    }

    /// Inserts a key/value pair
    void insert(const std::pair<const K, P> &pair) {
        contents.insert(std::forward(pair));
    }

    /// Inserts a list of keys/values
    void insert(std::initializer_list<std::pair<const K, P>> list) {
        contents.insert(list);
    }

    /// Looks up a resource by a key
    ResourceHandle & at(const K &key) {
        return contents.at(key);
    }

    /// Loads all the resources inside the library
    void loadAll() {
        for (auto &handle : contents)
            handle.load();
    }

    /// Loads all the resources inside the library
    void operator()() {
        loadAll();
    }

    /// A handle to a resource
    class ResourceHandle {
    public:
        /// Constructs the handle with the parameter object
        /**
         * There is no constructor accepting a pointer to the resource
         * because the handle is meant to be the sole owner of the resource
         * and the parameter object should be the only thing needed to
         * create the resource object.
         */
        ResourceHandle(P _parameter) : parameter(_parameter) {

        }

        /// Loads the managed resource
        void load() {
            if (!resource)
                resource = std::make_unique<R>(parameter);
        }

        /// Returns a reference to the managed resource
        R * get() {
            load();
            return resource.get();
        }
    private:
        /// The pointer to the resource it is handling
        std::shared_ptr<R> resource;

        /// The 'parameter' object for initializing the resource
        P parameter;
    };
private:
    /// The map of contents
    std::unordered_map<K, ResourceHandle> contents;
};

} // namespace

#endif
