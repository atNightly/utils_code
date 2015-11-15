newTable = {}
table.insert(newTable,"first")
table.insert(newTable,"second")
table.insert(newTable,"third")
-- 求长度
print(#newTable)
-- 跳着插入
newTable[5] = "fourth"
print(newTable[9])
-- 求长度
print(#newTable)

