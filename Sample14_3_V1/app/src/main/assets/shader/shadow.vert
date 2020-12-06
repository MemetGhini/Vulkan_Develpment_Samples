#version 400
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable
layout (push_constant) uniform constantVals { //推送常量块
    mat4 mvp; //总变换矩阵
    mat4 mm; //基本变换矩阵
} myConstantVals;
layout (location = 0) in vec3 pos; //输入的顶点位置
layout (location = 0) out vec4 vPosition; //输出到片元着色器的顶点坐标
out gl_PerVertex { vec4 gl_Position;}; //内建变量 gl_Position
void main() { //主方法
    gl_Position = myConstantVals.mvp * vec4(pos,1.0); //计算顶点的最终位置
    vPosition=myConstantVals.mm*vec4(pos,1); //计算出基本变换后的顶点位置并传递给片元着色器
}
