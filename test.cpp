///* A simple ray tracer - part 1 */
//
//#include <stdio.h>
//#include <stdbool.h> /* Needed for boolean datatype */
//#include "Include/miniRT.h"
//
//
///* The vector structure */
//typedef struct{
//      double x,y,z;
//}vector;
//
///* The sphere */
//typedef struct{
//        vector pos;
//        double  radius;
//}sphere;
//
///* The ray */
//typedef struct{
//        vector start;
//        vector dir;
//}ray;
//
///* Subtract two vectors and return the resulting vector */
//vector vectorSub(vector *v1, vector *v2){
//	vector result = {v1->x - v2->x, v1->y - v2->y, v1->z - v2->z };
//	return result;
//}
//
///* Multiply two vectors and return the resulting scalar (dot product) */
//double vectorDot(vector *v1, vector *v2){
//	return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
//}
//
//
///* Check if the ray and sphere intersect */
//bool intersectRaySphere(ray *r, sphere *s){
//
//	/* A = d.d, the vector dot product of the direction */
//	double A = vectorDot(&r->dir, &r->dir);
//
//	/* We need a vector representing the distance between the start of
//	 * the ray and the position of the circle.
//	 * This is the term (p0 - c)
//	 */
//	vector dist = vectorSub(&r->start, &s->pos);
//
//	/* 2d.(p0 - c) */
//	double B = 2 * vectorDot(&r->dir, &dist);
//
//	/* (p0 - c).(p0 - c) - r^2 */
//	double C = vectorDot(&dist, &dist) - (s->radius * s->radius);
//
//	/* Solving the discriminant */
//	double discr = B * B - 4 * A * C;
//
//	/* If the discriminant is negative, there are no real roots.
//	 * Return false in that case as the ray misses the sphere.
//	 * Return true in all other cases (can be one or two intersections)
//	 */
//	if(discr < 0)
//		return false;
//	else
//		return true;
//}
//
//
//int main(){
//	t_minirt *miniRT;
//	miniRT = ft_calloc(1, sizeof(t_minirt));
//	/* Our ray and a sphere */
//	sphere s;
//	ray r;
//
//	/* x, y for screen 'resolution' */
//	int x,y;
//
//	/* Intersect ray/sphere or not */
//	bool hit;
//
//	/* Position the sphere */
//	s.pos.x = 100.0;
//	s.pos.y = 100.0;
//	s.pos.z = 20.6;
//
//	/* Sphere radius */
//	s.radius = 100;
//
//	/* Direction of the ray */
//	r.dir.x = 0.0;
//	r.dir.y = 0.0;
//	r.dir.z = -10.0;
//
//	/* Start position of the ray, z coordinate */
//	r.start.z = 100;
//
//	/* Iterate over every 'pixel' of our screen
//	 * We use a 40x40 virtual ASCII screen for now
//	 */
//	miniRT->Mlx = ft_calloc(1, sizeof(t_mlx));
//	miniRT->Mlx->mlx = mlx_init();
//	miniRT->Mlx->win = mlx_new_window(miniRT->Mlx->mlx, 720, 540, "miniRT");
//	miniRT->Mlx->img = mlx_new_image(miniRT->Mlx->mlx, 720, 540);
//	miniRT->Mlx->addr = mlx_get_data_addr(miniRT->Mlx->img, &miniRT->Mlx->bits_per_pixel, &miniRT->Mlx->line_length, &miniRT->Mlx->endian);
//
//	for(y=0;y<540;y++){
//		/* Set the y-coordinate of the start position of the ray */
//		r.start.y = y;
//		for(x=0;x<720;x++){
//			/* Set the x-coordinate of the start position of the ray */
//			r.start.x = x;
//
//			/* Check if the ray intersects with the shpere */
//			hit = intersectRaySphere(&r, &s);
//			if(hit)
//				my_mlx_pixel_put(miniRT->Mlx, x, y, 0xFFFF00);
//			else
//				my_mlx_pixel_put(miniRT->Mlx, x, y, 0x000033);
//		}
//		/* First row of the screen done, move to next row */
//
//	}
//	mlx_put_image_to_window(miniRT->Mlx->mlx, miniRT->Mlx->win, miniRT->Mlx->img, 0, 0);
//	mlx_loop(miniRT->Mlx->mlx);
//}

#include <cstdlib> 
#include <cstdio> 
#include <cmath> 
#include <fstream> 
#include <vector> 
#include <iostream> 
#include <cassert> 
 
#if defined __linux__ || defined __APPLE__ 
// "Compiled for Linux
#else 
// Windows doesn't define these values by default, Linux does
#define M_PI 3.141592653589793 
#define INFINITY 1e8 
#endif 
 
