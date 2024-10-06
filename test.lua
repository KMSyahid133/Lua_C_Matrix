local Matrix = require("matrix")

------------------
---Variable
------------------

local prefix = ''
local seperator = '|'

------------------
---TESTING
------------------
print("Benchmark create matrix 4 x 4")
local time = os.clock()
local a = Matrix.new(4, 4)
time = os.clock() - time
print("Time taken: "..(time).."s")

print("Benchmark create matrix 4 x 4")
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

print(a:format(seperator, prefix))
print(a.y.."x"..a.x)
print("------------------")
print(b:format(seperator, prefix))
print(b.y.."x"..b.x)


--Operation benchmark

print("Bench mark test start..\nA: 4 x 4. B: 4 x 4")

print("\nMultiplication")
time = os.clock()
local c = a*b
time = os.clock() - time

print(c:format(seperator,prefix))

print("\nAddition")
time = os.clock()
c = a+b
time = os.clock() - time

print(c:format(seperator,prefix))

print("\nSubtraction")
time = os.clock()
local c = a-b
time = os.clock() - time

print(c:format(seperator,prefix))

print("Benchmark ends. Final time: ")
print(time.."seconds")
