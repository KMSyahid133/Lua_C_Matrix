local dll = package.loadlib("./matrix.dll", "lua_matrix_library")()

--[[
    Compatibility problems:
    
    The code in C is 0 based indexing but Lua is 1 based indexing.
    So the solution is to use 1 based indexing but before calling the API substract it by 1 for C code compatibality.

    THE PROBLEM:
        C use 0 based indexing while lua uses 1 based indexing.

    SOLUTION:
        Subtract 1 before calling the C function.
            
        Sounds like a great idea! With the best of intentions! What could possibly go wrong?
        Nothing went wrong so far
]]

Matrix = {}

Matrix.__index = Matrix

--Convert index used in lua to index used for C code
local function convert(x, y)
    return x-1, y-1;
end

--Make sure that variable X and Y are not out of bounds
local function sizeCheck(self, x, y)
    if x > self.x then
        error("x is larger than the size of x")
    end

    if y > self.y then
        error("y is larger than the size of y")
    end

    if x < 0 then
        error("x is less than 0")
    end

    if y < 0 then
        error("y is less than 0")
    end
end

--Check the size of 2 matrix to make sure the are the same
local function dimensionCheck(a, b)
    if a.x ~= b.x then
        error("Dimension X is different")
    end

    if a.y ~= b.y then
        error("Dimension Y is different")
    end
end

--Creates a new matrix.
--@param x number The amount of column
--@param y number The amount of row
--@return matrix
function Matrix.new(x, y)
    if math.type(x) ~= 'integer' then
        return nil
    end

    if math.type(y) ~= 'integer' then
        return nil
    end

    local self = {}
    local matrix = dll.create(x, y)
    self.matrix = matrix
    self.x = x
    self.y = y

    self = setmetatable(self, Matrix)
    return self
end

--Get individual element in Matrix
function Matrix:get(x, y)

    sizeCheck(self, x, y)

    x, y = convert(x, y) --This converts x and y to 0 based indexing

    return dll.get(self.matrix, x, y)
end

--Set individual element in Matrix
function Matrix:set(x, y, number)
    sizeCheck(self, x, y)

    x, y = convert(x, y) --This converts x and y to 0 based indexing

    dll.set(self.matrix, x, y, number)

end

--Returns a formatted matrix.
--@param seperator Optional, it is what appears between the values of the matrix. Default is ",\t"
--@param prefix Optional, concatenated at the beginning of a value. Default is 1 space " "
--@return string Formatted string of the matrix
function Matrix:format(seperator, prefix)
    local output_str = ""
    local comma = seperator or ",\t"
    local prefix = prefix or " "
    local lastY = 1;
    for x, y, var in self:loop() do
        --If the iterator are on the last element then make the comma disappear

        if (x == self.x) and (y == self.y) then
            comma = '\t'
        end

        --Have we move on to the next row?
        if y ~= lastY then

            output_str = output_str.."\n"
            output_str = output_str..prefix..tostring(var)..comma

        else --If not do this
            output_str = output_str..prefix..tostring(var)..comma
        end

        lastY = y
    end

    return output_str
end

--Custom for loop iterator
--@return number, number, number
function Matrix:loop()
    --realX and realY are the index used for the C matrix
    local realX = 0
    local realY = 1

    --Constant
    local column = self.x
    local row = self.y

    return function()
        --increment call
        realX=realX+1

        --If the iteration have completed the first row then it will reset and go to the next row
        if (realX) > column then
            realX = 1
            realY = realY+1
        end

        --If we have completed all of the row then we will terminate
        if realY > row then
            return nil, nil, nil
        end

        return realX, realY, self:get(realX, realY)
    end
end

------------------
--Misc metamethods
------------------

--Delete the table after being unused
function Matrix.__gc(self)
    --Prevent memory leak
    dll.free(self.matrix)
end

--Make the table readonly
--Doesnt work and never will work and it isn't nessecary
-- function Matrix.__newindex(self, key, value)
--     error("Attempted to write to readonly Matrix.", 2)
-- end

------------------
--Matrix operations
------------------

function Matrix.__add(self, b)
    dimensionCheck(self, b)
    local c = Matrix.new(self.x, self.y)
    c.matrix = dll.add(self.matrix, b.matrix)

    return c
end

function Matrix.__sub(self, b)
    dimensionCheck(self, b)
    local c = Matrix.new(self.x, self.y)
    c.matrix = dll.sub(self.matrix, b.matrix)

    return c
end

--Returns the product of 2 matrices
function Matrix.__mul(self, b)
    if self.x ~= b.y then
        error("Size doesn't fit for matrix multiplication")
    end

    local c = Matrix.new(b.x, self.y)
    c.matrix = dll.mul(self.matrix, b.matrix)

    return c
end



return Matrix


