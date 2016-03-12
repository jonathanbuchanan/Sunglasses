require("math")
package.path = package.path .. ";../../Engine/Scripts/GLFWKeys.lua"
require("GLFWKeys")

oldMouse = {
    x = 0.0,
    y = 0.0
}
speed = 5.0
sensitivity = 0.1
yaw = 0.0
pitch = 0.0

function vec3timesscalar(vec3, scalar)
    local new = {}
    new.x = vec3.x * scalar
    new.y = vec3.y * scalar
    new.z = vec3.z * scalar
    return new
end

function vec3overscalar(vec3, scalar)
    local new = {}
    new.x = vec3.x / scalar
    new.y = vec3.y / scalar
    new.z = vec3.z / scalar
    return new
end

function vec3timesvec3(vec_1, vec_2)
    local new = {}
    new.x = vec_1.y * vec_2.z - vec_1.z * vec_2.y
    new.y = vec_1.z * vec_2.x - vec_1.x * vec_2.z
    new.z = vec_1.x * vec_2.y - vec_1.y * vec_2.x
    return new
end

function vec3length(vec3)
    return math.sqrt((vec3.x * vec3.x) + (vec3.y * vec3.y) + (vec3.z * vec3.z))
end

function normalizevec3(vec3)
    return vec3overscalar(vec3, vec3length(vec3))
end

function vec3plusvec3(vec_1, vec_2)
    local new = {}
    new.x = vec_1.x + vec_2.x
    new.y = vec_1.y + vec_2.y
    new.z = vec_1.z + vec_2.z
    return new
end

function negativevec3(vec3)
    local new = {}
    new.x = -vec3.x
    new.y = -vec3.y
    new.z = -vec3.z
    return new
end

function setcppvec3(cppvec3, vec3)
    cppvec3.set_x(vec3.x)
    cppvec3.set_y(vec3.y)
    cppvec3.set_z(vec3.z)
end

function update(delta, mousex, mousey)
    mouse = {
        x = mousex,
        y = mousey
    }
    offset = {
        x = mouse.x - oldMouse.x,
        y = oldMouse.y - mouse.y
    }
    oldMouse = mouse
    offset.x = offset.x * sensitivity
    offset.y = offset.y * sensitivity
    yaw = yaw + offset.x
    pitch = pitch + offset.y
    if pitch > 89.0 then
        pitch = 89.0
    end
    if pitch < -89.0 then
        pitch = -89.0
    end
    direction = {
        x = math.cos(math.rad(pitch)) * math.cos(math.rad(yaw)),
        y = math.sin(math.rad(pitch)),
        z = math.cos(math.rad(pitch)) * math.sin(math.rad(yaw))
    }
    camera.direction.set_x(direction.x)
    camera.direction.set_y(direction.y)
    camera.direction.set_z(direction.z)

    finalSpeed = speed * delta

    position = {
        x = camera.position.x(),
        y = camera.position.y(),
        z = camera.position.z()
    }
    up = {
        x = camera.up.x(),
        y = camera.up.y(),
        z = camera.up.z()
    }
    if keyboard_manager.pollKey(keys.up) == true then
        setcppvec3(camera.position, vec3plusvec3(vec3timesscalar(direction, finalSpeed), position))
    end
    if keyboard_manager.pollKey(keys.down) == true then
        setcppvec3(camera.position, vec3plusvec3(vec3timesscalar(direction, -finalSpeed), position))
    end
    if keyboard_manager.pollKey(keys.right) == true then
        setcppvec3(camera.position, vec3plusvec3(vec3timesscalar(normalizevec3(vec3timesvec3(direction, up)), finalSpeed), position))
    end
    if keyboard_manager.pollKey(keys.left) == true then
        setcppvec3(camera.position, vec3plusvec3(vec3timesscalar(normalizevec3(vec3timesvec3(direction, up)), -finalSpeed), position))
    end
    if keyboard_manager.pollKey(keys.space) == true then
        setcppvec3(camera.position, vec3plusvec3(vec3timesscalar({x = 0, y = 1, z = 0}, finalSpeed), position))
    end
    if keyboard_manager.pollKey(keys.leftshift) == true then
        setcppvec3(camera.position, vec3plusvec3(vec3timesscalar({x = 0, y = -1, z = 0}, finalSpeed), position))
    end
end
