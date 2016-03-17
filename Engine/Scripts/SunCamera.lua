require("math")
package.path = package.path .. ";../../Engine/Scripts/?.lua"
require("GLFWKeys")
require("vec3")

oldMouse = {
    x = 0.0,
    y = 0.0
}
speed = 5.0
sensitivity = 0.1
yaw = 0.0
pitch = 0.0

function setcppvec3(cppvec3, vec3)
    cppvec3.set_x(vec3.x)
    cppvec3.set_y(vec3.y)
    cppvec3.set_z(vec3.z)
end

doCameraInput = true
firstFrame = true

function update(delta, mousex, mousey)
    local cameraInputChanged = false
    if globalenvironment.globalExists("doCameraInput") == true then
        if doCameraInput ~= globalenvironment.getBoolean("doCameraInput") then
            cameraInputChanged = true
        end
        doCameraInput = globalenvironment.getBoolean("doCameraInput")
    end
    if doCameraInput == true then
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
        if cameraInputChanged == true or firstFrame == true then
            offset = {x = 0, y = 0}
        end
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
        camera.direction.assignTable(direction)

        finalSpeed = speed * delta

        position = camera.position.toTable()
        up = camera.up.toTable()
        if keyboard_manager.pollKey(keys.up) == true then
            camera.position.assignTable(vec3plusvec3(vec3timesscalar(direction, finalSpeed), position))
        end
        if keyboard_manager.pollKey(keys.down) == true then
            camera.position.assignTable(vec3plusvec3(vec3timesscalar(direction, -finalSpeed), position))
        end
        if keyboard_manager.pollKey(keys.right) == true then
            camera.position.assignTable(vec3plusvec3(vec3timesscalar(normalizevec3(vec3crossvec3(direction, up)), finalSpeed), position))
        end
        if keyboard_manager.pollKey(keys.left) == true then
            camera.position.assignTable(vec3plusvec3(vec3timesscalar(normalizevec3(vec3crossvec3(direction, up)), -finalSpeed), position))
        end
        if keyboard_manager.pollKey(keys.space) == true then
            camera.position.assignTable(vec3plusvec3(vec3timesscalar({x = 0, y = 1, z = 0}, finalSpeed), position))
        end
        if keyboard_manager.pollKey(keys.leftshift) == true then
            camera.position.assignTable(vec3plusvec3(vec3timesscalar({x = 0, y = -1, z = 0}, finalSpeed), position))
        end
    end
    firstFrame = false
end
