newTable = {}
newTable['value'] = 3.14
newTable[3.14] = "value"
keyTable = {}
newTable[keyTable] = "VALID"


print(newTable["value"])
print(newTable[3.14])
print(newTable[keyTable])
