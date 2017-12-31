#include "sphere.h"
#include "ray.h"
#include <cmath>


// Determine if the ray intersects with the sphere
bool Sphere::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{

	vec3 w = ray.direction;
	vec3 u = ray.endpoint;
	vec3 v = u - this->center;
	double r = this->radius;
	
	double b = dot(w,v);
	double a = dot(w,w);
	double c = dot(v,v);
	
	double discrim = (b*b) - a*(c - (r*r));
	
	
	// calculate intersections
	if(discrim > 0)
	{
		double t_1 = -b - sqrt(discrim) / (a);
		double t_2 = -b + sqrt(discrim) / (a);
		
		Hit h1 = {this, t_1, true};
		Hit h2 = {this, t_2, true};
		
		if(t_1 >= 0)
		{
			hits.push_back(h1);
		}
		if(t_2 >= 0)
		{
			hits.push_back(h2);
		}
	}
	
	
	
	
	
	// end
	
	
	
	
	if(discrim < 0)
	{
		return false;
	}
	else
	{
		return true;
	}
	
}

vec3 Sphere::Normal(const vec3& point) const
{
    vec3 normal;
	
	normal = ((point - center) / radius).normalized();
    return normal;
}
