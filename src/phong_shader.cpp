#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"
#include "math.h"


vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& same_side_normal,int recursion_depth) const
{
    vec3 color;
    
	// A M B I E N T
	color += world.ambient_color * world.ambient_intensity * color_ambient;
	
	for(int i = 0; i < world.lights.size(); i++)
	{
		vec3 light_color = world.lights[i]->Emitted_Light(ray);

		
		if(world.enable_shadows)
		{
			Object *obj = nullptr;
			Hit hit;
			Ray shadow_ray(intersection_point, (world.lights[i]->position - intersection_point).normalized());
			obj = world.Closest_Intersection(shadow_ray, hit);
			
			if(obj != nullptr && (hit.t < (world.lights[i]->position - intersection_point).magnitude()))
			{
				continue;
			}
		}
			
			// D I F F U S E
			vec3 L = world.lights[i]->position - intersection_point;
	
			double dist = L.magnitude();
			dist = pow(dist, 2);

			color += color_diffuse * (light_color / dist)  * fmax(0, dot(L.normalized(), same_side_normal.normalized()));
	
	
	
			// S P E C U L A R

			color += color_specular * (light_color / dist) * pow(fmax(dot((2 * (dot(L, same_side_normal)) * same_side_normal - L).normalized(), (ray.endpoint - intersection_point).normalized()), 0), specular_power);
	
	}
	
    return color;
}
