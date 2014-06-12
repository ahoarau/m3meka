



file(GLOB M3RTSCRIPTS
"demo/*.py"
"dev/*.py"
"ros_dev/*.py"
"tutorials/*.py"
)
message("Scripts:${M3RTSCRIPTS}")

install (
	FILES ${M3RTSCRIPTS} 
	PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ WORLD_EXECUTE
	DESTINATION bin
)




