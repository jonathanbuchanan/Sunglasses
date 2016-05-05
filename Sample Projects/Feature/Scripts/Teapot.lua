require("math")
package.path = package.path .. ";../../Scripts/?.lua"
require("GLFWKeys")
require("vec3")

time = 0
rotationConstant = 30
function init()

end

function update(delta)
    time = time + delta
    if keyboard_manager.pollKey(keys.w) == true then
        rotationConstant = 1000
    end
    if keyboard_manager.pollKey(keys.s) == true then
        rotationConstant = 30
    end
    if keyboard_manager.pollKey(keys.x) == true then
        rotationConstant = 3
    end
    object.position.y = (4 * math.sin(4 * time)) + 1
    object.rotation.y = object.rotation.y + (delta * rotationConstant)
    --object.color.x = math.abs(math.sin(2 * time))
    --object.color.y = math.abs(math.sin(3 * time + 1))
    --object.color.z = math.abs(math.sin(4 * time + 2))
end
