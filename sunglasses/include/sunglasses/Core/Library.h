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
 * The fourth template parameter is the resource 'library' type.
 */
template<typename K, typename R, typename P, typename L>
class Library {
static_assert(std::is_constructible<R, P, L>::value, "The resource must be constructible by its parameter and library objects!");
public:
    class ResourceHandle;

    /// Constructs the library with nothing
    Library(L &&_library = L()) : library(_library) {

    }

    /// Constructs the library with a list of keys/values
    Library(std::initializer_list<std::pair<const K, ResourceHandle>> _contents, L &&_library = L()) : contents(_contents), library(_library) {

    }

    /// Inserts a key/value pair
    void insert(const std::pair<const K, P> &pair) {
        contents.insert(pair);
    }

    /// Inserts a list of keys/values
    void insert(std::initializer_list<std::pair<const K, P>> list) {
        contents.insert(list);
    }

    /// Looks up a resource by a key
    /**
     * Only enabled if the parameter object is constructible by the key type
     */
    typename std::enable_if<std::is_constructible<P, K>::value, typename ResourceHandle::Returnable>::type
    operator[](const K &key) {
        if (contents.find(key) == contents.end())
            insert({key, P(key)});
        return contents.at(key).getReturnable(library);
    }

    /// Looks up a resource by a key
    typename ResourceHandle::Returnable at(const K &key) {
        return contents.at(key).getReturnable(library);
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

        /// The object that can be implicitly converted to the resource itself
        struct Returnable {
            /// Constructs the returnable
            Returnable(ResourceHandle &_handle, L &_library) : handle(_handle), library(_library) {

            }

            /// Implicitly converts the object to the resource
            operator R& () {
                return *handle.load(library);
            }

            /// A reference to the resource handle
            ResourceHandle &handle;

            /// A reference to the library parameter
            L &library;
        };

        /// Loads the managed resource
        R * load(L &library) {
            if (!resource)
                resource = std::make_unique<R>(parameter, library);
            return resource.get();
        }

        /// Returns a reference to the managed resource
        Returnable getReturnable(L &library) {
            return Returnable(*this, library);
        }
    private:
        /// The pointer to the resource it is handling
        std::shared_ptr<R> resource;

        /// The 'parameter' object for initializing the resource
        P parameter;
    };

    /// The library object
    L library;
private:
    /// The map of contents
    std::unordered_map<K, ResourceHandle> contents;
};

} // namespace

#endif
