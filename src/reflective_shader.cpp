#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& same_side_normal,int recursion_depth) const
{
    vec3 color;
    
	for(int i = 0; i < world.lights.size(); i++)
	{	
	
		//std::cout << "Hello" << std::endl;
		//vec3 t = ray.endpoint + intersection_point * ray.direction;
		vec3 R = 2 * dot((ray.direction.normalized() * -1), same_side_normal.normalized()) * same_side_normal.normalized() - (ray.direction.normalized() * -1);
	
	
		Ray reflection(intersection_point + 0.001*R, R);
		
		recursion_depth++;
		vec3 reflected_color = world.Cast_Ray(reflection, recursion_depth);
		
		
		
		color = (reflectivity*reflected_color + (1-reflectivity)*shader->Shade_Surface(ray, intersection_point, same_side_normal, recursion_depth));
		
		
	}
	
    return color;
}
