$input v_color0

/*
 * Copyright 2011-2022 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */
 
#include <bgfx_shader.sh>
//#include "../common/common.sh"

void main()
{
	//gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	gl_FragColor = v_color0;
}