newTable = {}
newTable['first'] = 1
newTable['second'] = 2
newTable['third'] = 3

for key,value in pairs(newTable) do
	print(key..":" ..value)
end

newTable = {}
table.insert(newTable,"first")
table.insert(newTable,"second")
table.insert(newTable,"third")

for index,value in ipairs(newTable) do
	print(index..": "..value)
end
