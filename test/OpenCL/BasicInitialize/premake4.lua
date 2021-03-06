function createProject(vendor)
	
	hasCL = findOpenCL(vendor)
	
	if (hasCL) then

		project ("Test_OpenCL_intialize_" .. vendor)

		initOpenCL(vendor)
	
		language "C++"
				
		
		kind "ConsoleApp"
		targetdir "../../../bin"

		includedirs {"../../../src"}
		
		files {
			"main.cpp",
			"../../../src/Bullet3OpenCL/Initialize/b3OpenCLUtils.cpp",
			"../../../src/Bullet3OpenCL/Initialize/b3OpenCLUtils.h"
		}
		
	end
end
	
createProject("Apple")
createProject("AMD")
createProject("Intel")
createProject("NVIDIA")
