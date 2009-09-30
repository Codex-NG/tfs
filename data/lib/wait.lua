--[[
	FIXME

Wait = createClass(nil)
Wait:setAttributes({
	co = nil
})

Wait.wait = coroutine.yield
function Wait:continue()
	if(self:co == nil or coroutine.status(self:co) == 'dead') then
		return false
	end

	local _, delay = coroutine.resume(self:co)
	addEvent(self:continue, delay)
	return true
end

function Wait:createObject(v)
	local f, t = v, type(v)
	if(t == 'string') then
		f = loadstring(v)
	elseif(t ~= 'function') then
		return false
	end

	self:co = coroutine.create(f)
	self:continue()
	return true
end
]]--
