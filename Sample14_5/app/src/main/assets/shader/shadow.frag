#version 400
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

layout (binding = 1) uniform sampler2D tex;
layout (location = 0) in vec4 inLightQD;
layout (location = 1) in vec2 inTexCoor;
layout (location = 2) in float shadow;
layout (location = 0) out vec4 outColor;

void main(){

   if(shadow==0){							//绘制物体本身
	    vec4 finalColor=texture(tex, inTexCoor);		//物体本身的颜色
	    //综合三个通道光的最终强度及片元的颜色计算出最终片元的颜色并传递给管线
	    outColor = inLightQD*finalColor;
   	}else{								//绘制阴影
	    outColor = vec4(0.2,0.2,0.2,1.0);		//片元最终颜色为阴影的颜色
    }
}