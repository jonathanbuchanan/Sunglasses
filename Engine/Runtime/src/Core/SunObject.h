// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef SUNOBJECT_H
#define SUNOBJECT_H

#include <vector>
#include <functional>

#include "../Physics/SunPhysicsObject.h"
#include "../Audio/SunSoundObject.h"
#include "../Graphics/SunModel.h"
#include "../Scripting/SunScript.h"

class SunGlobalLogicEnvironment;

/// A SunNode intended to be used in the scene graph as a game object
/**
 * SunObject is a SunNode subclass that is intended to be used as an object in the
 * scene graph. It has built-in support for graphics, audio, physics, game logic
 * (coming), and AI (coming).
 */
class SunObject : public SunNode {
    friend SunGlobalLogicEnvironment;
public:
    /// Default Constructor
    /**
     * This is the default constructor, which has no arguments. It initializes position
     * and rotation to (0, 0, 0), and initializes scale to (1, 1, 1). Physics is
     * disabled by default. Also, it has no models by default, no sounds, and
     * the flip normals member (boolean) is set to false.
     */
    SunObject();

    /// Constructor for name (string), model (string), and flip normals (boolean)
    /**
     * This is the constructor for name (string), model (string), and flip normals (boolean).
     * It initializes position and rotation to (0, 0, 0), and initializes scale to (1, 1, 1). Physics is
     * disabled by default. Also, it has no sounds. It loads a single model from the
     * file provided, and flipNormals is set by the constructor.
     */
    SunObject(string _name, string _modelPath, bool _flipNormals);

    /// Constructor for name (string), model (string), tag (string), and flip normals (boolean)
    /**
     * This is the constructor for name (string), model (string), and flip normals (boolean).
     * It initializes position and rotation to (0, 0, 0), and initializes scale to (1, 1, 1). Physics is
     * disabled by default. Also, it has no sounds. It loads a single model from the
     * file provided, and flipNormals is set by the constructor. Finally, it adds
     * a single tag from the third parameter.
     */
	SunObject(string _name, string _modelPath, string tag, bool _flipNormals);

    void loadScript(std::string _script);

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
    virtual void update(SunAction action);

    /// Renders the object.
    /**
     * This member function renders the object. This object should be called with
     * a tag, so that it only renders objects for a certain shader. This function
     * loops through the models and renders them with the object's material.
     */
    virtual void render(SunAction action);

    /// OLD.
    virtual void playSound(SunAction action);

    /// Passes the objects uniforms.
    /**
     * This member function passes the objects uniforms in OpenGL. As of right now,
     * this does nothing, but is still called because the rendering system calls it`
     * every frame.
     */
    virtual void uniform(SunAction action);

    /// OLD.
    virtual void passPOVUniforms(SunShader _shader);

    void setScriptingEnabled(bool s) { scriptingEnabled = s; }

    /// Gets the position vector member.
    glm::vec3 getPosition() { return position; }
    /// Sets the position vector member.
    void setPosition(glm::vec3 _position) { position = _position; physicsObject.setPosition(position); }

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

    /// Gets the material member (SunObjectMaterial).
    SunObjectMaterial getMaterial() { return material; }
    /// Sets the material member (SunObjectMaterial).
    void setMaterial(SunObjectMaterial _material) { material = _material; }

    /// Gets the flip normals member (bool).
    bool getFlipNormals() { return flipNormals; }
    /// Sets the flip normals member (bool).
    void setFlipNormals(bool _f) { flipNormals = _f; }
private:
    /// Position vector
    glm::vec3 position;
    /// Rotation vector
    glm::vec3 rotation;
    /// Scale vector
    glm::vec3 scale;

    /// The physics objects
    SunPhysicsObject physicsObject;
    /// Enables physics
    bool physicsEnabled;

    /// The sound object
    SunSoundObject sound;

    /// The models
    SunModel model;

    /// The material of the models
    SunObjectMaterial material;

    /// Flips normals of models
    bool flipNormals = false;

    // Scripting
    SunScript script;
    bool scriptingEnabled = false;
};

#endif