template<typename T> 
class Vec3 
{ 
public: 
    T x, y, z; 
    Vec3() : x(T(0)), y(T(0)), z(T(0)) {} 
    Vec3(T xx) : x(xx), y(xx), z(xx) {} 
    Vec3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {} 
    Vec3& normalize() 
    { 
        T nor2 = length2(); 
        if (nor2 > 0) { 
            T invNor = 1 / sqrt(nor2); 
            x *= invNor, y *= invNor, z *= invNor; 
        } 
        return *this; 
    } 
    Vec3<T> operator * (const T &f) const { return Vec3<T>(x * f, y * f, z * f); } 
    Vec3<T> operator * (const Vec3<T> &v) const { return Vec3<T>(x * v.x, y * v.y, z * v.z); } 
    T dot(const Vec3<T> &v) const { return x * v.x + y * v.y + z * v.z; } 
    Vec3<T> operator - (const Vec3<T> &v) const { return Vec3<T>(x - v.x, y - v.y, z - v.z); } 
    Vec3<T> operator + (const Vec3<T> &v) const { return Vec3<T>(x + v.x, y + v.y, z + v.z); } 
    Vec3<T>& operator += (const Vec3<T> &v) { x += v.x, y += v.y, z += v.z; return *this; } 
    Vec3<T>& operator *= (const Vec3<T> &v) { x *= v.x, y *= v.y, z *= v.z; return *this; } 
    Vec3<T> operator - () const { return Vec3<T>(-x, -y, -z); } 
    T length2() const { return x * x + y * y + z * z; } 
    T length() const { return sqrt(length2()); } 
    friend std::ostream & operator << (std::ostream &os, const Vec3<T> &v) 
    { 
        os << "[" << v.x << " " << v.y << " " << v.z << "]"; 
        return os; 
    } 
}; 
 
typedef Vec3<double> Vec3f; 
 
class Sphere 
{ 
public: 
    Vec3f center;                           /// position of the sphere 
    double radius, radius2;                  /// sphere radius and radius^2 
    Vec3f surfaceColor, emissionColor;      /// surface color and emission (light) 
    double transparency, reflection;         /// surface transparency and reflectivity 
    Sphere( 
        const Vec3f &c, 
        const double &r, 
        const Vec3f &sc, 
        const double &refl = 0, 
        const double &transp = 0, 
        const Vec3f &ec = 0) : 
        center(c), radius(r), radius2(r * r), surfaceColor(sc), emissionColor(ec), 
        transparency(transp), reflection(refl) 
    { /* empty */ } 
// Compute a ray-sphere intersection using the geometric solution

    bool intersect(const Vec3f &rayorig, const Vec3f &raydir, double &t0, double &t1) const 
    { 
        Vec3f l = center - rayorig; 
        double tca = l.dot(raydir); 
        if (tca < 0) return false; 
        double d2 = l.dot(l) - tca * tca; 
        if (d2 > radius2) return false; 
        double thc = sqrt(radius2 - d2); 
        t0 = tca - thc; 
        t1 = tca + thc; 
 
        return true; 
    } 
}; 
 
// This variable controls the maximum recursion depth
#define MAX_RAY_DEPTH 5 
 
double mix(const double &a, const double &b, const double &mix) 
{ 
    return b * mix + a * (1 - mix); 
} 
 
