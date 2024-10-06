local Matrix = require("matrix")

------------------
---TESTING
------------------
print("Benchmark create matrix 20 x 20")
local time = os.clock()
local a = Matrix.new(4, 4)
time = os.clock() - time
print("Time taken: "..(time).."s")

print("Benchmark create matrix 20 x 20")
time = os.clock()
local b = Matrix.new(4, 4)
time = os.clock() - time
print("Time taken: "..(time).."s")


for x, y, element in a:loop() do
    a:set(x, y, math.random(-1, 1))
end

for x, y, element in b:loop() do
    b:set(x, y, math.random(-1, 1))
end

print(a:format("|"))
print(a.y.."x"..a.x)
print("------------------")
print(b:format("|"))
print(b.y.."x"..b.x)

local c = (a*b)
print("\nA * B = ")
print(c:format('|'))
print(c.y.."x"..c.x)

print("Bench mark test start A x B. A: 4 x 4. B: 4 x 4")
time = os.clock()
local c = a*b
time = os.clock() - time
print("Benchmark ends. Final time: ")
print(time.."seconds")
