value1 = 2

while value1 do
	print("We got here! "..value1)
	value1 = value1 - 1
	if value1 == -1 then
		break
	end
end
