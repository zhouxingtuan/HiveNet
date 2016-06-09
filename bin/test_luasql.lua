--
-- Created by IntelliJ IDEA.
-- User: AppleTree
-- Date: 16/6/9
-- Time: 下午5:55
-- To change this template use File | Settings | File Templates.
--


local env = luasql.mysql()
print("mysql env", env)
local con = assert (env:connect("log", "AppleTree", "66", "127.0.0.1", 3306))
-- reset our table
local res = con:execute"DROP TABLE people"
res = assert (con:execute[[
  CREATE TABLE people(
    name  varchar(50),
    email varchar(50)
  )
]])
-- add a few elements
local list = {
    { name="Jose das Couves", email="jose@couves.com", },
    { name="Manoel Joaquim", email="manoel.joaquim@cafundo.com", },
    { name="Maria das Dores", email="maria@dores.com", },
}
for i, p in pairs (list) do
    res = assert (con:execute(string.format([[
    INSERT INTO people
    VALUES ('%s', '%s')]], p.name, p.email)
    ))
end
-- retrieve a cursor
local cur = assert (con:execute"SELECT name, email from people")
-- print all rows
local row = cur:fetch ({}, "a")	-- the rows will be indexed by field names
while row do
    print(string.format("Name: %s, E-mail: %s", row.name, row.email))
    row = cur:fetch (row, "a")	-- reusing the table of results
end
-- close everything
cur:close()
con:close()
env:close()
