
require("class")

local Player = class("Player")

function Player:ctor(name, word)
	print("ctor called param", name, word)
	self.m_name = name
	self.m_word = word
end
function Player:say()
	print("Player", self.m_name, "say", self.m_word)
end

local p = Player.new("Lily", "How are you!")
p:say()

local test_global_new = function()
	g_param_1 = 0
end
local test_global_index = function()
	local h = g_param_2
	local h = _G["tttt"]
	local classes_table = classes
	for k,v in pairs(classes_table) do
		print(k, v)
	end
end
print(pcall(test_global_new))
print(pcall(test_global_index))

print("=====params of _G begin========")
for k,v in pairs(_G) do
	print(k, v)
end
print("=====params of _G end==========")
