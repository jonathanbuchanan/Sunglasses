// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef OBJECT_H
#define OBJECT_H

#include <vector>

//#include <sunglasses/Physics/PhysicsObject.h>
#include <sunglasses/Graphics/Mesh.h>
#include <sunglasses/Scripting/Script.h>
#include <sunglasses/Audio/AudioSource.h>

namespace sunglasses {

class GlobalScriptingEnvironment;

#include <sunglasses/Scripting/LuaTypeRegistrar.h>

/// A Node intended to be used in the scene graph as a game object
/**
 * Object is a Node subclass that is intended to be used as an object in the
 * scene graph. It has built-in support for graphics, audio, physics, game logic
 * (coming), and AI (coming).
 */
class Object : public Node<Object> {
    friend GlobalScriptingEnvironment;
    friend LuaTypeRegistrar<Object>;
public:
    /// Default Constructor
    /**
     * This is the default constructor, which has no arguments. It initializes position
     * and rotation to (0, 0, 0), and initializes scale to (1, 1, 1). Physics is
     * disabled by default. Also, it has no models by default, no sounds, and
     * the flip normals member (boolean) is set to false.
     */
    Object();

    /// Constructor for name
    Object(std::string _name);

    /// Loads a script
    /**
     * This member function loads a lua script and executes it. This should be called
     * after loading all of the values, so everything is included properly. Each mesh
     * is registered as a subtable of object, in the fashion meshx, where x is the index
     * of a mesh in the vector of meshes
     * @param _script The path of the script
     */
    void loadScript(std::string _script);

    /// Registers the object within a script.
    /**
     * This method registers the object within a script.
     * @param script A pointer to the script to register in
     * @param value The value where the object should be registered
     */
    void registerInScript(Script *script, _PrivateScripting::LuaValue value);

    /// Registers the object within a script.
    /**
     * This method registers the object within a script. This action is intended
     * to be used recursively typically on the scene graph after adding a new scripted
     * node.
     */
    void registerInScript(Action action);

    /// Initializes the object.
    /**
     * This member function initializes the object by adding the update, render
     * playSound, and uniform actions.
     */
    virtual void init();

    /// Updates the object.
    /**
     * This member function updates the object. As of right now, it updates the
     * physics.
     */
    virtual void update(Action action);

    /// Renders the object.
    /**
     * This member function renders the object. This object should be called with
     * a tag, so that it only renders objects for a certain shader. This function
     * loops through the models and renders them with the object's material.
     */
    virtual void render(Action action);

    /// Passes the objects uniforms.
    /**
     * This member function passes the objects uniforms in OpenGL. As of right now,
     * this does nothing, but is still called because the rendering system calls it`
     * every frame.
     */
    virtual void uniform(Action action);

    /// Adds a mesh with pointers to the resources
    /**
     * This method creates a new mesh and adds it to the vector of meshes. It
     * associates the mesh with the resources specified in the parameters.
     * @param name The name of the new mesh
     * @param mesh The identifier of the mesh resource
     * @param material The name of the material resource
     */
    void newMesh(std::string name, std::string mesh, std::string material);

    /// Adds a mesh with pointers to the resources and some initial values
    /**
     * This method creates a new mesh and adds it to the vector of meshes. It
     * associates the mesh with the resources specified in the parameters. It
     * also initializes the mesh with the position, rotation, and scale values.
     * @param name The name of the new mesh
     * @param mesh The identifier of the mesh resource
     * @param material The name of the material resource
     * @param _position The position vector
     * @param _rotation The rotation vector
     * @param _scale The scale vector
     */
    void newMesh(std::string name, std::string mesh, std::string material, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale);

    /// Adds an audio source
    void newAudioSource(std::string name, std::string buffer,
        glm::vec3 position = glm::vec3(0.0f),
        float pitch = 1.0f,
        float gain = 1.0f);

    /// Plays an audio source
    void playAudioSource(std::string name);

    /// Sets the scripting enabled boolean
    void setScriptingEnabled(bool s) { scriptingEnabled = s; }

    /// Gets the position vector member.
    glm::vec3 getPosition() { return position; }
    /// Sets the position vector member.
    //void setPosition(glm::vec3 _position) { position = _position; physicsObject.setPosition(position); }

    /// Gets the rotation vector member.
    glm::vec3 getRotation() { return rotation; }
    /// Sets the rotation vector member.
    void setRotation(glm::vec3 _rotation) { rotation = _rotation; }

    /// Gets the scale vector member.
    glm::vec3 getScale() { return scale; }
    /// Sets the scale vector member.
    void setScale(glm::vec3 _scale) { scale = _scale; }

    /// Gets the physics enabled member (bool).
    bool getPhysicsEnabled() { return physicsEnabled; }
    /// Sets the physics enabled member (bool).
    void setPhysicsEnabled(bool _p) { physicsEnabled = _p; }
private:
    /// Position vector
    glm::vec3 position;
    /// Rotation vector
    glm::vec3 rotation;
    /// Scale vector
    glm::vec3 scale;

    /// The map of meshes
    std::map<std::string, graphics::Mesh> meshes;

    /// The map of audio sources
    std::map<std::string, AudioSource> audioSources;

    /// The physics objects
    //PhysicsObject physicsObject;
    /// Enables physics
    bool physicsEnabled;


    // Scripting
    Script script;
    bool scriptingEnabled = false;
};

} // namespace

#endif
