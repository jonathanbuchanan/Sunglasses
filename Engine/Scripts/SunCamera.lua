package.path = package.path .. ";../../Engine/Scripts/GLFWKeys.lua"
require("GLFWKeys")

function update(delta)
    t = keyboard_manager.pollKey(keys.t) -- Key 'T'
    if t == true then
        camera.set_FOV(camera.FOV() - 0.05)
    end
end