// This is the main trace function. It takes a ray as argument (defined by its origin and direction). We test if this ray intersects any of the geometry in the scene. If the ray intersects an object, we compute the intersection point, the normal at the intersection point, and shade this point using this information. Shading depends on the surface property (is it transparent, reflective, diffuse). The function returns a color for the ray. If the ray intersects an object that is the color of the object at the intersection point, otherwise it returns the background color.
Vec3f trace( 
    const Vec3f &rayorig, 
    const Vec3f &raydir, 
    const std::vector<Sphere> &spheres, 
    const int &depth) 
{ 
    //if (raydir.length() != 1) std::cerr << "Error " << raydir << std::endl;
    double tnear = INFINITY; 
    const Sphere* sphere = NULL; 
    // find intersection of this ray with the sphere in the scene
    for (unsigned i = 0; i < spheres.size(); ++i) { 
        double t0 = INFINITY, t1 = INFINITY; 
        if (spheres[i].intersect(rayorig, raydir, t0, t1)) { 
            if (t0 < 0) t0 = t1; 
            if (t0 < tnear) { 
                tnear = t0; 
                sphere = &spheres[i]; 
            } 
        } 
    } 
    // if there's no intersection return black or background color
    if (!sphere) return Vec3f(2); 
    Vec3f surfaceColor = 0;  //color of the ray/surfaceof the object intersected by the ray 
    Vec3f phit = rayorig + raydir * tnear;  //point of intersection 
    Vec3f nhit = phit - sphere->center;  //normal at the intersection point 
    nhit.normalize();  //normalize normal direction 
    // If the normal and the view direction are not opposite to each other
    // reverse the normal direction. That also means we are inside the sphere so set
    // the inside bool to true. Finally reverse the sign of IdotN which we want
    // positive.
    double bias = 1e-4;  //add some bias to the point from which we will be tracing 
    bool inside = false; 
    if (raydir.dot(nhit) > 0) nhit = -nhit, inside = true; 
    if ((sphere->transparency > 0 || sphere->reflection > 0) && depth < MAX_RAY_DEPTH) { 
        double facingratio = -raydir.dot(nhit); 
        // change the mix value to tweak the effect
        double fresneleffect = mix(pow(1 - facingratio, 3), 1, 0.1); 
        // compute reflection direction (not need to normalize because all vectors
        // are already normalized)
        Vec3f refldir = raydir - nhit * 2 * raydir.dot(nhit); 
        refldir.normalize(); 
        Vec3f reflection = trace(phit + nhit * bias, refldir, spheres, depth + 1); 
        Vec3f refraction = 0; 
        // if the sphere is also transparent compute refraction ray (transmission)
        if (sphere->transparency) { 
            double ior = 1.1, eta = (inside) ? ior : 1 / ior;  //are we inside or outside the surface? 
            double cosi = -nhit.dot(raydir); 
            double k = 1 - eta * eta * (1 - cosi * cosi); 
            Vec3f refrdir = raydir * eta + nhit * (eta *  cosi - sqrt(k)); 
            refrdir.normalize(); 
            refraction = trace(phit - nhit * bias, refrdir, spheres, depth + 1); 
        } 
        // the result is a mix of reflection and refraction (if the sphere is transparent)
        surfaceColor = ( 
            reflection * fresneleffect + 
            refraction * (1 - fresneleffect) * sphere->transparency) * sphere->surfaceColor; 
    } 
    else { 
        // it's a diffuse object, no need to raytrace any further
        for (unsigned i = 0; i < spheres.size(); ++i) { 
            if (spheres[i].emissionColor.x > 0) { 
                // this is a light
                Vec3f transmission = 1; 
                Vec3f lightDirection = spheres[i].center - phit; 
                lightDirection.normalize(); 
                for (unsigned j = 0; j < spheres.size(); ++j) { 
                    if (i != j) { 
                        double t0, t1; 
                        if (spheres[j].intersect(phit + nhit * bias, lightDirection, t0, t1)) { 
                            transmission = 0; 
                            break; 
                        } 
                    } 
                } 
                surfaceColor += sphere->surfaceColor * transmission * 
                std::max(double(0), nhit.dot(lightDirection)) * spheres[i].emissionColor; 
            } 
        } 
    } 
 
    return surfaceColor + sphere->emissionColor; 
} 
 
// Main rendering function. We compute a camera ray for each pixel of the image trace it and return a color. If the ray hits a sphere, we return the color of the sphere at the intersection point, else we return the background color.
void render(const std::vector<Sphere> &spheres) 
{ 
    unsigned width = 640, height = 480; 
    Vec3f *image = new Vec3f[width * height], *pixel = image; 
    double invWidth = 1 / double(width), invHeight = 1 / double(height); 
    double fov = 30, aspectratio = width / double(height); 
    double angle = tan(M_PI * 0.5 * fov / 180.); 
    // Trace rays
    for (unsigned y = 0; y < height; ++y) { 
        for (unsigned x = 0; x < width; ++x, ++pixel) { 
            double xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio; 
            double yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle; 
            Vec3f raydir(xx, yy, -1); 
            raydir.normalize(); 
            *pixel = trace(Vec3f(0), raydir, spheres, 0); 
        } 
    } 
    // Save result to a PPM image (keep these flags if you compile under Windows)
    std::ofstream ofs("./untitled.ppm", std::ios::out | std::ios::binary); 
    ofs << "P6\n" << width << " " << height << "\n255\n"; 
    for (unsigned i = 0; i < width * height; ++i) { 
        ofs << (unsigned char)(std::min(double(1), image[i].x) * 255) << 
               (unsigned char)(std::min(double(1), image[i].y) * 255) << 
               (unsigned char)(std::min(double(1), image[i].z) * 255); 
    } 
    ofs.close(); 
    delete [] image; 
} 
 
// In the main function, we will create the scene which is composed of 5 spheres and 1 light (which is also a sphere). Then, once the scene description is complete we render that scene, by calling the render() function.
int main(int argc, char **argv) 
{ 
    srand48(13); 
    std::vector<Sphere> spheres; 
    // position, radius, surface color, reflectivity, transparency, emission color
    spheres.push_back(Sphere(Vec3f( 0.0, -10004, -20), 10000, Vec3f(0.20, 0.20, 0.20), 0, 0.0)); 
    spheres.push_back(Sphere(Vec3f( 0.0,      0, -20),     4, Vec3f(1.00, 0.32, 0.36), 1, 0.5)); 
    spheres.push_back(Sphere(Vec3f( 5.0,     -1, -15),     2, Vec3f(0.90, 0.76, 0.46), 1, 0.0)); 
    spheres.push_back(Sphere(Vec3f( 5.0,      0, -25),     3, Vec3f(0.65, 0.77, 0.97), 1, 0.0)); 
    spheres.push_back(Sphere(Vec3f(-5.5,      0, -15),     3, Vec3f(0.90, 0.90, 0.90), 1, 0.0)); 
    // light
    spheres.push_back(Sphere(Vec3f( 0.0,     20, -30),     3, Vec3f(0.00, 0.00, 0.00), 0, 0.0, Vec3f(3))); 
    render(spheres); 
 
    return 0; 
} 