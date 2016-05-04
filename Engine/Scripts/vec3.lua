
--- This function defines multiplying a vec3 by a scalar (vec3 * scalar)
function vec3timesscalar(vec3, scalar)
    local new = Vec3{}
    new.x = vec3.x * scalar
    new.y = vec3.y * scalar
    new.z = vec3.z * scalar
    return new
end

--- This function defines multiplying a vec3 by a scalar (scalar * vec3)
function scalartimesvec3(scalar, vec3)
    local new = Vec3{}
    new.x = vec3.x * scalar
    new.y = vec3.y * scalar
    new.z = vec3.z * scalar
    return new
end

--- This function defines dividing a vec3 by a scalar (vec3 / scalar)
function vec3overscalar(vec3, scalar)
    local new = Vec3{}
    new.x = vec3.x / scalar
    new.y = vec3.y / scalar
    new.z = vec3.z / scalar
    return new
end

--- This function defines taking the cross product of two vec3's
function vec3crossvec3(vec_1, vec_2)
    local new = Vec3{}
    new.x = vec_1.y * vec_2.z - vec_1.z * vec_2.y
    new.y = vec_1.z * vec_2.x - vec_1.x * vec_2.z
    new.z = vec_1.x * vec_2.y - vec_1.y * vec_2.x
    return new
end

--- This function defines taking the dot product of two vec3's
function vec3dotvec3(vec_1, vec_2)
    return (vec_1.x * vec_2.x) + (vec_1.y * vec_2.y) + (vec_1.z * vec_2.z)
end

--- This function defines taking the length of a vec3
function lengthvec3(vec3)
    return math.sqrt((vec3.x * vec3.x) + (vec3.y * vec3.y) + (vec3.z * vec3.z))
end

--- This function defines normalizing a vec3 (preserve direction, but make length=1)
function normalizevec3(vec3)
    return vec3overscalar(vec3, lengthvec3(vec3))
end

--- This function defines adding two vec3's (vec3 + vec3)
function vec3plusvec3(vec_1, vec_2)
    new = Vec3{}
    new.x = vec_1.x + vec_2.x
    new.y = vec_1.y + vec_2.y
    new.z = vec_1.z + vec_2.z
    return new
end

--- This function negates a vec3 (-vec3)
function negatevec3(vec3)
    local new = Vec3{}
    new.x = -vec3.x
    new.y = -vec3.y
    new.z = -vec3.z
    return new
end
